// Import mqtt node package and hidden credentials
const mqtt = require('mqtt');
const { MQTT_HOST } = require('./server_secrets');


// Create mqtt client
const client = mqtt.connect(MQTT_HOST);
const topic = 'bms/test';


client.on('connect', () => {

    console.log('Connected to MQTT broker!');

    client.subscribe(topic, (err) => {

        if(!err) {
            console.log(`Subscribed to ${topic}`);
        }
        else {
            console.log("An error has occured.")
        }
    });
});


client.on('message', (topic, message) => {

    console.log(`Received message: ${message} from topic: ${topic}`);
});


const publishMessage = (topic, message) => {
    client.publish(topic, message);
};


module.exports = {
    client,
    publishMessage,
};