import '../node_modules/chart.js/dist/Chart.min.js';

export function makeChart($root) {
   return new Chart($root, {
      type: 'line',
      data: {
         datasets: [{
            label: 'RK4',
            borderColor: 'rgba(240,90,40,1)',
         }, {
            label: "Euler's method",
            borderColor: 'rgba(13,96,223,1)',
         }, {
            label: 'Exact value',
            borderColor: 'rgba(150,9,22,1)',
         }],
      },
      options: {
         maintainAspectRatio: false,
         scales: {
            xAxes: [{
               gridLines: {
                  color: 'red',
                  display: false,
                  offsetGridLines: true,
               },
               ticks: {
                  autoSkip: true,
                  autoSkipPadding: 25,
                  minRotation: 0,
                  maxRotation: 0,
               },
            }],
            yAxes: [{
               gridLines: {
                  drawBorder: false,
                  color: 'rgba(255, 255, 255, 0.05)',
                  zeroLineColor: 'rgba(255, 255, 255, 0.05)',
               },
            }],
         },
         elements: {
            line: {
               tension: 0.15,
               borderWidth: 1.5,
               backgroundColor: 'rgba(0,0,0,.05)',
            },
            point: {
               radius: 0,
            },
         },
         tooltips: {
            intersect: false,
            mode: 'index',
            position: 'nearest',
         },
         legend: {

         },
      },
   });
}