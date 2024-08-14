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

        database = client.db('BMS');
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
            .limit(48)
            .toArray();
        
        const timeStamps = getTimeStamps(latestReadings);
        const temperatureValues = getEnvironmentData(latestReadings, 'temperature');

        return { timeStamps, temperatureValues };

    } catch(err) {

        console.log(err);
    };

    client.close();
}


// Fetch 25 latest humidity readings
async function getHumiHistory() {

    await connectToDB();

    try {

        const latestReadings = await humiCollection.find()
            .sort({ time: -1 }) // sort by time in descending order to get the latest entries
            .limit(48)
            .toArray();

        const timeStamps = getTimeStamps(latestReadings);
        const humidityValues = getEnvironmentData(latestReadings, 'humidity');

        return { timeStamps, humidityValues };

    } catch(err) {

        console.log(err);
    };

    client.close();
}


// Iterate through JSON array and extract time stamps for visual chart X axis.
function getTimeStamps(environmentArray) {

    const timeStamps = environmentArray.map(doc => doc.time);

    return timeStamps;
}


// Iterate through JSON array and extract temperature/humidity for visual chart Y axis.
function getEnvironmentData(environmentArray, environmentDataType) {

    const environmentData = environmentArray.map(doc => doc[environmentDataType]);

    return environmentData;
}


// Post new temperature reading to database
async function addTempValue(temperature) {

    try {

        await connectToDB();

        await tempCollection.insertOne({

            temperature: temperature,
            time: new Date(Date.now()).toLocaleTimeString('sv-SE', { // Add Hour and minute as time attribute

                hour: '2-digit',
                minute: '2-digit'
            })
        });

    } catch(err) {

        console.log(err);
    };

    client.close();
}


// Post new humidity reading to database
async function addHumiValue(humidity) {

    try {

        await connectToDB();

        await humiCollection.insertOne({

            humidity: humidity,
            time: new Date(Date.now()).toLocaleTimeString(undefined, { // Add Hour and minute as time attribute

                hour: '2-digit',
                minute: '2-digit'
            })
        });

    } catch (err) {
        
        console.log(err);
    };

    client.close();
}


module.exports = { 

    getHumiHistory, 
    getTempHistory, 
    addHumiValue, 
    addTempValue 

}