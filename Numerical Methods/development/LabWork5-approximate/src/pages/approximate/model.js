
export default class Model {
    data = {
        xs: [1, 2, 3, 4, 5, 6, 7, 8, 9],
        ys: [42.78, 10.27, 4.58, 3.78, 3.05, 2.88, 2.45, 2.34, 2.15],
        equation: '(44.59316 / X) - 5.76363',
    }
    
    approximate() { 
        return this.data.xs.map((x) => { 
            return {
                x, y: (44.59316 / x) - 5.76363,
            }
        });
    }
    
}