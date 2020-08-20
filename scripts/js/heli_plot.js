/**
 * HeliPlot - Plots data points from
 * the heli copter on the HeliRig Viewer
 * 
 * Author: Jos Craw
 */

let altChart = undefined;
let yawChart = undefined;


function createPlots() {
    let ctxAlt = document.getElementById('altChart').getContext('2d');
    let ctxYaw = document.getElementById('yawChart').getContext('2d');

    altChart = new Chart(ctxAlt, {
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

    yawChart = new Chart(ctxYaw, {
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
}


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
            dataset.data.push(element);
        });
    });
    yawChart.update();
}

