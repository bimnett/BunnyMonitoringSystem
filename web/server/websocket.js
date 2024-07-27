const WebSocket = require('ws');

let wss;

function initializeWebSocketServer(server) {
    wss = new WebSocket.Server({ server });

    wss.on('connection', (ws) => {
        console.log("New WebSocket client connected.");
        
        ws.on('close', () => {
            console.log("WebSocket client disconnected.");
        });
    });

    return wss;
}

function getWebSocketServer() {
    return wss;
}

module.exports = { initializeWebSocketServer, getWebSocketServer };