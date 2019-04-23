'use strict'
var FramedButton = require('./framedButton');
var ReactiveBar = require('./reactiveBar');
var ReactiveRichText = require('./reactiveRichText')
var textFunction = require('./textFunctions');

var ActionButton = function (parent, game, x, y, buttonKey, frameKey, barKey, callbacks, percentageFunction, percentageFunctionContext,
    timeFunction, timeFunctionContext, barSignal, totalRechargeSignal, tint,
    frameColorOver = 0, frameColorOut = 0, frameColorDown = 0, frameColorUp = 0, frameColorDisabled = 0,
    overButtonFrame = 0, outButtonFrame = 0, downButtonFrame = 0, upButtonFrame = 0, disabledButtonFrame = 0,
    overFrameFrame = 0, outFrameFrame = 0, downFrameFrame = 0, upFrameFrame = 0, disabledFrameFrame = 0, barFrame = 0) {

    FramedButton.call(this, parent, game,x, y, buttonKey, frameKey, callbacks, 
        frameColorOver, frameColorOut, frameColorDown, frameColorUp, frameColorDisabled,
         overButtonFrame, outButtonFrame, downButtonFrame, upButtonFrame, disabledButtonFrame,
         overFrameFrame, outFrameFrame, downFrameFrame, upFrameFrame, disabledFrameFrame);
    this._button.tint = tint;
    this._bar = this.add(new ReactiveBar(game, parent, 0, 0, barKey, percentageFunction, percentageFunctionContext, barSignal, barFrame));
    this._bar.maskAngle = -90;
    this.moveUp(this._frame);

    this._text = this.add(new ReactiveRichText(game, 1, 2, this._button.width, textFunction.Fun(timeFunction, timeFunctionContext), {
        "font": "Minecraft",
        "fill": "#fff",
        "fontSize": 10,
        "align": "center"
    }, this, [barSignal]));
   
    this._rechargeEvent = totalRechargeSignal?totalRechargeSignal.add( this.activate, this):{};
    this._rechargeEvent.active;
}

ActionButton.prototype = Object.create(FramedButton.prototype);
ActionButton.prototype.constructor = ActionButton;

ActionButton.prototype.deactivate = function() {
    FramedButton.prototype.deactivate.apply(this);
    
}

module.exports = ActionButton;