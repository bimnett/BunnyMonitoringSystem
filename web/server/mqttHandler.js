// Import mqtt node package and hidden credentials
const mqtt = require('mqtt');
const { MQTT_HOST } = require('./server_secrets');
const { getWebSocketServer } = require('./websocket');


// Create mqtt client
const client = mqtt.connect(MQTT_HOST);
const topic = 'bms/#';


client.on('connect', () => {

    console.log('Connected to MQTT broker!');

    client.subscribe(topic, (err) => {

        if(!err) {
            console.log(`Subscribed to ${topic}`);
        }
        else {
            console.log("An error has occured.");
        }
    });
});


client.on('message', (topic, message) => {
    
    const wss = getWebSocketServer();

    if(wss) {

        wss.clients.forEach( ws => {

            if (ws.readyState === ws.OPEN) {
                ws.send(JSON.stringify({ topic, message: message.toString() }));
            } else {
                console.log(`WebSocket not open. ReadyState: ${ws.readyState}`);
            }
        });

    } else {
        console.log('WebSocket server (wss) is not initialized');
    }
});


module.exports = { client };