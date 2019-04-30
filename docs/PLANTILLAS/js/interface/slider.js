'use strict'

var SliderImage = require('./sliderImage');


var Slider = function (game, parent, x, y, keyContiner, keySlider, height, sliderHeight, offsetSlider) {
    Phaser.Group.call(this, game, parent);
    this.x = x;
    this.y = y;
    this._container = this.add(new SliderImage(game, this, 0, 0, keyContiner, height));
    this._slider = this.add(new SliderImage(game, this, 0, offsetSlider, keySlider, sliderHeight));
    
    this._offset = offsetSlider;
    this._drag = this.add( new Phaser.Image(game, 0, offsetSlider,  keySlider));
    this._drag.height = this._slider.height;
    this._drag.renderable = false;
    this._drag.inputEnabled = true
    this._drag.input.enableDrag();
    this._drag.input.setDragLock(false, true);
    this._drag.events.onDragUpdate.add(function() {
        if(this._drag.y-this._offset <= 0){
            this._drag.y = this._offset;
            this.onBegin.dispatch();
        } else if(this._drag.y-this._offset >= this._container.height - 2 * this._offset - this._slider.height) {
            this._drag.y=this._offset + this._container.height - 2 * this._offset - this._slider.height;
            this.onEnd.dispatch();
        }
        this._slider.x = this._drag.x;
        this._slider.y = this._drag.y;
        this.onChange.dispatch((this._slider.y - this._offset) / (this._container.height - 2 * this._offset - this._slider.height) * 100);
    }, this);
    this.onBegin = new Phaser.Signal();
    this.onEnd = new Phaser.Signal();
    this.onChange = new Phaser.Signal();
}

Slider.prototype = Object.create(Phaser.Group.prototype);
Slider.prototype.constructor = Slider;

Slider.prototype.move = function (movement) {
    this._slider.y += movement * (this._container.height - 2 * this._offset - this._slider.height) / 100;
    if (this._slider.y <= this._container.y) {
        this._drag.y = this._offset;
        this.onBegin.dispatch();
        this._slider.y = this._container.y;
    } else if (this._slider.y >= this._container.y + this._container.height - 2 * this._offset - this._slider.height) {
        this._drag.y=this._offset + this._container.height - 2 * this._offset - this._slider.height;
        this.onEnd.dispatch();
        this._slider.y = this._container.y + this._container.height - 2 * this._offset - this._slider.height;
    }
    this._drag.y = this._slider.y +this._offset;
    this.onChange.dispatch((this._slider.y - this._container.y) / (this._container.height - 2 * this._offset - this._slider.height) * 100);
}

module.exports = Slider;