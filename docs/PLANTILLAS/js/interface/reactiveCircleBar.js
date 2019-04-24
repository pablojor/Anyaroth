'use strict'

var CircleBar = require('./circleBar');

var ReactiveCircleBar = function(game,parent, x, y, radius, angles, colors, alphas, antiClockWise, segments, initialAngle, percentageFunction, functionContext, signal){
    CircleBar.call(this, game,parent, x, y, radius, angles, colors, alphas, antiClockWise, segments, initialAngle);
    this.percentageFunction = percentageFunction.bind(functionContext);
    this._signal = signal?signal.add(this.changePercentage,this,0):null;
    if(this._signal) {
        this.onDestroy.add(this._signal.detach, this._signal);
    }
    ReactiveCircleBar.prototype.changePercentage.call(this);
}

ReactiveCircleBar.prototype = Object.create(CircleBar.prototype);
ReactiveCircleBar.prototype.constructor = ReactiveCircleBar;

ReactiveCircleBar.prototype.changePercentage = function () {
    let p = this.percentageFunction();

    this.percentage = isNaN(p)?100:p;
}

module.exports = ReactiveCircleBar;