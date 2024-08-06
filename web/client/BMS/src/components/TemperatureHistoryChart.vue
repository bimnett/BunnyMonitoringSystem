<template>

<div class="TemperatureChart">
    <line-chart
        :chart-data="temperatureLineChart.chartData"
        :gradient-color="temperatureLineChart.gradientColors"
        :gradient-stops="temperatureLineChart.gradientStops"
        :extra-options="temperatureLineChart.extraOptions"
    ></line-chart>
</div>

</template>


<script>

import LineChart from '@/components/LineChart.vue'

export default {

    name: "TemperatureHistoryChart",

    components: {
        LineChart
    },

    data() {

        return {

            temperatureLineChart: {

                gradientColors: ['rgba(240, 175, 63, 0.2)', 'rgba(240, 175, 63, 0.0)', 'rgba(240, 175, 63, 0)'],
                gradientStops: [1, 0.4, 0],
                extraOptions: {
                    maintainAspectRatio: false,
                    plugins: {
                        legend: {
                        display: false
                        },
                        title: {
                        display: false
                        }
                    },
                    responsive: true,
                    tooltips: {
                        backgroundColor: '#f5f5f5',
                        titleFontColor: '#333',
                        bodyFontColor: '#666',
                        bodySpacing: 4,
                        xPadding: 12,
                        mode: "nearest",
                        intersect: 0,
                        position: "nearest"
                    },
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
                },
                chartData: {
                    labels: ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN'],
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
                        data: [18, 24, 19, 26, 22, 20],
                        tension: 0.35
                    }]
                }
            }       
        }
    }
}

</script>


<style scoped>

.TemperatureChart {
  height: 280px; 
}

</style>