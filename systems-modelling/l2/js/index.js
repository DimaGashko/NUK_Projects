import { debounce } from '../node_modules/throttle-debounce/esm/index.js';
import findSolution from './findSolution.js';
import { makeResultChart } from './resultChart.js';

const $p = document.querySelector('.page-js');
const $args = $p.querySelector('.args-js');
const $chart = $p.querySelector('.chart-js');

const chart = makeResultChart($chart);

initEvents();
update();

function initEvents() {
   const delayedUpdate = debounce(500, update);

   $args.addEventListener('submit', (e) => {
      e.preventDefault();
      update();
   });

   $args.addEventListener('input', delayedUpdate);
   $args.addEventListener('change', delayedUpdate);
}

function update() {
   try {
      const solution = findSolution(getArgs());
      console.log(solution);
      updateChart(solution);
   } catch (e) {
      console.warn('Incorrect data');
      console.error(e);
   }
}

function updateChart({ x, y1, y2 }) {
   chart.data.labels = x.map(y => y.toFixed(4));
   chart.data.datasets[0].data = y1.map(y => y.toFixed(4));
   chart.data.datasets[1].data = y2.map(y => y.toFixed(4));

   chart.update();
}

function getArgs() {
   return {
      b1: +$args.b1.value,
      b2: +$args.b2.value,
      sigma: +$args.sigma.value,
      y0: +$args.y0.value,
      c1: +$args.c1.value,
      c3: +$args.c3.value,
      w: +$args.w.value,
      epsilon: +$args.epsilon.value,
      from: +$args.from.value,
      to: +$args.to.value,
   }
}