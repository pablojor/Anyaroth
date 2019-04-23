'use strict'

var Bar = require('./bar.js');

var ReactiveBar = function (game, parent, x, y, key, percentageFunction, functionContext, signal, frame = null) {
    Bar.call(this, game, parent, x, y, key, frame);
    this.percentageFunction = percentageFunction.bind(functionContext);
    this._signal = signal?signal.add(this.changePercentage, this, 0):null;
    if(this._signal){
        this.onDestroy.add(this._signal.detach, this._signal);
    }
    ReactiveBar.prototype.changePercentage.call(this);
}

ReactiveBar.prototype = Object.create(Bar.prototype);
ReactiveBar.prototype.constructor = ReactiveBar;

ReactiveBar.prototype.changePercentage = function () {
    let p = this.percentageFunction();

    this.percentage = isNaN(p)?100:p;
}

module.exports = ReactiveBar;