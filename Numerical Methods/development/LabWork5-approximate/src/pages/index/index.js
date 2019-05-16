import tmpl from 'lodash/template';
import Chart from 'chart.js';
import './index.sass';

import template from './index.template.html';
import Model from './model.js';

const model = new Model();
const approximate = model.approximate();
const approximateYs = approximate.map(item => +item.y.toFixed(2)); 
const xs = approximate.map(item => +item.x.toFixed(2)); 

const $contentSlot = document.querySelector('.content-slot');

$contentSlot.innerHTML = tmpl(template)(model);

const $canvas = document.querySelector('.canvas');
var ctx = $canvas.getContext('2d');
var myChart = new Chart(ctx, {
    type: 'line',
    data: {
        labels: xs,
        datasets: [{
            label: 'value',
            data: approximateYs,
            backgroundColor: 'transparent',
            borderColor: 'rgb(0,110,135)',
        }],
    },
    options: {
        scales: {
            
        }
    }
});