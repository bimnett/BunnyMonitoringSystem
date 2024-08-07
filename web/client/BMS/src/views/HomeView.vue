<template>
  <div class="dashboard">
    <header class="header">
      <h1>Dashboard</h1>
    </header>
    <div class="stats-cards">
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
    </div>
    <div class="charts">
      <div class="chart">
        <h3>Temperature History</h3>
        <TemperatureHistoryChart/>
      </div>
      <div class="chart">
        <h3>Humidity History</h3>
        <HumidityHistoryChart/>
      </div>
    </div>
  </div>
</template>

<script>
import { useEnvironmentData } from '@/composables/useEnvironmentData'
import TemperatureHistoryChart from '@/components/TemperatureHistoryChart.vue'
import HumidityHistoryChart from '@/components/HumidityHistoryChart.vue'

export default {

  name: 'HomeView',

  components: {
    TemperatureHistoryChart,
    HumidityHistoryChart
  },

  setup() {

    const { temperature, humidity } = useEnvironmentData();

    return {
      temperature,
      humidity
    }
  }
}
</script>

<style scoped>
.dashboard {
  background-color: #1f1f31;
  color: #f0af3f;
  padding: 30px 30px 20px;
  font-family: 'Poppins', sans-serif;
}
.header {
  margin-bottom: 60px;
  text-align: center;
}
h1 {
  margin: 0;
}
.stats-cards {
  display: flex;
  justify-content: space-between;
  margin-bottom: 50px;
  text-align: center;
}
.card {
  background-color: #27293d;
  padding: 55px;
  border-radius: 5px;
  width: 43%;
}
.number {
  font-size: 24px;
  font-weight: bold;
}
.charts {
  display: flex;
  justify-content: space-between;
}
.chart {
  background-color: #27293d;
  padding: 30px;
  border-radius: 5px;
  margin-top: 40px;
  width: 46%;
  height: 350px; /* Adjust this value as needed */
  text-align: center;
  display: flex;
  flex-direction: column;
}
</style>