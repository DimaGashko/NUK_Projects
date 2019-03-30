;(function () { 

   /**
    * Интегрирует функцию до точности precision
    * @param {(x: number) => number} f интегрируемая функция
    * @param {number} a нижняя граница интегрирования
    * @param {number} b верхняя граница интегрирования
    * @param {'left-rect'|'middle-rect'|'right-rect'|'trapezoidal'|'simpson'} method метод интегрирования
    * @param {number} precision точность вычисления
    * @returns {{n: number, val: number}[]} массив значение всех итераций
    * интегрирования(значения указаны в порядке возрастания 
    * точности - наибольшая точно в последнем элементе)
    */
   function integrate(f, a, b, method, precision = 0.00001) { 
      const res = [];

      let n = 2;
      let prev = getNextValue(f, a, b, n, method);

      return res;
   }

   /**
    * Интегрирует функцию f на интервале [a, b] 
    * по методу method, и количеству разбиения n
    * @param {(x: number) => number} f интегрируемая функция
    * @param {number} a нижняя граница интегрирования
    * @param {number} b верхняя граница интегрирования
    * @param {'left-rect'|'middle-rect'|'right-rect'|'trapezoidal'|'simpson'} method метод интегрирования
    * @param {number} precision точность вычисления
    * @returns {{n: number, val: number}[]} массив значение всех итераций
    * интегрирования(значения указаны в порядке возрастания 
    * точности - наибольшая точно в последнем элементе)
    */
   function getNextValue(f, a, b, n, method) { 
      return (method === 'simpson') ?
         integrateBySimpson(f, a, b, n) :
         integrateByPolygon(f, a, b, n, method);
   }

   window.integrate = integrate;

}());