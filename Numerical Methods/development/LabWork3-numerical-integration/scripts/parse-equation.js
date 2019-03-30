//+ Jonas Raoni Soares Silva
//Mathematical expression parser using reverse polish notation and binary tree. 
//Created: 2005.10.07
//@ http://jsfromhell.com/classes/math-processor [rev. #1]

// Rewrite by Dmitry Gashko <https://github.com/DimaGashko> 2019.03.30
// (I've done everything I can)

/**
 * Mathematical expression parser using reverse polish notation and binary tree
 * @example 
 * 
 * parseEquation("2+3*2^3"); // 26
 */
const parseEquation = (function () {
   const o = {
      "+": (a, b) => (a + b),
      "-": (a, b) => (a - b),
      "%": (a, b) => (a % b),
      "/": (a, b) => (a / b),
      "*": (a, b) => (a * b),
      "^": (a, b) => (Math.pow(a, b)),
   };
   const s = { "^": 3, "*": 2, "/": 2, "%": 1, "+": 0, "-": 0 };
   const u = { "+": 1, "-": -1 };
   const p = { "(": 1, ")": -1 };

   const methods = {
      div: (a, b) => (Math.floor(a / b)),
      sin: Math.sin, cos: Math.cos,
      sqrt: Math.sqrt, cbrt: Math.cbrt,
      max: Math.max, min: Math.min,
      abs: Math.abs, tan: Math.tan,
      e: Math.exp, lg: Math.log10,
   };

   function parse(e) {
      for (var n, x, _o = [], s = [x = RPN(e.replace(/[\s]+/g, "").split(""))]; s.length;)
         for ((n = s[s.length - 1], --s.length); n[2]; _o[_o.length] = n, s[s.length] = n[3], n = n[2]);
      for (; (n = _o.pop()) != undefined; n[0] = o[n[0]](isNaN(n[2][0]) ? f(n[2][0]) : n[2][0], isNaN(n[3][0]) ? f(n[3][0]) : n[3][0]));
      return +x[0];
   };

   function RPN(e) {
      var x, r, c = r = [, , , 0];
      if (e[0] in u || !e.unshift("+"))
         for (; e[1] in u; e[0] = u[e.shift()] * u[e[0]] + 1 ? "+" : "-");
      (c[3] = [u[e.shift()], c, , 0])[1][0] = "*", (r = [, , c, 0])[2][1] = r;
      (c[2] = v(e))[1] = c;
      (!e.length && (r = c)) || (e[0] in s && ((c = r)[0] = e.shift(), !e.length && error()));
      while (e.length) {
         if (e[0] in u) {
            for (; e[1] in u; e[0] = u[e.shift()] * u[e[0]] + 1 ? "+" : "-");
            (c = c[3] = ["*", c, , 0])[2] = [-1, c, , 0];
         }
         (c[3] = v(e))[1] = c;
         e[0] in s && (c = s[e[0]] > s[c[0]] ?
            ((c[3] = (x = c[3], c[2]))[1][2] = [e.shift(), c, x, 0])[2][1] = c[2]
            : r == c ? (r = [e.shift(), , c, 0])[2][1] = r
               : ((r[2] = (x = r[2], [e.shift(), r, , 0]))[2] = x)[1] = r[2]);
      }
      return r;
   };
   function v(e) {
      var i, j, l;
      if ("0123456789.".indexOf(e[0]) + 1) {
         for (i = -1, l = e.length; ++i < l && "0123456789.".indexOf(e[i]) + 1;);
         return [+e.splice(0, i).join(""), , , 0];
      }
      else if (e[0] == "(") {
         for (i = 0, l = e.length, j = 1; ++i < l && (e[i] in p && (j += p[e[i]]), j););
         return RPN(l = e.splice(0, i), l.shift(), !j && e.shift());
      }
      else {
         if (((j = e[0].toLowerCase()) >= "a" && j <= "z") || j == "_") {
            for (i = 0; ((j = e[++i].toLowerCase()) >= "a" && j <= "z") || j == "_" || (j >= 0 && j <= 9););
            if (j == "(") {
               for (var l = e.length, j = 1; ++i < l && (e[i] in p && (j += p[e[i]]), j););
               return [e.splice(0, i + 1).join(""), , , 0];
            }
         }
      }
      error();
   };
   function f(e) {
      var n, i = 0;
      if (((e = e.split(""))[i] >= "a" && e[i] <= "z") || e[i] == "_") {
         while ((e[++i] >= "a" && e[i] <= "z") || e[i] == "_" || (e[i] >= 0 && e[i] <= 9));
         if (e[i] == "(") {
            !methods[n = e.splice(0, i).join("")] && error("Fun??o \"" + n + "\" n?o encontrada"), e.shift();
            for (var a = [], i = -1, j = 1; e[++i] && (e[i] in p && (j += p[e[i]]), j);)
               j == 1 && e[i] == "," && (a.push(parse(e.splice(0, i).join(""))), e.shift(), i = -1);
            a.push(parse(e.splice(0, i).join(""))), !j && e.shift();
         }

         return methods[n](...a);
      }
   };
   function error(s) {
      throw new Error("MathProcessor: " + (s || "Error in expression"));
   };

   return parse;
}());