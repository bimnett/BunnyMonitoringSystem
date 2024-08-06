<template>
    <div class="chart-container">
      <canvas ref="canvas"></canvas>
    </div>
  </template>
  
  <script>
  import Chart from 'chart.js/auto'
  
  export default {
    name: 'LineChart',
    props: {
      chartData: {
        type: Object,
        required: true
      },
      gradientColor: {
        type: Array,
        default: () => []
      },
      gradientStops: {
        type: Array,
        default: () => []
      },
      extraOptions: {
        type: Object,
        default: () => ({})
      }
    },
    mounted() {
      this.renderChart()
    },
    methods: {
      renderChart() {
        const ctx = this.$refs.canvas.getContext('2d')
        
        // Create gradient
        const gradientStroke = ctx.createLinearGradient(0, 230, 0, 50)
        this.gradientColor.forEach((color, index) => {
          gradientStroke.addColorStop(this.gradientStops[index], color)
        })
  
        // Merge chartData with gradient
        const chartDataWithGradient = {
          ...this.chartData,
          datasets: this.chartData.datasets.map(dataset => ({
            ...dataset,
            backgroundColor: gradientStroke
          }))
        }
  
        // Create chart
        new Chart(ctx, {
          type: 'line',
          data: chartDataWithGradient,
          options: {
            ...this.extraOptions,
            // Add any additional options here
          }
        })
      }
    }
  }
  </script>
  
  <style scoped>
  .chart-container {
    position: relative;
    width: 100%;
    height: 100%;
  }
  </style>