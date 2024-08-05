const { MongoClient, ServerApiVersion } = require('mongodb');
const { MONGODB_URI } = require('./databaseSecrets');

// MongoDB database and collections to post/get environment data
let database;
let tempCollection;
let humiCollection;


// Create a MongoClient with a MongoClientOptions object to set the Stable API version
const client = new MongoClient(MONGODB_URI, {
  serverApi: {
    version: ServerApiVersion.v1,
    strict: true,
    deprecationErrors: true,
  }
});


async function connectToDB() {

    console.log('Connecting to DB..');

    try {

        await client.connect();

        database = client.db('bms');
        tempCollection = database.collection('temperature');
        humiCollection = database.collection('humidity');

        console.log('Connected to DB');
    }

    catch(err) {
        console.log(err);
    }
}


// Fetch 25 latest temperature readings
async function getTempHistory() {

    await connectToDB();

    try {

        const latestReadings = await tempCollection.find()
            .sort({ time: -1 }) // sort by time in descending order to get the latest entries
            .limit(25)
            .toArray();

        return latestReadings;

    } catch(err) {

        console.log(err);
    }

    client.close();
}


// Fetch 25 latest humidity readings
async function getHumiHistory() {

    await connectToDB();

    try {

        const latestReadings = await humiCollection.find()
            .sort({ time: -1 }) // sort by time in descending order to get the latest entries
            .limit(25)
            .toArray();

        return latestReadings;

    } catch(err) {

        console.log(err);
    }

    client.close();
}


// Post new temperature reading to database
async function addTempValue(temperature) {

    try {

        await connectToDB();

        await tempCollection.insertOne({
            temperature: temp,
            time: Date.now()
        })

    } catch(err) {

        throw(err);
    }

    client.close();
}


// Post new humidity reading to database
async function addHumiValue(humidity) {

    try {

        await connectToDB();

        await humiCollection.insertOne({

            humidity: humi,
            time: Date.now()
        })
    } catch (err) {
        throw(err);
    }

    client.close();
}


module.exports = { 

    getHumiHistory, 
    getTempHistory, 
    addHumiValue, 
    addTempValue 

}