import { throttle } from '../node_modules/throttle-debounce/esm/index.js';
import { euler, exact, rk4 } from './solution.js';
import { makeChart } from './chart.js';

const $p = document.querySelector('.page-js');
const $args = $p.querySelector('.args-js');
const $chart = $p.querySelector('.chart-js');

const chart = makeChart($chart);
 
initEvents();
update();

function initEvents() {
   const delayedUpdate = throttle(500, update);

   $args.addEventListener('submit', (e) => {
      e.preventDefault();
      update();
   });

   $args.addEventListener('input', delayedUpdate);
   $args.addEventListener('change', delayedUpdate);
}

function update() {
   if (!$args.checkValidity()) {
      $args.reportValidity();
      return;
   }

   try {
      const args = getArgs();
      updateChart(exact(args), euler(args), rk4(args));
   } catch (e) {
      console.warn('Incorrect data');
      console.error(e);
   }
}

function updateChart(exact, euler, rk4) {
   console.log(exact, euler);
   chart.data.labels = exact.map(p => p.x);
   chart.data.datasets[0].data = exact.map(p => p.y);
   chart.data.datasets[1].data = euler.map(p => p.y);
   chart.data.datasets[2].data = rk4.map(p => p.y);
   chart.update();
}

function getArgs() {
   const maxX = 120;
   const a = +$args.a.value;
   const b = +$args.b.value;
   const h = +$args.h.value;
   const n = maxX / h;
   return { a, b, h, n }
}