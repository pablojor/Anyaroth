// var Phaser = require('phaser');

var Character = require('./characters/character');
var Seeker = require('./characters/seeker');
var Enemy = require('./characters/enemy');
var Bar = require('./interface/bar');
var CircleWithSectors = require('./interface/circleWithSectors');
var HealthBar = require('./interface/healthBar');
var ReactiveBar = require('./interface/reactiveBar');
var ReactiveContinuousBar = require('./interface/reactiveContinuousBar');
var ReactiveRichText = require('./interface/reactiveRichText');
var RichText = require('./interface/richText');
var ActionButton = require('./interface/actionButton');
var SeekerCombatHUD = require('./interface/seekerCombatHUD');
var EnemyCombatHUD = require('./interface/enemyCombatHUD');
var CombatHUD = require('./interface/combatHUD');
var ScrollText = require('./interface/scrollText');
var EventHUD = require('./interface/eventHUD');
var OptionMenu = require('./interface/optionMenu');
var ButtonMenu = require('./interface/buttonMenu');
var WindowFrame = require('./interface/windowFrame');
var FramedButton = require('./interface/framedButton');
var InfoWindow = require('./interface/infoWindow');
var MainMenuHUD = require('./interface/mainMenuHUD');
var CreationHUD = require('./interface/creationHUD');
/**
 * 
 */
fun = function (Phaser) {
    Phaser.GameObjectFactory.prototype.character = function (x, y, name, stats, spriteSheet, actions, particles, group) {
        if (group === undefined) { group = this.world; }
        return group.add(new Character(this.game, x, y, name, stats, spriteSheet, actions, particles));
    }

    Phaser.GameObjectFactory.prototype.seeker = function (x, y, name, stats, objects, spriteSheet, actions, particles, group) {
        if (group === undefined) { group = this.world; }
        return group.add(new Seeker(this.game, x, y, name, stats, objects, spriteSheet, actions, particles));
    }

    Phaser.GameObjectFactory.prototype.enemy = function (x, y, name, stats, spriteSheet, actions, particles, seeker, pattern, group) {
        if (group === undefined) { group = this.world; }
        return group.add(new Enemy(this.game, x, y, name, stats, spriteSheet, actions, particles, seeker, pattern));
    }

    Phaser.GameObjectFactory.prototype.bar = function (x, y, key, frame, parent = this.game.world) {
        return new Bar(this.game, parent, x, y, key, frame);
    }

    Phaser.GameObjectFactory.prototype.circleWithSectors = function (x, y, radius, angles, colors, alphas, antiClockWise, segments, group) {
        if (group === undefined) { group = this.world; }
        return group.add(new CircleWithSectors(this.game, x, y, radius, angles, colors, alphas, antiClockWise, segments));
    }

    Phaser.GameObjectFactory.prototype.healthBar = function (x, y, character, voidKey, healKey, damageKey, healthKey, framekey, style, delay, speed, voidFrame = null, healFrame = null, damageFrame = null, healthFrame = null, parent = this.game.world) {
        return new HealthBar(this.game, x, y, character, voidKey, healKey, damageKey, healthKey, healthKey, style, delay, speed, voidFrame, healFrame, damageFrame, healthFrame, parent);
    }

    Phaser.GameObjectFactory.prototype.reactiveBar = function (parent, x, y, key, percentageFunction, functionContext, signal, frame) {
        return new ReactiveBar(this.game, parent, x, y, key, percentageFunction, functionContext, signal, frame);
    }

    Phaser.GameObjectFactory.prototype.reactiveContinuousBar = function (parent, x, y, key, percentageFunction, functionContext, signal, decreaseDelay, increaseDelay, decreaseSpeed, increaseSpeed, frame = null) {
        return new ReactiveContinuousBar(this.game, parent, x, y, key, percentageFunction, functionContext, signal, decreaseDelay, increaseDelay, decreaseSpeed, increaseSpeed, frame);
    }

    Phaser.GameObjectFactory.prototype.reactiveRichText = function (x, y, lineWidth, text, style, signal, group) {
        if (group === undefined) { group = this.world; }
        return group.add(new ReactiveRichText(this.game, x, y, lineWidth, text, style, group, signal));
    }

    Phaser.GameObjectFactory.prototype.richText = function (x, y, lineWidth, text, style = {}, group = this.game.world) {
        return new RichText(this.game, x, y, lineWidth, text, style, group);
    }

    Phaser.GameObjectFactory.prototype.actionButton = function (x, y, buttonKey, frameKey, barKey, callbacks, percentageFunction, percentageFunctionContext,
        timeFunction, timeFunctionContext, barSignal, totalRechargeSignal,
        overButtonFrame = 0, outButtonFrame = 0, downButtonFrame = 0, upButtonFrame = 0, disabledButtonFrame = 0,
        overFrameFrame = 0, outFrameFrame = 0, downFrameFrame = 0, upFrameFrame = 0, disabledFrameFrame = 0,
        frameColorOver = 0, frameColorOut = 0, frameColorDown = 0, frameColorUp = 0, frameColorDisabled = 0, barFrame = 0, parent = this.game.world) {
        return new ActionButton(parent, this.game, x, y, buttonKey, frameKey, barKey, callbacks, percentageFunction, percentageFunctionContext,
            timeFunction, timeFunctionContext, barSignal, totalRechargeSignal,
            overButtonFrame, outButtonFrame, downButtonFrame, upButtonFrame, disabledButtonFrame,
            overFrameFrame, outFrameFrame, downFrameFrame, upFrameFrame, disabledFrameFrame,
            frameColorOver, frameColorOut, frameColorDown, frameColorUp, frameColorDisabled, barFrame);
    }

    Phaser.GameObjectFactory.prototype.seekerCombatHUD = function (x, y, seeker, enemy, parent = this.game.world) {
        return new SeekerCombatHUD(this.game, parent, x, y, seeker, enemy);
    }

    Phaser.GameObjectFactory.prototype.enemyCombatHUD = function (x, y, seeker, enemy, parent = this.game.world) {
        return new EnemyCombatHUD(this.game, parent, x, y, seeker, enemy);
    }

    Phaser.GameObjectFactory.prototype.combatHUD = function (x, y, seeker, enemy, parent = this.game.world) {
        return new CombatHUD(this.game, parent, x, y, seeker, enemy);
    }

    Phaser.GameObjectFactory.prototype.scrollText = function (x, y, width, height, text, style, parent = this.game.world) {
        return new ScrollText(this.game, parent, x, y, width, height, text, style);
    }

    Phaser.GameObjectFactory.prototype.eventHUD = function (seeker, dayManager, text, options, image, parent = this.game.world) {
        return new EventHUD(this.game, parent, seeker, dayManager, text, options, image);
    }

    Phaser.GameObjectFactory.prototype.optionMenu = function (buttonsMenu, group) {
        if (group === undefined) { group = this.world; }
        return group.add(new OptionMenu(this.game, buttonsMenu, group));
    }

    Phaser.GameObjectFactory.prototype.buttonMenu = function (name, x, y, key, callback, callbackContext, overFrame, outFrame, downFrame, upFrame, group) {
        if (group === undefined) { group = this.world; }
        return group.add(new ButtonMenu(this.game, name, x, y, key, callback, callbackContext, overFrame, outFrame, downFrame, upFrame));
    }

    Phaser.GameObjectFactory.prototype.windowFrame = function (x, y, width, height, key, parent = this.world) {
        return new WindowFrame(this.game, parent, x, y, width, height, key);
    }

    Phaser.GameObjectFactory.prototype.framedButton = function (x, y, buttonKey, frameKey, callbacks,
        frameColorOver, frameColorOut, frameColorDown, frameColorUp, frameColorDisabled,
        overButtonFrame, outButtonFrame, downButtonFrame, upButtonFrame, disabledButtonFrame,
        overFrameFrame, outFrameFrame, downFrameFrame, upFrameFrame, disabledFrameFrame, parent = this.world) {

        return new FramedButton(parent, this.game, x, y, buttonKey, frameKey, callbacks,
            frameColorOver, frameColorOut, frameColorDown, frameColorUp, frameColorDisabled,
            overButtonFrame, outButtonFrame, downButtonFrame, upButtonFrame, disabledButtonFrame,
            overFrameFrame, outFrameFrame, downFrameFrame, upFrameFrame, disabledFrameFrame)
    }

    Phaser.GameObjectFactory.prototype.infoWindow = function (x, y, width, height, windowKey, text, style, parent = this.world) {
        return new InfoWindow(parent, this.game, x, y, width, height, windowKey, text, style);
    }

    Phaser.GameObjectFactory.prototype.mainMenuHUD = function (x, y, selector, seeker = undefined, dayManager = undefined, parent = this.game.world) {
        return new MainMenuHUD(this.game, parent, x, y, selector, seeker, dayManager);
    }

    Phaser.GameObjectFactory.prototype.creationHUD = function (x, y, exitFunction, context, parent = this.game.world) {
        return new CreationHUD(this.game, parent, x, y, exitFunction, context);
    }
}

module.exports = fun;