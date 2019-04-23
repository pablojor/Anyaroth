'use strict'


var createLeftUpCorner = function(game, width, height, key) {
    this._leftUpCorner = this.add(new Phaser.Sprite(game, 0, 0, key, 0));
    this._tileHeight = this._leftUpCorner.height;
    this._tileWidth = this._leftUpCorner.width;

    this._leftUpCornerRight = this.add(new Phaser.Sprite(game, this._tileWidth, 0, key, 1));
    this._leftUpCornerDown = this.add(new Phaser.Sprite(game, 0, this._tileHeight, key, 5));
    this._leftUpCornerRightDown = this.add(new Phaser.Sprite(game, this._tileWidth, this._tileHeight, key, 6));
}

var createLeftDownCorner = function(game, width, height, key) {
    this._leftDownCorner = this.add(new Phaser.Sprite(game, 0, height - this._tileHeight, key, 20));
    this._leftDownCornerUp = this.add(new Phaser.Sprite(game, 0, height - 2 * this._tileHeight, key, 15));;
    this._leftDownCornerRight = this.add(new Phaser.Sprite(game, this._tileWidth, height - this._tileHeight, key, 21));;
    this._leftDownCornerUpRight = this.add(new Phaser.Sprite(game, this._tileWidth, height - 2 * this._tileHeight, key, 16));;
}

var createRighttUpCorner = function(game, width, height, key) {
    this._rightUpCorner = this.add(new Phaser.Sprite(game, width - this._tileWidth, 0, key, 4));
    this._rightUpCornerDown = this.add(new Phaser.Sprite(game, width - this._tileWidth, this._tileHeight, key, 9));
    this._rightUpCornerLeft = this.add(new Phaser.Sprite(game, width - 2 * this._tileWidth, 0, key, 3));
    this._rightUpCornerDownLeft = this.add(new Phaser.Sprite(game, width - 2 * this._tileWidth, this._tileHeight, key, 8));
}

var createRightDownCorner = function(game, width, height, key) {
    this._rightDownCorner = this.add(new Phaser.Sprite(game, width - this._tileWidth, height - this._tileHeight, key, 24));
    this._rightDownCornerUp = this.add(new Phaser.Sprite(game, width - this._tileWidth, height - 2 * this._tileHeight, key, 19));
    this._rightDownCornerLeft = this.add(new Phaser.Sprite(game, width - 2 * this._tileWidth, height - this._tileHeight, key, 23));
    this._rightDownCornerUpLeft = this.add(new Phaser.Sprite(game, width - 2 * this._tileWidth, height - 2 * this._tileHeight, key, 18));
}

var createCorners = function(game, width, height, key) {
    createLeftUpCorner.call(this, game, width, height, key);
    createLeftDownCorner.call(this, game, width, height, key);
    createRighttUpCorner.call(this, game, width, height, key);
    createRightDownCorner.call(this, game, width, height, key);
}

var createUpEdge = function(game, width, height, key) {
    this._upEdge = this.add(new Phaser.Sprite(game, 2 * this._tileWidth, 0, key, 2));
    this._upEdge.width = width - 4 * this._tileWidth;
    this._upEdgeDown = this.add(new Phaser.Sprite(game, 2 * this._tileWidth, this._tileHeight, key, 7));
    this._upEdgeDown.width = this._upEdge.width;

}

var createLeftEdge = function(game, width, height, key) {
    this._leftEdge = this.add(new Phaser.Sprite(game, 0, 2 * this._tileHeight, key, 10));
    this._leftEdge.height = height - 4 * this._tileHeight;
    this._leftEdgeRight = this.add(new Phaser.Sprite(game, this._tileWidth, 2 * this._tileHeight, key, 11));
    this._leftEdgeRight.height = this._leftEdge.height;
}

var createDownEdge = function(game, width, height, key) {
    this._downEdge = this.add(new Phaser.Sprite(game, 2 * this._tileWidth, height - this._tileHeight, key, 22));
    this._downEdge.width = this._upEdge.width;
    this._downEdgeUp = this.add(new Phaser.Sprite(game, 2 * this._tileWidth, height - 2 * this._tileHeight, key, 17));
    this._downEdgeUp.width = this._downEdge.width;
    
}

var createRightEdge = function(game, width, height, key) {
    this._rightEdge = this.add(new Phaser.Sprite(game, width - this._tileWidth, 2 * this._tileHeight, key, 14));
    this._rightEdge.height = this._leftEdge.height;
    this._rightEdgeLeft = this.add(new Phaser.Sprite(game, width - 2 * this._tileWidth, 2 * this._tileHeight, key, 13));
    this._rightEdgeLeft.height = this._rightEdge.height;
}

var createEdges = function(game, width, height, key) {
    createUpEdge.call(this, game, width, height, key);
    createLeftEdge.call(this, game, width, height, key);
    createDownEdge.call(this, game, width, height, key);
    createRightEdge.call(this, game, width, height, key);
}

var createFill = function(game, width, height, key) {
    this._fill = this.add(new Phaser.Sprite(game, 2 * this._tileWidth, 2 * this._tileHeight, key, 12));
    this._fill.width = this._upEdge.width;
    this._fill.height = this._leftEdge.height;
}

var WindowFrame = function(game, parent, x, y, width, height, key) {
    Phaser.Group.call(this, game, parent);
    this.x = x;
    this.y = y;
    createCorners.call(this, game, width, height, key);
    createEdges.call(this, game, width, height, key);
    createFill.call(this, game, width, height, key);
}

WindowFrame.prototype = Object.create(Phaser.Group.prototype);
WindowFrame.prototype.constructor = WindowFrame;


// YA SE HARA.
WindowFrame.prototype.resize = function(width, height) {

}

module.exports = WindowFrame;