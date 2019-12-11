import './differential.sass';

export default class Model {
    a = 0.6;
    b = 2.6;
    h = 0.2;
    first = 3.4;

    eylerDifferential() {
        const nodes = this.getNodes();
        const res = [];

        let prev = this.first;

        for (let i = 1; i < nodes.length; i++) {
            const next = prev + this.h * this.primeF(nodes[i - 1], prev);

            res.push({
                x: nodes[i - 1],
                y: next,
            });

            prev = next;
        }

        return res;
    }

    primeF(x, y) {
        return 4.1 * x - y * y + 0.6;
    }

    getNodes() {
        const steps = (this.b - this.a) / this.h + 1;
        const nodes = new Array(steps);
        const x0 = this.a;

        for (let i = 0; i < steps; i++) {
            nodes[i] = x0 + i * this.h;
        }

        return nodes;
    }

}