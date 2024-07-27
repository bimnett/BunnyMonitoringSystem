const express = require('express');
const { SERVER_PORT } = require('./server_secrets');
const { initializeWebSocketServer } = require('./websocket');

const app = express();
app.use(express.json());


const server = app.listen(SERVER_PORT, () => {

  console.log(`Server is running on http://localhost:${SERVER_PORT}`);
});

initializeWebSocketServer(server);

module.exports = { app, server };