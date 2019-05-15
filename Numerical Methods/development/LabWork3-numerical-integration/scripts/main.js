;(function(){

   const els = {
      form: document.querySelector(".setup_form"),
      results: document.querySelector(".results-text"),
   }

   initEvents();

   function calculate() { 
      const func = getFunction();
      window.func = func;
      const precision = parseFloat(els.form.precision.value);
      const from = parseFloat(els.form.from.value);
      const to = parseFloat(els.form.to.value);
      const method = els.form.method.value;

      let res;
      
      try {
         res = integrate(func, from, to, method, precision);

      } catch (err) { 
         if (!(err instanceof SyntaxError)) return;
         printCalcError();
         throw err;
      }

      printResults(res, precision);
   }

   /**
    * @param {{n: number, val: number}[]} res 
    */
   function printResults(res, precision) { 
      console.log(res);
      
      const digits = Math.abs(Math.floor(Math.log10(precision)));
      
      const strRes = res.reverse()
         .map((item) => `I = ${item.val.toFixed(digits)}  n = ${item.n}`)
         .join('<br>');
      
      els.results.innerHTML = strRes;
   }

   function getFunction() {
      const strFunc = els.form.func.value;

      return (x) => { 
         return parseEquation(strFunc.replace(/x/gi, '' + x));
      };
   }

   function printCalcError() {
      console.log("Error");
   }

   function initEvents() { 
      els.form.addEventListener('submit', (event) => {
         event.preventDefault();

         calculate();         
      });
   }

}());