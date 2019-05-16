export default class Events {
    /** @private */
    _handlers = {};

    constructor() {

    }

    addListener(type, handler) {
        this._handlers[type] = this._handlers[type] || [];
        this._handlers[type].push(handler);

        return handler;
    }

    removeListener(type, handler) {
        if (!this._handlers[type]) return;

        this._handlers[type] = this._handlers[type]
            .filter(item => item != handler);
    }

    /**
     * Call the event
     * @param {string} type
     * @param  {...any} params  
     */
    emit(type, ...params) {
        if (!this._handlers[type]) return;

        this._handlers[type].forEach((handler) => {
            handler(...params);
        });
    }


}