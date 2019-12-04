; (function () {
   
   /**
    * Интегрирует функцию f на интервале [a, b]
    * @param {(x: number) => number} f интегрируемая функция
    * @param {number} a нижная граница интегрирования 
    * @param {number} b верхняя граница интегрирования
    * @param {number} n количество шагов
    * @param {'left-rect'|'middle-rect'|'right-rect'|'trapezoidal'} method метод интегрирования
    */
   function integrateByPolygon(f, a, b, n, method) {
      if (a > b) [a, b] = [b, a];
      const h = (b - a) / n;

      if (method === 'left-rect') {
         return getSum(f, a, n, h, f(a), 0);

      } else if (method === 'middle-rect') {
         return getSum(f, a, n, h, f(a + h / 2), h / 2);
     
      } else if (method === 'right-rect') {
         return getSum(f, a, n, h, f(b), 0);
     
      } else if (method === 'trapezoidal') {
         return getSum(f, a, n, h, (f(a) + f(b)) / 2, 0);
      
      } else {
         throw SyntaxError(`Wrong integration method (${method})`);
      }
   }

   /**
    * Вычисляет общую часть интеграла функции f
    * @param {(x: number) => number} f интегрируемая функция
    * @param {number} a нижная граница интегрирования
    * @param {number} h шаг интегрирования
    * @param {number} s начальное значение результата
    * @param {number} offset смещение шага интегрирования 
    */
   function getSum(f, a, n, h, s, offset) {

      for (let i = 1; i < n; i++) {
         s += f(a + i * h + offset);
      }

      return Math.abs(s * h);
   }

   window.integrateByPolygon = integrateByPolygon;

}());
