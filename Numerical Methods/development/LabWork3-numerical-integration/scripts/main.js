;(function(){

   const form = document.querySelector(".setup_form");

   initEvents();

   function calculate() { 
      const func = getFunction();
      window.func = func;
      const precision = parseFloat(form.precision.value);
      const from = parseFloat(form.from.value);
      const to = parseFloat(form.to.value);
      const method = form.method.value;

      let res;

      switch (method) { 
         case 'simpson':
            res = integrateBySimpson(func, from, to, precision);
            break;
         case 'trapezoidal':
            res = integrateByTrapezoidal(func, from, to, precision);
            break;
         case 'middle-rectangular':
         case 'right-rectangular':
         case 'left-rectangular':            
            res = integrateByRectangular(func, from, to, precision, method);
            break;
         default:
            printCalcError();
      }

      if (!res) {
         console.log(res);
         
         printCalcError();
         return;
      }

      console.log(res);
   }

   function getFunction() { 
      const srtFunc = form.func.value;
      const func = new Function('x', `return ${srtFunc}`);

      return func;
   }

   function printCalcError() {
      console.log("Error");
      
   }

   function initEvents() { 
      form.addEventListener('submit', (event) => {
         event.preventDefault();

         calculate();         
      });
   }

}());