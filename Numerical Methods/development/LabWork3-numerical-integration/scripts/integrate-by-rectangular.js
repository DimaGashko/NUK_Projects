; (function () {
   
   function integrateByRectangular(f, a, b, n, method) {
      if (a > b) [a, b] = [b, a];
      const h = (b - a) / n;

      if (method === 'left-rectangular') {
         return getSum(func, a, n, h, f(a), 0);

      } else if (method === 'middle-rectangular') {
         return getSum(func, a, n, h, f(a + h / 2), h / 2);
     
      } else if (method === 'right-rectangular') {
         return getSum(func, a, n, h, f(b), 0);
     
      } else if (method === 'trapezoidal') {
         return getSum(func, a, n, h, (f(a) + f(b)) / 2, 0);
      }
   }

   function getSum(f, a, n, h, s, offset) {

      for (let i = 1; i < n; i++) {
         s += f(a + i * h + offset);
      }

      return s * h;
   }

   window.integrateByRectangular = integrateByRectangular;

}());

function integrateLeftRectangular(func, from, to, n) { 
   const h = Math.abs((to - from) / n);
   let s = 0;

   for (let i = 0; i < n; i++) {
      s += func(from + h * i);
   }

   s *= h;
   return s;
}

function integrateRightRectangular(func, from, to, n) { 
   const h = Math.abs((to - from) / n);
   let s = 0;

   for (let i = 1; i <= n; i++) {
      s += func(from + h * i);
   }

   s *= h;
   return s;
}

function integrateMiddleRectangular(func, from, to, n) { 
   const h = Math.abs((to - from) / n);
   const offset = h / 2;
   let s = 0;

   for (let i = 0; i < n; i++) {
      s += func(from + h * i + offset);
   }

   s *= h;
   return s;
}

function integrateTrap(func, from, to, n) { 
   const h = Math.abs((to - from) / n);
   let s = 0;

   for (let i = 0; i < n; i++) {
      s += (func(from + h * i) + func(from + h * i + h)) / 2;
   }

   s *= h;
   return s;
}