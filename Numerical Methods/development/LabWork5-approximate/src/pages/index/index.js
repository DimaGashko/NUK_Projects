import tmpl from 'lodash/template';
import Chart from 'chart.js';
import './index.sass';

import template from './index.template.html';
import Model from './model.js';

const model = new Model();
const approximate = model.approximate();
const approximateYs = approximate.map(item => +item.y.toFixed(2));
const xs = approximate.map(item => +item.x.toFixed(2));
const inputDataPoints = model.data.xs.map((x, i) => {
    return {
        x, y: model.data.ys[i]
    };
});

const $contentSlot = document.querySelector('.content-slot');

$contentSlot.innerHTML = tmpl(template)(model);

const $canvas = document.querySelector('.canvas');
var ctx = $canvas.getContext('2d');
var myChart = new Chart(ctx, {
    type: 'line',
    data: {
        labels: xs.map(x => `x: ${x}`),
        datasets: [{
            label: 'Approximate Function',
            data: approximateYs,
            backgroundColor: 'transparent',
            borderColor: 'rgb(0,110,135)',
        }, {
            label: 'Input Data',
            data: inputDataPoints,
            backgroundColor: 'transparent',
            borderColor: 'transparent',
            pointBackgroundColor: '#6464cd',
            type: 'scatter',
        }],
    },
});

/**

var myChart = new Chart(ctx, {
    type: 'scatter',
    data: {
        datasets: [{
            label: 'Approximate Function',
            data: approximate,
            backgroundColor: '#6464cd',//'transparent',
        }],
    },
    options: {
        scales: {

        }
    }
});



 */