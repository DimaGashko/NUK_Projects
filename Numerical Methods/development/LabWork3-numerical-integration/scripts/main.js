;(function(){

   const form = document.querySelector(".setup_form");

   //initEvents();

   function calculate() { 
      const func = form.func.value;
      const precision = parseFloat(form.precision.value);
      const from = parseFloat(form.from.value);
      const to = parseFloat(form.to.value);
      const method = form.method.value;

      switch (method) { 
         case 'simpson':
            integrateBySimpson(func, from, to, precision);
            break;
         case 'trapezoidal':
            integrateByTrapezoidal(func, from, to, precision);
            break;
         case 'middle-rectangular':
         case 'right-rectangular':
         case 'left-rectangular':
            integrateByRectangular(func, from, to, precision, method);
            break;
         default:
            printCalcError();
      }
   }

   function printCalcError() {

   }

   function initEvents() { 
      form.addEventListener('submit', (event) => {
         event.preventDefault();

         calculate();         
      });
   }

}());