// Import mqtt node package and hidden credentials
import mqtt from 'mqtt';
import { MQTT_HOST } from './server_secrets';


// Create mqtt client
export const mqttClient = mqtt.connect(MQTT_HOST);
const topic = 'bms/#';


// Subscribe to topic when connected to broker
mqttClient.on('connect', () => {

    console.log('Connected to MQTT broker!');

    mqttClient.subscribe(topic, (err) => {

        if(!err) {
            console.log(`Subscribed to ${topic}`);
        }
        else {
            console.log("An error has occured.");
        }
    });
});


// Function to set up a message handler
export function setMqttMessageHandler(handler) {

    mqttClient.on('message', (topic, message) => {

        if (topic === "bms/environment/temperature") {
            handler({ temperature: message });

        } else if (topic === "bms/environment/humidity") {
            handler({ humidity: message });
        }
    });
}
