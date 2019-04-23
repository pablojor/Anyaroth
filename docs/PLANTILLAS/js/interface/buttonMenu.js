'use strict';

var FramedButton = require('./framedButton');


var ButtonMenu = function (parent, game, name, x, y, buttonKey, frameKey, callbacks,
    frameColorOver, frameColorOut, frameColorDown, frameColorUp, frameColorDisabled,
    overButtonFrame = 0, outButtonFrame = 0, downButtonFrame = 0, upButtonFrame = 0, disabledButtonFrame = 0,
    overFrameFrame = 0, outFrameFrame = 0, downFrameFrame = 0, upFrameFrame = 0, disabledFrameFrame = 0) {
    FramedButton.call(this, parent, game, x, y, buttonKey, frameKey, callbacks,
        frameColorOver, frameColorOut, frameColorDown, frameColorUp, frameColorDisabled,
        overButtonFrame, outButtonFrame, downButtonFrame, upButtonFrame, disabledButtonFrame,
        overFrameFrame, outFrameFrame, downFrameFrame, upFrameFrame, disabledFrameFrame);
    this.name = name;
    this.leftButton = null;
    this.rightButton = null;
    this.upButton = null;
    this.downButton = null;
}

ButtonMenu.prototype = Object.create(FramedButton.prototype);
ButtonMenu.prototype.constructor = ButtonMenu;

ButtonMenu.prototype.goLeft = function() { return this.left; }
ButtonMenu.prototype.goRight = function() { return this.right; }
ButtonMenu.prototype.goUp = function() { return this.up; }
ButtonMenu.prototype.goDown = function() { return this.down; }

ButtonMenu.prototype.select = function() {
    this.onInputDown.dispatch();
}

module.exports = ButtonMenu;
