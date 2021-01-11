import { debounce } from "../node_modules/throttle-debounce/esm/index.js";
import findSolution from "./findSolution.js";

const p = document.querySelector('.page-js');
const args = p.querySelector('.args-js');

initEvents();
update();

function initEvents() {
   const delayedUpdate = debounce(500, update);

   args.addEventListener('submit', (e) => {
      e.preventDefault();
      update();
   });

   args.addEventListener('input', delayedUpdate);
   args.addEventListener('change', delayedUpdate);
}

function update() {
   const solution = findSolution(getArgs());
}

function getArgs() {
   return {
      b1: +args.b1.value,
      b2: +args.b2.value,
      sigma: +args.sigma.value,
      y0: +args.y0.value,
      c1: +args.c1.value,
      c3: +args.c3.value,
      w: +args.w.value,
      epsilon: +args.epsilon.value,
      from: +args.from.value,
      to: +args.to.value,
   }
}