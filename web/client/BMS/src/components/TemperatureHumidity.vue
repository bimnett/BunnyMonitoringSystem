<template>

  <div class="card">
    <h3>Temperature</h3>
    <p v-if="temperature" class="number">{{ temperature }} °C</p>
    <p v-else class="number">-- °C</p>
  </div>

  <div class="card">
    <h3>Humidity</h3>
    <p v-if="humidity" class="number">{{ humidity }}%</p>
    <p v-else class="number">--%</p>
  </div>

</template>


<script>

import { mqttClient, setMqttMessageHandler } from '../../../../server/mqtt.js'

export default {

  data() {

    return {

      temperature: null,
      humidity: null
    }
  },

  mounted() {

    setMqttMessageHandler(({ temperature, humidity }) => {

      if (temperature !== undefined) {
        this.temperature = temperature;
      }

      if (humidity !== undefined) {
        this.humidity = humidity;
      }
    });
  },

  name: 'TemperatureHumidity'
}

</script>


<style scoped>

  #temperature, #humidity {

    text-align: center;
    caret-color: transparent;
    margin-right: 20px;
  }

  .card {
  background-color: #27293d;
  padding: 38px;
  border-radius: 5px;
  width: 43%;
  }

  .number {
  font-size: 24px;
  font-weight: bold;
  }

</style>