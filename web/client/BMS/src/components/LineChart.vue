<template>
  <canvas ref="chart"></canvas>
</template>

<script>
import { Chart, registerables } from 'chart.js'
Chart.register(...registerables)

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
  data() {
    return {
      chart: null
    }
  },
  watch: {
    chartData: {
      handler() {
        this.updateChart()
      },
      deep: true
    }
  },
  mounted() {
    this.createChart()
  },
  beforeUnmount() {
    if (this.chart) {
      this.chart.destroy()
    }
  },
  methods: {
    createChart() {
      const ctx = this.$refs.chart.getContext('2d')
      
      const gradientStroke = ctx.createLinearGradient(0, 230, 0, 50)
      this.gradientColor.forEach((color, index) => {
        gradientStroke.addColorStop(this.gradientStops[index], color)
      })

      const chartDataWithGradient = {
        ...this.chartData,
        datasets: this.chartData.datasets.map(dataset => ({
          ...dataset,
          backgroundColor: gradientStroke
        }))
      }

      this.chart = new Chart(ctx, {
        type: 'line',
        data: chartDataWithGradient,
        options: this.extraOptions
      })
    },
    updateChart() {
      if (this.chart) {
        this.chart.data = this.chartData
        this.chart.update()
      } else {
        this.createChart()
      }
    }
  }
}
</script>