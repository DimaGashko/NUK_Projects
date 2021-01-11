import '../node_modules/chart.js/dist/Chart.min.js';

export function makeResultChart($root) {
   return new Chart($root, {
      type: 'line',
      data: {
         datasets: [{
            label: 'Function value',
            borderColor: 'rgba(240,90,40,1)',
            pointBackgroundColor: 'rgba(240,90,40,1)',
         }, {
            label: 'Solution',
            borderColor: 'rgba(13,96,223,1)',
            pointBackgroundColor: 'rgba(13,96,223,1)',
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
               borderWidth: 1,
               backgroundColor: 'rgba(0,0,0,.05)',
            },
            point: {
               radius: 1,
               hoverRadius: 2,
               borderWidth: 0,
               hoverBorderWidth: 0,
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