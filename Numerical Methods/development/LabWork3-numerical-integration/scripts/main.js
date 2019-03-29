;(function(){

   var els = {
      form: document.querySelector(".setup_form"),
   }

   initEvents();

   function calculate() { 
      
   }

   function initEvents() { 
      els.form.addEventListener('submit', (event) => {
         event.preventDefault();

         calculate();         
      });
   }

}());