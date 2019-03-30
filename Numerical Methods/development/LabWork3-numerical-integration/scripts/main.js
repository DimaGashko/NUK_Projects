;(function(){

   const form = document.querySelector(".setup_form");

   initEvents();

   function calculate() { 
      const func = getFunction();
      const precision = parseFloat(form.precision.value);
      const from = parseFloat(form.from.value);
      const to = parseFloat(form.to.value);
      const method = form.method.value;

      let res;

      try {
         res = integrate(func, from, to, method, precision);

      } catch (err) { 
         if (!(err instanceof SyntaxError)) return;
         printCalcError();
         throw err;
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