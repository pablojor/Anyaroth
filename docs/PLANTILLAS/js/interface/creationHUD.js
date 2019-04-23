'use strict'
//var ActionButton = require('./actionButton');
//var HealthBar = require('./healthBar');
var ReactiveRichText = require('./reactiveRichText');
var RichText = require('./richText');
var textFunctions = require('./textFunctions');
var FramedButton = require('./framedButton');
var StatMarker = require('./statMarker');
var ShowCase = require('./showCase');

/*var deactivateActionButton = function () {
  this._button.onInputOver.removeAll();
  this._button.onInputOut.removeAll();
  this._button.onInputDown.removeAll();
  this._button.onInputUp.removeAll();
  this._rechargeEvent.active = false;
  this._text.visible = false;
  this._bar.percentageFunction = function () { return 0; };
  this._bar.percentage = 0;
  this.deactivate()
};*/

var CreationHUD = function (game, parent, x, y, selector, context) {
  Phaser.Group.call(this, game, parent);
  this.x = x;
  this.y = y;
  let style = { "font": "Minecraft", "fill": "#FFFFFF", "fontSize": 10, "align": 'center' };
  var style2 = { font: 'Minecraft', fill: '#000000', fontSize: 10 };
  var style3 = { font: 'Minecraft', fill: '#000000', fontSize: 10, align: 'center' };

  this.MainMenuScene = function () {
    this.game.add.audio('button', 0.1).play();
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('mainmenu'); }, this);
  };

  this.NameScene = function () {
    this.game.add.audio('button', 0.1).play();
    //fadeOut
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('name', true, false, this._showCase.character()); }, this);
  };

  this.add(new Phaser.Image(game, 0, 0, 'creationinterface'));

  this._showCase = this.add(new ShowCase(game, this, 0, 0, require('../../assets/characters/characters.json')));

  this.backButton = this.game.world.add(new FramedButton(this.game.world, this.game, 20, 22, 'backIcon', 'backFrame', [{ callback: function () { this.MainMenuScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));

  this.leftArrowButton = this.add(new FramedButton(this, game, 49, 55, 'arrow', 'arrowFrame', [{ callback: this._showCase.rotate, context: this._showCase, arguments: [1] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767, 1, 0, 1));

  this.rightArrowButton = this.add(new FramedButton(this, game, 151, 55, 'arrow', 'arrowFrame', [{ callback: this._showCase.rotate, context: this._showCase, arguments: [-1] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767, 1, 0, 1));

  this.nextStateButton = this.add(new FramedButton(this, game, 134, 13, 'ritualButton', 'ritualFrame', [{ callback: this.NameScene, context: this, arguments: [1] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767, 1, 0, 1));

  this.nextStateButtonText = this.add(new RichText(game, 141, 17, 50, 'INICIAR RITUAL', style3, this));
  this.nextStateButton._button.input.pixelPerfectClick = true;
  this.nextStateButton._button.input.pixelPerfectOver = true;

  this.rightArrowButton.scale.x *= -1;

  this.leftArrowButton.onInputOver.add(function () { selector.frame = 1; });
  this.leftArrowButton.onInputOut.add(function () { selector.frame = 0; });
  this.leftArrowButton.onInputDown.add(function () { selector.frame = 2; });
  this.leftArrowButton.onInputUp.add(function (over) { 
    if(over)
      selector.frame = 1;
    else
    selector.frame = 0;});

  this.rightArrowButton.onInputOver.add(function () { selector.frame = 1; });
  this.rightArrowButton.onInputOut.add(function () { selector.frame = 0; });
  this.rightArrowButton.onInputDown.add(function () { selector.frame = 2; });
  this.rightArrowButton.onInputUp.add(function (over) { 
    if(over)
      selector.frame = 1;
    else
    selector.frame = 0;});

  this.nextStateButton.onInputOver.add(function () { selector.frame = 1; });
  this.nextStateButton.onInputOut.add(function () { selector.frame = 0; });
  this.nextStateButton.onInputDown.add(function () { selector.frame = 2; });
  this.nextStateButton.onInputUp.add(function (over) { 
    if(over)
      selector.frame = 1;
    else
    selector.frame = 0;});

  this.backButton.onInputOver.add(function () { selector.frame = 1; });
  this.backButton.onInputOut.add(function () { selector.frame = 0; });
  this.backButton.onInputDown.add(function () { selector.frame = 2; });
  this.backButton.onInputUp.add(function (over) { 
    if(over)
      selector.frame = 1;
    else
    selector.frame = 0;});
    
  this.add(new RichText(game, -20, -1, 150, 'ELIGE A TU BUSCADOR:', style, this));

  this._showCase.onBeginRotation.add(function () {
    this.leftArrowButton.deactivate();
    this.rightArrowButton.deactivate();
    this.nextStateButton.deactivate();
    this.nextStateButton._button.tint = 0x555555;
    this.nextStateButtonText.text = '';
    this.game.input.keyboard.addKey(Phaser.Keyboard.LEFT).onDown.active = false;
    this.game.input.keyboard.addKey(Phaser.Keyboard.RIGHT).onDown.active = false;
  }, this);

  this._showCase.onEndRotation.add(function () {
    this.leftArrowButton.activate();
    this.rightArrowButton.activate();
    this.game.input.keyboard.addKey(Phaser.Keyboard.LEFT).onDown.active = true;
    this.game.input.keyboard.addKey(Phaser.Keyboard.RIGHT).onDown.active = true;
    if (this._showCase.isAvaliable()) {
      this.nextStateButton.activate();
      this.nextStateButton._button.tint = 0xFFFFFF;
      this.nextStateButtonText.text = 'INICIAR RITUAL';
    }
  }, this);


  this.game.input.keyboard.addKey(Phaser.Keyboard.LEFT).onDown.add(function(key, direction){this.rotate(direction)}, this._showCase,0,1);
  this.game.input.keyboard.addKey(Phaser.Keyboard.RIGHT).onDown.add(function(key, direction){this.rotate(direction)}, this._showCase,0,-1);
}

CreationHUD.prototype = Object.create(Phaser.Group.prototype);
CreationHUD.prototype.constructor = CreationHUD;

module.exports = CreationHUD;