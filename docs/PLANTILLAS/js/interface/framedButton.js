


//callBack ={function, context, arguments}

var FramedButton = function (parent, game, x, y, buttonKey, frameKey, callbacks,
    frameColorOver, frameColorOut, frameColorDown, frameColorUp, frameColorDisabled,
    overButtonFrame = 0, outButtonFrame = 0, downButtonFrame = 0, upButtonFrame = 0, disabledButtonFrame = 0,
    overFrameFrame = 0, outFrameFrame = 0, downFrameFrame = 0, upFrameFrame = 0, disabledFrameFrame = 0) {

    Phaser.Group.call(this, game, parent);
    this.x = x;
    this.y = y;

    this._frame = this.add(new Phaser.Image(game, 0, 0, frameKey));

    this._button = this.add(new Phaser.Button(game, 0, 0, buttonKey, function () { }, null, overButtonFrame, outButtonFrame, downButtonFrame, upButtonFrame));
    
    this._pressed = false;

    this._callbacks = callbacks;

    this._disabledButtonFrame = disabledButtonFrame;

    this._frameColorOver = frameColorOver;
    this._frameColorOut = frameColorOut;
    this._frameColorDown = frameColorDown;
    this._frameColorDisabled = frameColorDisabled;
    this._overFrameFrame = overFrameFrame;
    this._outFrameFrame = outFrameFrame;
    this._downFrameFrame = downFrameFrame;
    this._upFrameFrame = upFrameFrame;
    this._frameColorUp = frameColorUp;
    this._disabledFrameFrame = disabledFrameFrame;

    this.onInputDown = new Phaser.Signal();
    this.onInputOut = new Phaser.Signal();
    this.onInputOver = new Phaser.Signal();
    this.onInputUp = new Phaser.Signal();
    this.onInputDisable = new Phaser.Signal();

    this._button.onInputDown.add(this._down, this);
    this._button.onInputOut.add(this._out, this);
    this._button.onInputOver.add(this._over, this);
    
    this._button.onInputUp.add(this._up, this);

    this._button.input.useHandCursor = false;
    this.activate();

}


FramedButton.prototype = Object.create(Phaser.Group.prototype);
FramedButton.prototype.constructor = FramedButton;

FramedButton.prototype._down = function () {
    if (this._button.input.enabled) {
        this.changeFrameFrame('Down');
        this._pressed = true;
        this.onInputDown.dispatch();
    }
}

FramedButton.prototype._out = function () {
    if (this._button.input.enabled) {
        if (!this._pressed) {
            this.changeFrameFrame( 'Out');
        }
        this.onInputOut.dispatch();
    }
}

FramedButton.prototype._over = function () {
    if (this._button.input.enabled) {
        if (!this._pressed) {
            this.changeFrameFrame( 'Over');
        }
        this.onInputOver.dispatch();
    }
}

FramedButton.prototype._up = function () {
    if (this._button.input.enabled) {
        this.changeFrameFrame( 'Up');
        if (this._button.input.checkPointerOver(this.game.input.activePointer)) {
            this.changeFrameFrame( 'Over');
            this._do();
            this.onInputUp.dispatch(true);
        } else {
            this.changeFrameFrame( 'Out');
            this.onInputUp.dispatch(false);
        }
        this._pressed = false;
        
    }
}

FramedButton.prototype._do = function () {
    if (this._pressed) {
        this._callbacks.forEach(function (callback) {
            callback.callback.call(callback.context, ...callback.arguments);
        }, this);
    }
}

FramedButton.prototype.activate = function () {
    this._button.input.enabled = true;
    if (this._button.input.checkPointerOver(this.game.input.activePointer)) {
        this.changeFrameFrame('Over');
    } else {
        this.changeFrameFrame( 'Out');
    }
}

FramedButton.prototype.deactivate = function () {
    this.changeFrameFrame('Disabled');
    this._button.input.enabled = false;
    if (typeof this._disabledButtonFrame === 'number') {
        this._button.frame = this._disabledButtonFrame;
    } else {
        this._button.frameName = this._disabledButtonFrame;
    }
    this.onInputDisable.dispatch();
}

FramedButton.prototype.changeFrameFrame = function (frame) {

    this._frame.tint = this['_frameColor' + frame];
    frame = this['_' + frame.toLowerCase() + 'FrameFrame'];
    if (typeof frame === 'number') {
        this._frame.frame = frame;
    } else {
        this._frame.frameName = frame;
    }
}

module.exports = FramedButton;