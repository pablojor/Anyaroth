'use strict'

var Bar = require('./bar.js');
var ReactiveContinuousBar = require('./reactiveContinuousBar.js');
var ReactiveRichText = require('./reactiveRichText.js');
var textFunction = require('./textFunctions')

var hpPercentage = function () {
        return this.hp / this.stats.maxHp * 100;
}

var HealthBar = function (game, x, y, character, voidKey, healKey, damageKey, healthKey, frameKey, style, delay, speed, voidFrame, healFrame, damageFrame, healthFrame, parent) {
        Phaser.Group.call(this, game, parent);
        this.x = x;
        this.y = y;
        this.voidBar = this.add(new Bar(game, this, 0, 0, voidKey, voidFrame));
        this.damageBar = this.add(new ReactiveContinuousBar(game, this, 0, 0, damageKey, hpPercentage, character, character.onHpChange, delay, delay, speed, speed, damageFrame));
        this.healBar = this.add(new ReactiveContinuousBar(game, this, 0, 0, healKey, hpPercentage, character, character.onHpChange, 0, 0, speed, speed, healFrame));
        this.healthBar = this.add(new ReactiveContinuousBar(game, this, 0, 0, healthKey, hpPercentage, character, character.onHpChange, 0, delay, speed, speed, healthFrame));
        this.hpText = this.add(new ReactiveRichText(game, 0, -2, this.voidBar.width, [textFunction.VariableNumber(function () { return this.hp; }, character, speed),
                '/',
        textFunction.VariableNumber(function () { return this.stats.maxHp; }, character, 1000)], style, this, [character.onHpChange, character.stats.onHealthChange]));
        this.frame = this.add(new Phaser.Sprite(game, -1, -1, frameKey));
        
}

HealthBar.prototype = Object.create(Phaser.Group.prototype);
HealthBar.prototype.constructor = HealthBar;

HealthBar.prototype.activate = function() {
        this.damageBar.percentage = this.damageBar.percentageFunction();
        this.healBar.percentage = this.healBar.percentageFunction();
        this.healthBar.percentage = this.healthBar.percentageFunction();
        this.hpText.write();
}


module.exports = HealthBar;