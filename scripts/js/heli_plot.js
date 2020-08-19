/**
 * HeliPlot - Plots data points from
 * the heli copter on the HeliRig Viewer
 * 
 * Author: Jos Craw
 */

let ctxAlt = document.getElementById('altChart').getContext('2d');
let ctxYaw = document.getElementById('yawChart').getContext('2d');

let altChart = new Chart(ctxAlt, {
    type: 'line',
    data: {
        labels: [],
        datasets: [{
            label: 'Vertical Error',
            data: [],
            pointRadius: 0,
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

<<<<<<< HEAD
let yawChart = new Chart(ctxYaw, {
    type: 'line',
    data: {
        labels: [],
        datasets: [{
            label: 'Yaw Error',
            data: [],
            pointRadius: 0,
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


let i = 0;
let j = 0;

function plotAltitude(dataArray) {
    dataArray.forEach((element) => {
        altChart.data.labels.push(i);
        i += 1;
        altChart.data.datasets.forEach((dataset) => {
            dataset.data.push(element);
        });
    });
    altChart.update();
}

function plotYaw(dataArray) {
    dataArray.forEach((element) => {
        yawChart.data.labels.push(i);
        i += 1;
        yawChart.data.datasets.forEach((dataset) => {
=======
let i = 0;

function plotData(dataArray) {
    dataArray.forEach((element) => {
        chart.data.labels.push(i);
        i += 1;
        plotChart.data.datasets.forEach((dataset) => {
>>>>>>> 5d74426... Started Plotting stuff
            dataset.data.push(element);
        });
    });
    yawChart.update();
}

