;(function () {
   
   /**
    * Интегрирует функцию f на интервале [a, b] методом Симпсона
    * @param {(x: number) => number} f интегрируемая функция
    * @param {number} a нижная граница интегрирования 
    * @param {number} b верхняя граница интегрирования
    * @param {number} n количество шагов
    */
   function integrateBySimpson(f, a, b, n) {
      if (a > b) [a, b] = [b, a];
      const h = (b - a) / (2 * n);
      let s = f(a) + f(b);
      let k = 1;

      for (let i = 1; i <= 2 * n - 1; i++) {
         s += f(a + h * i) * (3 + k);
         k = -k;
      }

      return Math.abs((h / 3) * s);
   }

   window.integrateBySimpson = integrateBySimpson;

}());