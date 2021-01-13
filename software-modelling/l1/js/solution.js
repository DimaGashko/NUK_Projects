/** @returns {{ x: number, y: number }[]} */
export function exact({ a, b, h, n }) {
   return Array.from({ length: n + 1 }).map((_, i) => {
      const x = i * h;
      const y = a * (1 - Math.exp(-b * x))
      return { x, y }
   });
}

/** @returns {{ x: number, y: number }[]} */
export function euler({ a, b, h, n }) {
   const res = [{ x: 0, y: 0 }];

   for (let i = 0; i < n; i++) {
      const prev = res[res.length - 1];
      const k = prime(a, b, prev.y);
      const x = h * i;
      const y = prev.y + h * k;
      res.push({ x, y });
   }

   return res;
}

/** @returns {{ x: number, y: number }[]} */
export function rk4({ a, b, h, n }) {
   const res = [{ x: 0, y: 0 }];

   for (let i = 0; i < n; i++) {
      const prev = res[res.length - 1];
      const k1 = prime(a, b, prev.y);
      const k2 = prime(a, b, prev.y + k1 * h / 2);
      const k3 = prime(a, b, prev.y + k2 * h / 2);
      const k4 = prime(a, b, prev.y + k3 * h);
      const k = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
      const x = h * i;
      const y = prev.y + h * k;
      res.push({ x, y });
   }

   return res;
}

function prime(a, b, y) {
   return a * b - b * y;
}