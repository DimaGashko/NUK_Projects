const RAND_MAX = 32767;
let next = Date.now();

export function lcg() {
   next = (1103515245 * next + 12345) % 2**31;
   return next;
}

export function setSeed(seed) {
   next = seed;
}

export function lcg2() {
   next = (1103515245 * next + 12345) % 2**31;
   return (next / 2**16) % (RAND_MAX + 1);
}