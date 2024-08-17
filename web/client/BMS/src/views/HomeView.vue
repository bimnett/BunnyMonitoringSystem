<template>
  <div class="dashboard">
    <header class="header">
      <h1>Dashboard</h1>
    </header>
    <div class="stats-cards">
      <TemperatureHumidity />
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
import TemperatureHistoryChart from '@/components/TemperatureHistoryChart.vue'
import HumidityHistoryChart from '@/components/HumidityHistoryChart.vue'
import TemperatureHumidity from '@/components/TemperatureHumidity.vue'

export default {

  name: 'HomeView',

  components: {
    TemperatureHistoryChart,
    HumidityHistoryChart,
    TemperatureHumidity
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
  margin-bottom: 30px;
  text-align: center;
}
h1 {
  margin: 0;
}
.stats-cards {
  display: flex;
  justify-content: space-between;
  text-align: center;
}
.charts {
  display: flex;
  justify-content: space-between;
}
.chart {
  background-color: #27293d;
  padding: 24px;
  border-radius: 5px;
  margin-top: 40px;
  width: 45%;
  height: 350px; /* Adjust this value as needed */
  text-align: center;
  display: flex;
  flex-direction: column;
}
</style>