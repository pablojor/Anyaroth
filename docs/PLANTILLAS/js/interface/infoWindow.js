'use strict'

var WindowFrame = require('./windowFrame');
var ScrollText = require('./scrollText');
var RichText = require('./richText');

var InfoWindow = function(parent, game, x, y, width, height, windowKey,  text, style) {
    Phaser.Group.call(this, game, parent);
    this.x = x;
    this.y = y;
    this._window = this.add(new WindowFrame(game,this,0,0,width,height,windowKey));
    this._text = this.add(new ScrollText(game, this, 1.5 *this._window._tileWidth, this._window._tileHeight,
        width - 4 * this._window._tileWidth, height - 2 * this._window._tileHeight,
        text, style));
}

InfoWindow.prototype = Object.create(Phaser.Group.prototype);
InfoWindow.prototype.constructor = InfoWindow;

module.exports = InfoWindow;