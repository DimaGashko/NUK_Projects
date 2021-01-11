
export default function findSolution({ b1, b2, sigma, y0, c1, c3, w, epsilon, from, to }) {
   from = 0;
   to = 180;
   c1 = 1;
   c3 = -1;
   w = 1;
   epsilon = 0.05;
   b1 = 0.01;
   b2 = 3;
   sigma = 0.150;
   y0 = 0.166;   

   const res = [];
   let delta = 2;

   while (true) {
      const n = Math.floor((to - from) / delta);

      const y1 = new Array(n + 1);
      const y2 = new Array(n + 1);
      const x = new Array(n + 1);

      y1[0] = y0;
      y2[0] = 0;

      for (let i = 1; i <= n; i++) {
         const t = x[i] = from + delta * i;
         const y2Prev = y2[i - 1];
         const f = sigma * Math.sin(w * t) - b1 * y2Prev -
            b2 * y2Prev * Math.abs(y2Prev) - c1 * y1[i - 1] - c3 * Math.pow(y2Prev, 3);
         y2[i] = y2Prev + f * delta;
         y1[i] = y1[i - 1] + y2Prev * delta;
      }

      let sum = 0
      for (let i = 1; i <= n; i++) {
         sum += Math.pow(y1[i] - y1[i - 1], 2);
      }
      const max = Math.max(...y1);
      const rule = Math.sqrt(sum / n / max);

      res.push({ delta, rule })

      if (rule >= epsilon || Number.isNaN(rule)) {
          delta /= 2;
         continue;
      }
         
      console.log(rule);
      return { x, y1, y2 };
   }
}