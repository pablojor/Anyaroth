'use strict'

var StatMarker = function(game, parent, x, y, xSpace, maxPoints, currentPoints, pointKey, emptyKey, color) {
    Phaser.Group.call(this, game, parent);
    this.x = x;
    this.y = y;
    let width = new Phaser.Image(game, 0, 0, pointKey).width;//.width;
    this._points = [];
    for(let i = 0; i < currentPoints; i++) {
        this._points.push(this.add(new Phaser.Image(game, i*(width+xSpace), 0, pointKey)));
        this._points[i].tint = color;
    }
    for(let i = currentPoints; i<maxPoints; i++) {
        this._points.push(this.add(new Phaser.Image(game, i*(width+xSpace), 0, emptyKey)));
    }
    this._emptyKey = emptyKey;
    this._pointKey = pointKey;
    this._currentPoints = currentPoints;
    this._maxPoints = maxPoints;
    this._color = color;
}

StatMarker.prototype = Object.create(Phaser.Group.prototype);
StatMarker.prototype.constructor = StatMarker;

Object.defineProperty(StatMarker.prototype, 'currentPoints', {
    get: function () {
        return this._currentPoints;
    },
    set: function (value) {
        if(value!==this._currentPoints) {
            this._currentPoints = value;
            for(let i = 0; i < this._currentPoints; i++) {
                this._points[i].loadTexture(this._pointKey);
                this._points[i].tint = this._color;
            }
            for(let i = this._currentPoints; i < this._maxPoints; i++) {
                this._points[i].loadTexture(this._emptyKey);
                this._points[i].tint = 0xFFFFFF;
            }
        }
    }
});
module.exports = StatMarker;