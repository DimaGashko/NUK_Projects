import tmpl from 'lodash/template';
import Chart from 'chart.js';
import './differential.sass';

import template from './differential.template.html';
import Model from './model.js';

const model = new Model();

const eyler = model.eylerDifferential().map(item => {
    return { x: +item.x.toFixed(2), y: +item.y.toFixed(2)}
});

const eylerXs = eyler.map(item => item.x);

const $contentSlot = document.querySelector('.content-slot');
$contentSlot.innerHTML = tmpl(template)(model);

const $canvas = document.querySelector('.canvas');
var ctx = $canvas.getContext('2d');

var differentialChart = new Chart(ctx, {
    type: 'scatter',
    data: {
        labels: eylerXs.map(x => `x: ${x}`),
        datasets: [{
            label: 'Eyler Method',
            data: eyler,
            backgroundColor: 'transparent',
            borderColor: 'rgb(0,110,135)',
        }],
    },
});
