import { expect } from 'chai';
import Events from './Events';

describe('Events', () => {

    it('addListener', () => {
        const events = new Events();
        let res = false;

        events.addListener('my-event', () => res = true);
        events.emit('my-event');

        expect(res).equal(true);
    });

    it('removeListener', () => {
        const events = new Events();
        let res = true;

        const listener1 = events.addListener('my-event', () => res = false);
        const listener2 = events.addListener('my-event', () => res = false);

        events.removeListener('my-event', listener1);
        events.removeListener('my-event', listener2);

        events.emit('my-event');

        expect(res).equal(true);
    });

    it('Event Params', () => {
        const events = new Events();

        events.addListener('my-event', (...params) => {
            expect(params).to.have.members([1, 2, 3]);
        });

        events.emit('my-event', 1, 2, 3);
    });

    it('Inherits', () => {
        class A extends Events {
            name = 'Name';

            setName(name) {
                this.name = name;
                this.emit('change-name', this.name);
            }
        }

        const a = new A();

        a.addListener('change-name', (newName) => {
            expect(newName).equal('Admin');
        });

        a.setName('Admin');
    });

});