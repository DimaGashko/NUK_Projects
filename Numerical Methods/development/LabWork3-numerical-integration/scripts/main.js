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
      return (x) => { 
         const strFunc = form.func.value.replace(/x/gi, '' + x);
         return parseEquation(strFunc);
      };
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