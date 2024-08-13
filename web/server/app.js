const express = require('express');
const { SERVER_PORT } = require('./server_secrets');
const { initializeWebSocketServer } = require('./websocket');
const { getHumiHistory, getTempHistory, addHumiValue, addTempValue } = require('../../database/database');
const cors = require('cors');

const app = express();
app.use(express.json());
app.use(cors({ origin: 'https://bunny-monitoring-system.netlify.app' }));


const server = app.listen(SERVER_PORT, () => {

  console.log(`Server is running on port ${SERVER_PORT}`);
});


initializeWebSocketServer(server);


// Fetch temperature history
app.get('/environment/temperature/history', async (req, res) => {

  try {

    const { timeStamps, temperatureValues } = await getTempHistory();

    res.status(200).send({ timeStamps, temperatureValues });

  } catch(err) {

    res.status(500).send('An error has occured while fetching latest temperatures.')
  }
});


// Fetch humidity history
app.get('/environment/humidity/history', async (req, res) => {

  try {

    const {timeStamps, humidityValues} = await getHumiHistory();

    res.status(200).send({ timeStamps, humidityValues });

  } catch(err) {

    res.status(500).send('An error has occured while fetching latest humidities.')
  }
});


// Post current temperature
app.post('/environment/temperature/history', async (req, res) => {

  try {

    const { temperature } = req.body;

    await addTempValue(temperature);

    res.status(200).send(`Temperature ${temperature} has successfully been added.`);
    
  } catch(err) {

    res.status(500).send('An error has occured while posting latest temperature.')
  }
});


// Post current humidity
app.post('/environment/humidity/history', async (req, res) => {

  try {

    const { humidity } = req.body;

    await addHumiValue(humidity);

    res.status(200).send(`Humidity ${humidity} has successfully been added.`);

  } catch(err) {

    res.status(500).send('An error has occured while posting latest humidity.')
  }
});

module.exports = { app, server };