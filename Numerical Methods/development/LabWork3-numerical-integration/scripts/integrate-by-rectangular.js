; (function () {
   
   function integrateByRectangular(func, from, to, precision, method) {
      const n = 10000;
      const h = (to - from) / n;

      if (method === "left-rectangular") {
         return getSum(func, from, from, h, func(a)) * h;

      } else if (method === "right-rectangular") {
         return getSum(func, from, n, h, func(b)) * h;
     
      } else if (method === "middle-rectangular") {
         return getSum(func, from, n, h, (func(from), func(to)) / 2) * h;
      }
   }

   function getSum(func, a, n, h, s) { 
      for (let i = 1; i <= n - 1; i++) {
         s += func(a + i * h);
      }

      return s;
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