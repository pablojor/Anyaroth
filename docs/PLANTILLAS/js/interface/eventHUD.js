'use strict'

var ScrollText = require('./scrollText');
var HealthBar = require('./healthBar');
var ReactiveRichText = require('./reactiveRichText');
var textFunctions = require('./textFunctions');
var Slider = require('./slider');
var FramedButton = require('./framedButton');
var RichText = require('./richText');

var EventHUD = function (game, parent, seeker, dayManager, text, options, image) {
    Phaser.Group.call(this, game, parent);
    for (let element in options) {
        options[element].text;
        options[element].callback;
    }
    let style = require('../../assets/fonts/style.json');

    var style2 = { "font": "Minecraft", "fill": "#000000", "fontSize": 10 };

    var style3 = { "font": "Minecraft", "fill": "#FFFFFF", "fontSize": 10, "align": 'center' };
    var style4 = { "font": "Minecraft", "fill": "#000000", "fontSize": 10, "align": 'center' };

    this.text = this.add(new ScrollText(game, this, 74, 32, 119, 85, text, style2));
    this.frame = this.add(new Phaser.Image(game, 0, 0, 'eventinterface'));
    this.healthBar = this.add(new HealthBar(game, 79, 2, seeker, 'emptyBar', 'healBar', 'damageBar', 'healthBar', 'frameBar', style3, 1000, 100, this));

    this.name = this.add(new ReactiveRichText(game, 3, -1, 80, textFunctions.Fun(function () {
        return this.name;
    }, seeker), style2, this, [seeker.onNameChange]));

    this.healthIcon = this.add(new Phaser.Image(game, 3, 15, 'healthIcon'));
    this.healthNumber = this.add(new ReactiveRichText(game, 15, 13, 12, textFunctions.Fun(function () {
        return this.stats.health.toString();
    }, seeker), style2, this, [seeker.stats.onHealthChange]));

    this.damageIcon = this.add(new Phaser.Image(game, 27, 15, 'damageIcon'));
    this.damageNumber = this.add(new ReactiveRichText(game, 39, 13, 12, textFunctions.Fun(function () {
        return this.stats.damage.toString();
    }, seeker), style2, this, [seeker.stats.onDamageChange]));

    this.defenseIcon = this.add(new Phaser.Sprite(game, 51, 15, 'defenseIcon'));
    this.defenseNumber = this.add(new ReactiveRichText(game, 63, 13, 12, textFunctions.Fun(function () {
        return this.stats.defense.toString();
    }, seeker), style2, this, [seeker.stats.onDefenseChange]));

    this.speedIcon = this.add(new Phaser.Image(game, 75, 15, 'speedIcon'));
    this.speedNumber = this.add(new ReactiveRichText(game, 87, 13, 12, textFunctions.Fun(function () {
        return this.stats.speed.toString();
    }, seeker), style2, this, [seeker.stats.onSpeedChange]));

    this.perceptionIcon = this.add(new Phaser.Image(game, 99, 15, 'perceptionIcon'));
    this.perceptionNumber = this.add(new ReactiveRichText(game, 111, 13, 12, textFunctions.Fun(function () {
        return this.stats.damage.toString();
    }, seeker), style2, this, [seeker.stats.onPerceptionChange]));

    this.gemIcon = this.add(new Phaser.Image(game, 68, 1, 'gemIcon'));
    this.gemNumber = this.add(new ReactiveRichText(game, 50, -1, 18, textFunctions.Fun(function () {
        return this.gems.toString();
    }, seeker), style2, this, [seeker.stats.onPerceptionChange]));//cambiar onPerceptionChange

    this.villageGemIcon = this.add(new Phaser.Image(game, 160 + 3, 18, 'villageGemIcon'));
    this.villageGemNumber = this.add(new ReactiveRichText(game, 142 + 3, 16, 18, textFunctions.Fun(function () {
        return this.totalGems.toString();
    }, seeker), style2, this, [seeker.stats.onPerceptionChange]));//cambiar onPerceptionChange

    this.populationIcon = this.add(new Phaser.Image(game, 160 + 28, 18, 'populationIcon'));
    this.populationNumber = this.add(new ReactiveRichText(game, 142 + 28, 16, 18, textFunctions.Fun(function () {
        return this.population.toString();
    }, seeker), style2, this, [seeker.stats.onPerceptionChange]));//cambiar onPerceptionChange

    this.slider = this.add(new Slider(game, this, 194, 35, 'sliderBackground', 'slider', 80, 50, 3));
    this.slider.onChange.add(function (percentage) { this.text.move(percentage); }, this);

    this.options = [{}, {}, {}, {}];
    for (let i = 0; i < 4 && i < options.length; i++) {
        this.slider.onEnd.add(function (i) {
            this.options[i].button.activate();
            this.options[i].text.visible = true;
        }, this, 0, i);
        this.options[i].button = this.add(new FramedButton(this, game, 101 * (i % 2), 122 + 15 * Math.floor(i / 2), 'optionBack', 'optionFrame', [{
            callback: options[i].callback,
            context: options[i].context,
            arguments: options[i].arguments
        }], 0x000000, 0xFFFFFF, 0x5C5C5C, 0x111111, 0xAAAAAA));
        this.options[i].text = this.add(new RichText(game, 2 + 101 * (i % 2), 122 + 15 * Math.floor(i / 2), 100, options[i].text, style));
        this.options[i].button.deactivate();
        this.options[i].text.visible = false;
    }

    for (let i = options.length; i < 4; i++) {
        options[i] = {
            callback: function () { },
            context: this,
            arguments: [],
            text: ' HOla'
        }
        this.options[i].button = this.add(new FramedButton(this, game, 101 * (i % 2), 122 + 15 * Math.floor(i / 2), 'optionBack', 'optionFrame', [{
            callback: options[i].callback,
            context: options[i].context,
            arguments: options[i].arguments
        }], 0x000000, 0xFFFFFF, 0x5C5C5C, 0x111111, 0xAAAAAA));
        this.options[i].text = this.add(new RichText(game, 2 + 101 * (i % 2), 122 + 15 * Math.floor(i / 2), 100, options[i].text, style));
        this.options[i].button.deactivate();
        this.options[i].text.visible = false;
    }

    this.imageFrame = this.add(new Phaser.Sprite(game, 2, 42, image));

    this.day = this.add(new ReactiveRichText(game, 26, 27, 40, textFunctions.Fun(function () {
        return this.day.toString();
    }, seeker), style4, this, [seeker.stats.onPerceptionChange]));

    this.pauseButton = this.add(new FramedButton(this, game, 190, 2, 'pauseButton', 'pauseButtonFrame',[{callback: EventHUD.prototype._pause, context:this, arguments:[]}],0xFFFFFF,0x000000,0x676767, 0x222222, 0x676767));
    this._pause = false;
}

EventHUD.prototype = Object.create(Phaser.Group.prototype);
EventHUD.prototype.constructor = EventHUD;

//[{text:, callback:}]
EventHUD.prototype.reset = function (text, options) {
    this.slider.move(-100);
    this.text.text = text;
    this.slider.onEnd.dispose();

    for (let i = 0; i < 4 && i < options.length; i++) {
        this.slider.onEnd.add(function (i) {
            this.options[i].button.activate();
            this.options[i].text.visible = true;
        }, this, 0, i);

        this.options[i].button._callbacks[0] = {
            callback: options[i].callback,
            context: options[i].context,
            arguments: options[i].arguments
        };
        this.options[i].text.text = options[i].text;
        this.options[i].button.deactivate();
        this.options[i].text.visible = false;
    }

    for(let i = options.length; i < 4; i++) {
        this.options[i].text.text = '';
        this.options[i].button.deactivate();
        this.options[i].text.visible = false;
    }
}

EventHUD.prototype._pause = function(){
    if(this._pause){
    } else {
    }
    this._pause = !this._pause;
}

module.exports = EventHUD;

