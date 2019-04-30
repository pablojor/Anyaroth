'use strict'
//var ActionButton = require('./actionButton');
//var HealthBar = require('./healthBar');
var ReactiveRichText = require('./reactiveRichText');
var textFunctions = require('./textFunctions');
var FramedButton = require('./framedButton')

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

var MainMenuHUD = function (game, parent, x, y, selector, seeker, dayManager) {
  Phaser.Group.call(this, game, parent, selector);
  this.x = x;
  this.y = y;
  let style = { "font": "Minecraft", "fill": "#FFFFFF", "fontSize": 10, "align": 'center' };
  var style2 = { font: 'Minecraft', fill: '#000000', fontSize: 10 };
  var style3 = { font: 'Minecraft', fill: '#000000', fontSize: 10, align: 'center' };

  this.CreationScene = function () {
    this.game.add.audio('button', 0.1).play();
    //fadeOut
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('creation'); }, parent);
  };

  this.EventScene = function () {
    this.game.add.audio('button', 0.1).play();
    //fadeOut
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('event'); }, parent);
  };

  this.CombatScene = function () {
    this.game.add.audio('button', 0.1).play();
    //fadeOut
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('combat', true, false, 'hola', 'semos', 'ah'); }, parent);
  };

  this.CreditsScene = function () {
    this.game.add.audio('button', 0.1).play();
    //fadeOut
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('credits'); }, parent);
  };

  this.SettingsScene = function () {
    this.game.add.audio('button', 0.1).play();
    //fadeOut
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('settings') }, parent);
  };

  this.ShopScene = function () {
    this.game.add.audio('button', 0.1).play();
    //fadeOut
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('shop') }, parent);
  };

  this.creditsButton = this.add(new FramedButton(this, game, 153, 0, 'tavern', 'tavernFrame', [{ callback: function () { this.CreditsScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767, 1, 0, 1));
  this.creditsButton._button.input.pixelPerfectClick = true;
  this.creditsButton._button.input.pixelPerfectOver = true;
  this.shopButton = this.add(new FramedButton(this, game, 0, 87, 'shop', 'shopFrame', [{ callback: function () { this.ShopScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767, 1, 0, 1, 0, 2));
  this.shopButton._button.input.pixelPerfectClick = true;
  this.shopButton._button.input.pixelPerfectOver = true;
  this.settingsButton = this.add(new FramedButton(this, game, 0, 27, 'settings', 'settingsFrame', [{ callback: function () { this.SettingsScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767, 1, 0, 1));
  this.settingsButton._button.input.pixelPerfectClick = true;
  this.settingsButton._button.input.pixelPerfectOver = true;
  this.doorButton = this.add(new FramedButton(this, game, 174, 39, 'door', 'doorFrame', [{ callback: function () { this.CombatScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767, 1, 0, 1, 0, 2));
  this.doorButton._button.input.pixelPerfectClick = true;
  this.doorButton._button.input.pixelPerfectOver = true;
  this.crystalButton = this.add(new FramedButton(this, game, 81, 9, 'crystal', 'crystalFrame', [{ callback: function () { this.CreationScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767, 1, 0, 1));
  this.crystalButton._button.input.pixelPerfectClick = true;
  this.crystalButton._button.input.pixelPerfectOver = true;

  //version
  this.game.add.richText(148, 139, 80, "v 1.0", style);

  //textos de buttons
  this.game.add.richText(10, 70, 80, "OPCIONES", style);
  this.shopText = this.game.add.richText(28, 119, 80, "TIENDA", style);
  this.crystalText = this.game.add.richText(60, 39, 80, "NUEVA PARTIDA", style);
  this.doorText = this.game.add.richText(120, 79, 80, "NUEVA BUSQUEDA", style);
  this.creditsText = this.game.add.richText(128, 20, 80, "CREDITOS", style);

  this.shopButton.onInputDisable.add(function () {
    this.shopText.setAll('tint', 0x888888);
  }, this);
  this.crystalButton.onInputDisable.add(function () {
    this.crystalText.setAll('tint', 0x888888);
  }, this);
  this.doorButton.onInputDisable.add(function () {
    this.doorText.setAll('tint', 0x888888);
  }, this);

  this.shopButton.onInputOver.add(function () { selector.frame = 1; });
  this.shopButton.onInputOut.add(function () { selector.frame = 0; });
  this.shopButton.onInputDown.add(function () { selector.frame = 2; });
  this.shopButton.onInputUp.add(function (over) {
    if (over)
      selector.frame = 1;
    else
      selector.frame = 0;
  });

  this.settingsButton.onInputOver.add(function () { selector.frame = 1; });
  this.settingsButton.onInputOut.add(function () { selector.frame = 0; });
  this.settingsButton.onInputDown.add(function () { selector.frame = 2; });
  this.settingsButton.onInputUp.add(function (over) {
    if (over)
      selector.frame = 1;
    else
      selector.frame = 0;
  });

  this.doorButton.onInputOver.add(function () { selector.frame = 1; });
  this.doorButton.onInputOut.add(function () { selector.frame = 0; });
  this.doorButton.onInputDown.add(function () { selector.frame = 2; });
  this.doorButton.onInputUp.add(function (over) {
    if (over)
      selector.frame = 1;
    else
      selector.frame = 0;
  });

  this.crystalButton.onInputOver.add(function () { selector.frame = 1; });
  this.crystalButton.onInputOut.add(function () { selector.frame = 0; });
  this.crystalButton.onInputDown.add(function () { selector.frame = 2; });
  this.crystalButton.onInputUp.add(function () { selector.frame = 1; });
  this.crystalButton.onInputUp.add(function (over) {
    if (over)
      selector.frame = 1;
    else
      selector.frame = 0;
  });

  this.creditsButton.onInputOver.add(function () { selector.frame = 1; });
  this.creditsButton.onInputOut.add(function () { selector.frame = 0; });
  this.creditsButton.onInputDown.add(function () { selector.frame = 2; });
  this.creditsButton.onInputUp.add(function (over) {
    if (over)
      selector.frame = 1;
    else
      selector.frame = 0;
  });

  if (!seeker) {
    this.doorButton.deactivate();
    this.shopButton.deactivate();
  } else {
    this.crystalButton.deactivate();
  }

  //var object1 = seeker.items[0];
  //var object2 = seeker.items[1];





  //this.item2Button = this.add(new FramedButton(this, game, 14,139, seeker.items[1].key,'itemFrame', [{callback:function(){seeker.use(object2.name, enemy);}, context:this, arguments:[]}], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));


  //this.healthBar = this.add(new HealthBar(game, 2, 121, seeker, 'emptyBar', 'healBar', 'damageBar', 'healthBar', 'frameBar', style, 1000, 100, this));

  /*this.name = this.add(new ReactiveRichText(game, 3, -1, 80, textFunctions.Fun(function () {
    return this.name;
  }, seeker), style2, this, seeker.onNameChange));
 
    this.defenseIcon = this.add(new Phaser.Sprite(game,3,14,'healthIcon'));
    this.defenseNumber = this.add(new ReactiveRichText(game,15,13,11,textFunctions.Fun(function() {
        return this.stats.defense.toString();
    }, seeker), style2, this, seeker.stats.onDefenseChange));
 
  this.damageIcon = this.add(new Phaser.Sprite(game, 27, 14, 'damageIcon'));
  this.damageNumber = this.add(new ReactiveRichText(game, 39, 13, 11, textFunctions.VariableNumber(function () { return this.stats.damage;}
  , seeker, 100), style2, this, [seeker.stats.onDamageChange]));
 
  this.defenseIcon = this.add(new Phaser.Sprite(game, 51, 14, 'defenseIcon'));
  this.defenseNumber = this.add(new ReactiveRichText(game, 63, 13, 11, textFunctions.Fun(function () {
    return this.stats.defense.toString();
  }, seeker), style2, this, seeker.stats.onDefenseChange));
 
  this.speedIcon = this.add(new Phaser.Sprite(game, 13, 24, 'speedIcon'));
  this.speedNumber = this.add(new ReactiveRichText(game, 25, 23, 11, textFunctions.Fun(function () {
    return this.stats.speed.toString();
  }, seeker), style2, this, seeker.stats.onSpeedChange));
 
  this.perceptionIcon = this.add(new Phaser.Sprite(game, 38, 24, 'perceptionIcon'));
  this.perceptionNumber = this.add(new ReactiveRichText(game, 50, 23, 11, textFunctions.Fun(function () {
    return this.stats.perception.toString();
  }, seeker), style2, this, seeker.stats.onPerceptionChange));
 
  this.gemIcon = this.add(new Phaser.Sprite(game, 68, 1, 'gemIcon'));
  this.gemNumber = this.add(new ReactiveRichText(game, 50, -1, 15, textFunctions.Fun(function () {
    return this.gems.toString();
  }, seeker), style2, this, seeker.stats.onPerceptionChange));
 
  this.day = this.add(new ReactiveRichText(game, 80, -1, 40, textFunctions.Fun(function () {
    return this.stats.perception.toString();
  }, seeker), style3, this, seeker.stats.onPerceptionChange));*/

  /*this.villageGemIcon = this.add(new Phaser.Image(game, 110-3, 18, 'villageGemIcon'));
    this.villageGemNumber = this.add(new ReactiveRichText(game, 90-3, 16, 15, textFunctions.Fun(function () {
    return this.totalGems.toString();//hay que cambiarlo
    }, seeker), style2, this, seeker.stats.onPerceptionChange));//cambiar onPerceptionChange
 
    this.populationIcon = this.add(new Phaser.Image(game, 110-3, 28, 'populationIcon'));
    this.populationNumber = this.add(new ReactiveRichText(game, 90-3, 26, 15, textFunctions.Fun(function () {
    return this.population.toString();//hay que cambiarlo
    }, seeker), style2, this, seeker.stats.onPerceptionChange));//cambiar onPerceptionChange*/

  //this.game.add.optionMenu([['pauseButton', 190, 2, 'pauseButton', this.EventScene, this, {}]]);
}

MainMenuHUD.prototype = Object.create(Phaser.Group.prototype);
MainMenuHUD.prototype.constructor = MainMenuHUD;

module.exports = MainMenuHUD;