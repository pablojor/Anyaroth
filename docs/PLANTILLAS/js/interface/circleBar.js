'use strict'

var CircleWithSectors = require('./circleWithSectors');

var CircleBar = function (game,parent, x, y, radius, angles, colors, alphas, antiClockWise, segments, initialAngle) {
    Phaser.Group.call(this,game, parent);
    this.x = x;
    this.y = y;
    this._actionCircleBack = this.add(new CircleWithSectors(game,0,0,radius,angles,colors,alphas,antiClockWise, segments));
    this._actionCircleBack.tint = 0xAAAAAA;
    this._actionCircleFront = this.add(new CircleWithSectors(game,0,0,radius,angles,colors,alphas,antiClockWise, segments));
    this._actionCircleFront.mask = this.add(new Phaser.Graphics(game,0,0));
    this._antiClockWise = antiClockWise;
    this._radius = radius;
    this._initialAngle = initialAngle;
    this._percentage = 1;
}

CircleBar.prototype = Object.create(Phaser.Group.prototype);
CircleBar.prototype.constructor = CircleBar;

Object.defineProperty(CircleBar.prototype, 'percentage', {
    get: function () {
        return 100 * this._percentage;
    },
    set: function (value) {
        value = value / 100;
        this._percentage = value;
        this._actionCircleFront.mask.clear();
        this._actionCircleFront.mask.beginFill(0xffffff);
        let second = this._initialAngle + value*Math.PI*2;
        this._actionCircleFront.mask.arc(0,0,this._radius,second,this._initialAngle,this._antiClockWise);
        if(value<0.5){
            this._actionCircleFront.mask.drawPolygon([0,0,
                this._radius * Math.cos(second), this._radius * Math.sin(second),
                this._radius * Math.cos(this._initialAngle), this._radius * Math.sin(this._initialAngle)]);
        }
        this._actionCircleFront.mask.endFill();

    }
});

module.exports = CircleBar;