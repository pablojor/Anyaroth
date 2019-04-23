'use strict'
var ActionButton = require('./actionButton');
var HealthBar = require('./healthBar');
var ReactiveRichText = require('./reactiveRichText');
var textFunctions = require('./textFunctions');
var FramedButton = require('./framedButton')

var deactivateActionButton = function () {
  this._button.onInputOver.removeAll();
  this._button.onInputOut.removeAll();
  this._button.onInputDown.removeAll();
  this._button.onInputUp.removeAll();
  this._rechargeEvent.active = false;
  this._text.visible = false;
  this._bar.percentageFunction = function () { return 0; };
  this._bar.percentage = 0;
  this.deactivate()
};

var SeekerCombatHUD = function (game, parent, x, y, seeker, enemy, selector) {
  Phaser.Group.call(this, game, parent);
  this.x = x;
  this.y = y;
  let style = { "font": "Minecraft", "fill": "#FFFFFF", "fontSize": 10, "align": 'center' };
  var style2 = { font: 'Minecraft', fill: '#000000', fontSize: 10 };
  var style3 = { font: 'Minecraft', fill: '#000000', fontSize: 10, align: 'center' };


  this.blockButton = this.add(new ActionButton(this, game, 44, 132, 'blockIcon', 'actionFrame','blockIcon', [{callback: seeker.block, context: seeker, arguments: []}], 
    function () {
      return (1 - this.block.timeToCoolDown() / this.block.coolDownTime()) * 100;
    }, seeker, function () {
    let a = this.block.timeToCoolDown() / 1000;
    if (isNaN(a)) {
      return '';
    } else {
      let t = a.toFixed(1);
      if(t>=0.1)
        return t.toString();
      else
        return '';
    }
  }, seeker, seeker.coolDown.block.onWhile, seeker.coolDown.block.onEnd, 0x5c5c5c, 0xffffff, 0x000000, 0x222222, 0x676767, 0x676767));

  this.attackButton = this.add(new ActionButton(this, game, 25, 132, 'attackIcon', 'actionFrame','attackIcon', [{callback: seeker.attack, context: seeker, arguments:[enemy]}],
   function () {
      return (1 - this.attack.timeToCoolDown() / this.attack.coolDownTime()) * 100;
    }, seeker, function () {
    let a = this.attack.timeToCoolDown() / 1000;
    if (isNaN(a)) {
      return '';
    } else {
      let t = a.toFixed(1);
      if(t>=0.1)
        return t.toString();
      else
        return '';
    }
    
  }, seeker, seeker.coolDown.attack.onWhile, seeker.coolDown.attack.onEnd, 0x5c5c5c, 0xffffff, 0x000000, 0x222222, 0x676767, 0x676767));

  this.ultimateButton = this.add(new ActionButton(this, game, 64, 132, 'ultimateIcon', 'actionFrame','ultimateIcon', [{callback: seeker.attack, context: seeker, arguments:[enemy]}],
   function () {
      return (1 - this.attack.timeToCoolDown() / this.attack.coolDownTime()) * 100;
    }, seeker, function () {
    let a = this.attack.timeToCoolDown() / 1000;
    if (isNaN(a)) {
      return '';
    } else {
      let t = a.toFixed(1);
      if(t>=0.1)
        return t.toString();
      else
        return '';
    }
  }, seeker, seeker.coolDown.attack.onWhile, seeker.coolDown.attack.onEnd, 0x5c5c5c, 0xffffff, 0x000000, 0x222222, 0x676767, 0x676767));

  var object1 = seeker.items[0];
  var object2 = seeker.items[1];
  if(object1!==undefined){
  this.item1Button = this.add(new ActionButton(this, game, 2,139, 'emptyItem','itemFrame',seeker.items[0].key, [{callback:function(){seeker.use(object1.name, enemy);}, context:this, arguments:[]}],
  function(){return 100;}, this, function(){return '';}, this, object1.onUse, object1.onUse, 0x5c5c5c, 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));
  object1.onUse.add(deactivateActionButton, this.item1Button);
  seeker.onDeath.add(deactivateActionButton, this.item1Button);
  enemy.onDeath.add(deactivateActionButton, this.item1Button);
} else {
  this.item1Button = this.add(new ActionButton(this, game, 2,139, 'emptyItem','itemFrame','emptyItem', [],
  function(){return 100;}, this, function(){return '';}, this, null, null, 0x5c5c5c, 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));
  deactivateActionButton.apply(this.item1Button);
}
  

if(object2!==undefined){
  this.item2Button = this.add(new ActionButton(this, game, 13,139, 'emptyItem','itemFrame', seeker.items[1].key, [{callback:function(){seeker.use(object2.name, enemy);}, context:this, arguments:[]}], 
  function(){return 100;}, this, function(){return '';}, this, object2.onUse, object2.onUse, 0x5c5c5c, 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));
  object2.onUse.add(deactivateActionButton, this.item2Button);
  seeker.onDeath.add(deactivateActionButton, this.item2Button);
  enemy.onDeath.add(deactivateActionButton, this.item2Button);
} else {
  this.item2Button = this.add(new ActionButton(this, game, 13,139, 'emptyItem','itemFrame','emptyItem', [],
  function(){return 100;}, this, function(){return '';}, this, null, null, 0x5c5c5c, 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));
  deactivateActionButton.apply(this.item2Button);
}

  this.blockButton._callbacks.push({ callback: this.attackButton.deactivate, context: this.attackButton, arguments: [] });
  this.blockButton._callbacks.push({ callback: this.blockButton.deactivate, context: this.blockButton, arguments: [] });
  this.blockButton._callbacks.push({ callback: this.blockButton.deactivate, context: this.ultimateButton, arguments: [] });
  this.attackButton._callbacks.push({ callback: this.blockButton.deactivate, context: this.blockButton, arguments: [] });
  this.attackButton._callbacks.push({ callback: this.attackButton.deactivate, context: this.attackButton, arguments: [] });
  this.attackButton._callbacks.push({ callback: this.attackButton.deactivate, context: this.ultimateButton, arguments: [] });
  this.ultimateButton._callbacks.push({ callback: this.blockButton.deactivate, context: this.blockButton, arguments: [] });
  this.ultimateButton._callbacks.push({ callback: this.attackButton.deactivate, context: this.attackButton, arguments: [] });
  this.ultimateButton._callbacks.push({ callback: this.attackButton.deactivate, context: this.ultimateButton, arguments: [] });
  seeker.onDeath.add(deactivateActionButton, this.blockButton);
  seeker.onDeath.add(deactivateActionButton, this.attackButton);
  seeker.onDeath.add(deactivateActionButton, this.ultimateButton);
  enemy.onDeath.add(deactivateActionButton, this.attackButton);
  enemy.onDeath.add(deactivateActionButton, this.blockButton);
  enemy.onDeath.add(deactivateActionButton, this.ultimateButton);



  this.healthBar = this.add(new HealthBar(game, 2, 121, seeker, 'emptyBar', 'healBar', 'damageBar', 'healthBar', 'frameBar', style, 1000, 100, this));

  this.name = this.add(new ReactiveRichText(game, 3, -1, 80, textFunctions.Fun(function () {
    return this.name;
  }, seeker), style2, this, [seeker.onNameChange]));

    this.healthIcon = this.add(new Phaser.Sprite(game,3,14,'healthIcon'));
    this.healthNumber = this.add(new ReactiveRichText(game,15,13,12,textFunctions.Fun(function() {
      if(this.stats.tempHealth > this.stats.health){
        return textFunctions.Color('#00CC00',this.stats.tempHealth.toString());
      } else if (this.stats.tempHealth < this.stats.health){
        return textFunctions.Color('#CC0000',this.stats.tempHealth.toString());
      } else {
        return textFunctions.Color('#000000',this.stats.tempHealth.toString());
      }
    }, seeker), style2, this, [seeker.stats.onHealthChange]));

  this.damageIcon = this.add(new Phaser.Sprite(game, 27, 14, 'damageIcon'));
  this.damageNumber = this.add(new ReactiveRichText(game, 39, 13, 12, textFunctions.Fun(function() {
    if(this.stats.tempDamage > this.stats.damage){
      return textFunctions.Color('#00CC00',this.stats.tempDamage.toString());
    } else if (this.stats.tempDamage < this.stats.damage){
      return textFunctions.Color('#CC0000',this.stats.tempDamage.toString());
    } else {
      return textFunctions.Color('#000000',this.stats.tempDamage.toString());
    }
  }, seeker, 100), style2, this, [seeker.stats.onDamageChange]));

  this.defenseIcon = this.add(new Phaser.Sprite(game, 51, 14, 'defenseIcon'));
  this.defenseNumber = this.add(new ReactiveRichText(game, 63, 13, 12, textFunctions.Fun(function() {
    if(this.stats.tempDefense > this.stats.defense){
      return textFunctions.Color('#00CC00',this.stats.tempDefense.toString());
    } else if (this.stats.tempDefense < this.stats.defense){
      return textFunctions.Color('#CC0000',this.stats.tempDefense.toString());
    } else {
      return textFunctions.Color('#000000',this.stats.tempDefense.toString());
    }
  }, seeker), style2, this, [seeker.stats.onDefenseChange]));

  this.speedIcon = this.add(new Phaser.Sprite(game, 13, 24, 'speedIcon'));
  this.speedNumber = this.add(new ReactiveRichText(game, 25, 23, 12, textFunctions.Fun(function() {
    if(this.stats.tempSpeed > this.stats.speed){
      return textFunctions.Color('#00CC00',this.stats.tempSpeed.toString());
    } else if (this.stats.tempSpeed < this.stats.speed){
      return textFunctions.Color('#CC0000',this.stats.tempSpeed.toString());
    } else {
      return textFunctions.Color('#000000',this.stats.tempSpeed.toString());
    }
  }, seeker), style2, this, [seeker.stats.onSpeedChange]));

  this.perceptionIcon = this.add(new Phaser.Sprite(game, 38, 24, 'perceptionIcon'));
  this.perceptionNumber = this.add(new ReactiveRichText(game, 50, 23, 12, textFunctions.Fun(function() {
    if(this.stats.tempPerception > this.stats.perception){
      return textFunctions.Color('#00CC00',this.stats.tempPerception.toString());
    } else if (this.stats.tempPerception < this.stats.perception){
      return textFunctions.Color('#CC0000',this.stats.tempPerception.toString());
    } else {
      return textFunctions.Color('#000000',this.stats.tempPerception.toString());
    }
  }, seeker), style2, this, [seeker.stats.onPerceptionChange]));

  this.gemIcon = this.add(new Phaser.Sprite(game, 68, 1, 'gemIcon'));
  this.gemNumber = this.add(new ReactiveRichText(game, 50, -1, 15, textFunctions.Fun(function () {
    return this.gems.toString();
  }, seeker), style2, this, [seeker.stats.onPerceptionChange]));

  this.day = this.add(new ReactiveRichText(game, 80, -1, 40, textFunctions.Fun(function () {
    return this.stats.perception.toString();
  }, seeker), style3, this, [seeker.stats.onPerceptionChange]));

  this.villageGemIcon = this.add(new Phaser.Image(game, 110-3, 18, 'villageGemIcon'));
    this.villageGemNumber = this.add(new ReactiveRichText(game, 90-3, 16, 18, textFunctions.Fun(function () {
    return this.totalGems.toString();//hay que cambiarlo
    }, seeker), style2, this, [seeker.stats.onPerceptionChange]));//cambiar onPerceptionChange

    this.populationIcon = this.add(new Phaser.Image(game, 110-3, 28, 'populationIcon'));
    this.populationNumber = this.add(new ReactiveRichText(game, 90-3, 26, 18, textFunctions.Fun(function () {
    return this.population.toString();//hay que cambiarlo
    }, seeker), style2, this, [seeker.stats.onPerceptionChange]));//cambiar onPerceptionChange

    this.seeker= seeker;
}

SeekerCombatHUD.prototype = Object.create(Phaser.Group.prototype);
SeekerCombatHUD.prototype.constructor = SeekerCombatHUD;

SeekerCombatHUD.prototype.freeze = function() {
  this.attackButton._button.inputEnabled = false;
  this.blockButton._button.inputEnabled = false;
  this.ultimateButton._button.inputEnabled = false;
  this.item1Button._button.inputEnabled = false;
  this.item2Button._button.inputEnabled = false;
}

SeekerCombatHUD.prototype.unFreeze = function() {
  this.attackButton._button.inputEnabled = true;
  this.blockButton._button.inputEnabled = true;
  this.ultimateButton._button.inputEnabled = true;
  this.item1Button._button.inputEnabled = true;
  this.item2Button._button.inputEnabled = true;
}

SeekerCombatHUD.prototype.deactivate = function() {
  this.ultimateButton.deactivate();
  this.attackButton.deactivate();
  this.blockButton.deactivate();
  this.item1Button.deactivate();
  this.item2Button.deactivate();

}

SeekerCombatHUD.prototype.activate = function () {
  this.ultimateButton.activate();
  this.attackButton.activate();
  this.blockButton.activate();
  this.healthBar.activate();
  if(this.seeker.items[0])
    this.item1Button.activate();
  if(this.seeker.items[1])
    this.item2Button.activate();
}

module.exports = SeekerCombatHUD;