'use strict';

var RichText = require('./richText.js');

var ReactiveRichText = function (game, x, y, lineWidth, text, style, parent, signals) {
    RichText.call(this, game, x, y, lineWidth, text, style, parent);
    this._signals = []
    for (let i = 0; i < signals.length; i++) {
        signals[i]?this._signals.push(signals[i].add(this.write, this, 0)):null;
    }
    this._signals.forEach(element => {
        this.onDestroy.add(element.detach, element);
    },this);
    this.write();
}

ReactiveRichText.prototype = Object.create(RichText.prototype);
ReactiveRichText.prototype.constructor = ReactiveRichText;

module.exports = ReactiveRichText;