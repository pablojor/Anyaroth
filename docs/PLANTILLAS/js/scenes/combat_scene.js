'use strict';

var Stats = require('../characters/stats');
var Item = require('../characters/item');
var textFunctions = require('../interface/textFunctions');

//village stats
var day = 1;
var population = 24;
var totalgems = 0;
var selector;
//var seeker = require('./character.js');//dice que character.js es un modulo común de js, que debe ser convertido a un ES6

var CombatScene = {

  MainMenuScene: function () {
    this.game.state.start('mainmenu');

  },
  seeker: null,
  enemy: null,
  init: function(seeker, dayManager, enemy, background, music, end){
    this._seeker = seeker;
    this._dayManager = dayManager;
    this._enemy = enemy;
    this._background = background;
    this._music = music;
    this._end = end;
  },
  create: function () {
    //fadeIn
    this.camera.flash('#000000');

    //render background
    var combatbackground = this.game.add.image(0, 0, this._background);
    //render seeker //tope de nombre caracteres = 9
    this.seeker = this.game.add.seeker( 0, -8, this._seeker.name, this._seeker.stats, this._seeker.items, this._seeker.spriteSheet, this._seeker.actions, this._seeker.particles);
    this.seeker.hp = this._seeker.hp;
    this.seeker.gems = this._seeker.gems;
    this.seeker.population = this._seeker.population;
    this.seeker.totalGems = this._seeker.totalGems;
    this.seeker.day = this._seeker.day;
    //render enemy
    var a = require('../../assets/patterns/patterns');
    this.enemy = this.game.add.enemy(this.game.world.width - 80, -8, this._enemy.name, this._enemy.stats, this._enemy.spriteSheet, 
    this._enemy.actions, this._enemy.particles, this.seeker, a[this._enemy.pattern]);

    //interface
    this.combatHUD = this.game.add.combatHUD(0, 0, this.seeker, this.enemy);
    this.combatHUD.deactivate();
    //transicion de entrada a combate

    var filter = this.game.add.filter('Pixelate', 800, 600);
    this.game.world.filters = [filter];
    filter.sizeX = 1000;
    filter.sizeY = 1000;
    var tween = this.game.add.tween(filter).to({ sizeX: 1, sizeY: 1 }, 2000, "Quart.easeOut").start();
    tween.onComplete.add(function () {
      this.game.world.filters = null;
      // Controls
      this.seeker.idle();
      this.enemy.act();
      this.combatHUD.activate();
    }, this);

    var style = require('../../assets/fonts/style.json');

    this.enemy.onDeathComplete.add(function () {
      var t = this.game.time.create();
      t.add(1000, function () {
        filter = this.game.add.filter('Pixelate', 800, 600);
        this.game.world.filters = [filter];
        filter.sizeX = 1;
        filter.sizeY = 1;
        tween = this.game.add.tween(filter).to({ sizeX: 1000, sizeY: 1000 }, 2000, "Quart.easeIn").start()
          .onComplete.add(function () {  this._end(this._seeker, this._dayManager); }, this);
      }, this);
      t.start();
    }, this);
    this.seeker.onDeathComplete.add(function () {
      var t = this.game.time.create();
      t.add(1000, function () {
        filter = this.game.add.filter('Pixelate', 800, 600);
        this.game.world.filters = [filter];
        filter.sizeX = 1;
        filter.sizeY = 1;
        tween = this.game.add.tween(filter).to({ sizeX: 1000, sizeY: 1000 }, 2000, "Quart.easeIn").start()
          .onComplete.add(function () {  this.MainMenuScene(); }, this);
      }, this);
      t.start();
    }, this);

    
    //para ir a fullscreen pulsar F11
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.add(this.goFullscreen, this);
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.halt();

    //music
    var music = this.game.add.audio(this._music, 0.1, true);
    this.game.sound.stopAll();
    music.play();

    //INFOWINDOWS
    //vitalidad
    //this.game.add.infoWindow(50, 50, 62, 53, 'infoWindow', [textFunctions.Color('#B60000', 'Vitalidad'), ' Determina tu salud máxima.'], { align: 'left' });
    //ataque
    /*this.game.add.infoWindow(50, 50, 62, 53, 'infoWindow',  [textFunctions.Color('#B60000','Ataque'), ' Determina el daño que haces.'], {align: 'left'});
    //defensa
    this.game.add.infoWindow(50, 50, 62, 53, 'infoWindow',  [textFunctions.Color('#B60000','Defensa'), ' Determina el daño bloqueado.'], {align: 'left'});
    //velocidad
    this.game.add.infoWindow(50, 50, 62, 53, 'infoWindow',  [textFunctions.Color('#B60000','Velocidad'), ' Determina el tiempo entre acciones.'], {align: 'left'});
    //percepcion
    this.game.add.infoWindow(50, 50, 78, 70, 'infoWindow',  [textFunctions.Color('#B60000','Percepción'), ' Determina la interfaz enemiga.'], {align: 'left'});
    */


    //prueba cursor
    selector = this.game.add.sprite(50, 50, 'cursor');

  },
  update: function () {
    //prueba cursor
    selector.x = this.game.input.x;
    selector.y = this.game.input.y;
  },
  shutdown: function() {
    this._seeker.stats = this.seeker.stats;
    this._seeker.hp = this.seeker.hp;
    this._seeker.gems = this.seeker.gems;
    this._seeker.population = this.seeker.population;
    this._seeker.totalGems = this.seeker.totalGems;
    this._seeker.items = this.seeker.items;
  },
  goFullscreen: function () {

    if (this.game.scale.isFullScreen) {
      this.game.scale.stopFullScreen();
    }
    else {
      this.game.scale.startFullScreen(false);
    }

  }
};




module.exports = CombatScene;
