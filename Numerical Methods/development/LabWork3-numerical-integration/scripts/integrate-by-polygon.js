; (function () {
   
   /**
    * Интегрирует функцию f на интервале [a, b]
    * @param {function} f интегрируемая функция
    * @param {number} a нижная граница интегрирования 
    * @param {number} b верхняя граница интегрирования
    * @param {number} n количество шагов
    * @param {string} method метод интегрирования, возможные значения: 
    * 'left-rectangular' | 'middle-rectangular' | 'right-rectangular' | 'trapezoidal'
    */
   function integrateByPolygonMethods(f, a, b, n, method) {
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

   /**
    * Вычисляет общую часть интеграла функции f
    * @param {function} f интегрируемая функция
    * @param {number} a нижная граница интегрирования
    * @param {number} h шаг интегрирования
    * @param {number} s начальное значение результата
    * @param {number} offset смещение шага интегрирования 
    */
   function getSum(f, a, n, h, s, offset) {

      for (let i = 1; i < n; i++) {
         s += f(a + i * h + offset);
      }

      return s * h;
   }

   window.integrateByPolygonMethods = integrateByPolygonMethods;

}());
