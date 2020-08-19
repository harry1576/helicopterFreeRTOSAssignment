/**
 * HeliPlot - Plots data points from
 * the heli copter on the HeliRig Viewer
 * 
 * Author: Jos Craw
 */

let ctx = document.getElementById('plotChart').getContext('2d');

let plotChart = new Chart(ctx, {
    type: 'line',
    data: {
        labels: [],
        datasets: [{
            label: 'Vertical Error',
            data: [],
            backgroundColor: 'rgba(255, 99, 132, 0.2)',
            borderColor: 'rgba(255, 99, 132, 1)',
            borderWidth: 1
        }]
    },
    options: {
        scales: {
            yAxes: [{
                ticks: {
                    beginAtZero: true
                }
            }]
        }
    }
});

function plotData(dataArray) {
    dataArray.forEach((element) => {
        plotChart.data.datasets.forEach((dataset) => {
            dataset.data.push(element);
        });
    });
    plotChart.update();
}

