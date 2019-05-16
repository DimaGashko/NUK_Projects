import tmpl from 'lodash/template';
import Chart from 'chart.js';
import './index.sass';

import template from './index.template.html';
import Model from './model.js';

const model = new Model();
const approximateYs = model.approximate();

const $contentSlot = document.querySelector('.content-slot');

$contentSlot.innerHTML = tmpl(template)(model);

const $canvas = document.querySelector('.canvas');
var ctx = $canvas.getContext('2d');
var myChart = new Chart(ctx, {
    type: 'bar',
    data: {
        labels: approximateYs,
        datasets: [{
            label: '# of Votes',
            data: approximateYs,
            backgroundColor: [
                'rgba(255, 99, 132, 0.2)',
                'rgba(54, 162, 235, 0.2)',
                'rgba(255, 206, 86, 0.2)',
                'rgba(75, 192, 192, 0.2)',
                'rgba(153, 102, 255, 0.2)',
                'rgba(255, 159, 64, 0.2)'
            ],
            borderColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)',
                'rgba(153, 102, 255, 1)',
                'rgba(255, 159, 64, 1)'
            ],
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