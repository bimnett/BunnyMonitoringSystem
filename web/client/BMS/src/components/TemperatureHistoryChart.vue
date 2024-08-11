<template>

    <div class="TemperatureChart">
        <line-chart
            v-if="!loading && !error"
            :chart-data="chartData"
            :gradient-color="gradientColors"
            :gradient-stops="gradientStops"
            :extra-options="extraOptions"
        ></line-chart>
    </div>

</template>
  
  <script>

  import LineChart from '@/components/LineChart.vue'
  import axios from 'axios'
  import { AWS_EC2_PUB_IP, PORT } from '@/assets/client_secrets'
  

  export default {

    name: "TemperatureHistoryChart",

    components: {
        LineChart
    },

    data() {

      return {

        loading: true,
        error: null,
        chartData: {

            labels: [],
            datasets: [{

                label: "Temperature",
                fill: true,
                backgroundColor: 'rgba(240, 175, 63, 0.2)',
                borderColor: '#f0af3f',
                borderWidth: 2,
                borderDash: [],
                borderDashOffset: 0.0,
                pointBackgroundColor: '#f0af3f',
                pointBorderColor: 'rgba(255,255,255,0)',
                pointHoverBackgroundColor: '#f0af3f',
                pointBorderWidth: 20,
                pointHoverRadius: 4,
                pointHoverBorderWidth: 15,
                pointRadius: 4,
                data: [],
                tension: 0.35
            }]
        },
        gradientColors: ['rgba(240, 175, 63, 0.2)', 'rgba(240, 175, 63, 0.0)', 'rgba(240, 175, 63, 0)'],
        gradientStops: [1, 0.4, 0],
        extraOptions: {
            maintainAspectRatio: false,
            plugins: {

                legend: { display: false },
                title: { display: false }
            },
            responsive: true,
            scales: {
                
                y: {
                    grid: {

                        drawBorder: false,
                        display: false,
                        color: 'rgba(240, 175, 63, 0.1)',
                        zeroLineColor: "transparent",
                    },
                    ticks: {

                        suggestedMin: 0,
                        suggestedMax: 40,
                        padding: 20,
                        color: "#f0af3f"
                    }
                },
                x: {
                    grid: {

                        drawBorder: false,
                        display: true,
                        color: 'rgba(240, 175, 63, 0.1)',
                        zeroLineColor: "transparent",
                    },
                    ticks: {

                        padding: 20,
                        color: "#f0af3f"
                    }
                }
            }
        }
      }
    },

    mounted() {
      this.fetchData()
    },

    methods: {

        async fetchData() {

            try {

                const response = await axios.get(`http://${AWS_EC2_PUB_IP}:${PORT}/environment/temperature/history`);

                const labels = response.data.timeStamps;

                this.chartData.labels = labels.reverse();
                this.chartData.datasets[0].data = response.data.temperatureValues.reverse();

                this.loading = false;

            } catch (err) {
                
                console.error('Error fetching temperature history:', err);

                this.error = err.message;
                this.loading = false;
            }
        }
    }
  }
  </script>
  
  <style scoped>

    .TemperatureChart {
        height: 280px;
        width: 100%;
    }

  </style>