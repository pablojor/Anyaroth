'use strict'

var SliderImage = function(game, parent, x, y, key, height) {
    Phaser.Group.call(this, game, parent);
    this.x = x;
    this.y = y;

    this._upImage = this.add(new Phaser.Image(game,0,0,key,0));
    this._tileHeight = this._upImage.height;
    this._downImage = this.add(new Phaser.Image(game,0,height-this._tileHeight,key,2));
    this._middleImage = this.add(new Phaser.Image(game, 0, this._tileHeight,key,1));
    this._middleImage.height = height - 2*this._tileHeight;
}

SliderImage.prototype = Object.create(Phaser.Group.prototype);
SliderImage.prototype.constructor = SliderImage;

module.exports = SliderImage;