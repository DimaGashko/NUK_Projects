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