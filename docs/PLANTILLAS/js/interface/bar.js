'use strict'

var Bar = function (game, parent, x, y, key, frame = null) {
    Phaser.Group.call(this, game, parent);
    this.x = x;
    this.y = y;
    this.bar = this.add(new Phaser.Sprite(game, 0, 0, key, frame));
    this.mask = this.add(new Phaser.Graphics(game, 0, 0));
    this.bar.mask = this.mask;
    this.mask.beginFill(0xffffff);
    this.mask.drawRect(0, 0, this.bar.width, this.bar.height);
    this.maxWidth = this.bar.width;
    this.maxHeight = this.bar.height;
    this._percentage = 1;
    this._maskAngle = 0;
}

Bar.prototype = Object.create(Phaser.Group.prototype);
Bar.prototype.constructor = Bar;

Object.defineProperty(Bar.prototype, 'percentage', {
    get: function () {
        return 100 * this._percentage;
    },
    set: function (value) {
        value = value / 100;
        this._percentage = value;
        this.mask.clear();
        this.mask.beginFill(0xffffff);
        this.mask.drawRect(0, 0, Math.round(this.bar.width * value), this.bar.height);

    }
});

Object.defineProperty(Bar.prototype, 'angle', {
    get: function () {
        return this.bar.angle;
    },
    set: function (value) {
        this.bar.angle = value;
        this.mask.angle = value + this._maskAngle;
        this.mask.y = this.bar.y + this.bar.height / 2 - Math.sqrt(this.bar.width * this.bar.width +
            this.bar.height * this.bar.height) / 2 * Math.cos((this._maskAngle - 45) * Math.PI / 180);
        this.mask.x = this.bar.x + this.bar.width / 2 + Math.sqrt(this.bar.width * this.bar.width +
            this.bar.height * this.bar.height) / 2 * Math.sin((this._maskAngle - 45) * Math.PI / 180);
    }
});

Object.defineProperty(Bar.prototype, 'maskAngle', {
    get: function () {
        return this._maskAngle;
    },
    set: function (value) {
        this._maskAngle = value;
        this.angle = this.angle;
    }
});

Object.defineProperty(Bar.prototype, 'width', {
    get: function () {
        return this.bar.width;
    },
    set: function (value) {
        this.bar.width = value;
        this.percentage = this._percentage;
    }
});

Object.defineProperty(Bar.prototype, 'height', {
    get: function () {
        return this.bar.height;
    },
    set: function (value) {
        this.bar.height = value;
        this.percentage = this._percentage;
    }
});

module.exports = Bar;