;(function () { 

   /**
    * Интегрирует функцию до точности precision
    * @param {'left-rect'|'middle-rect'|'right-rect'|'trapezoidal'|'simpson'} method метод интегрирования
    * @param {(x: number) => number} func интегрируемая функция
    * @param {number} a нижняя граница интегрирования
    * @param {number} b верхняя граница интегрирования
    * @param {number} precision точность вычисления
    * @returns {{n: number, val: number}[]} массив значение всех итераций
    * интегрирования(значения указаны в порядке возрастания 
    * точности - наибольшая точно в последнем элементе)
    */
   function integrate(method, func, a, b, precision) { 
      

   }

   windows.integrate = integrate;

}());