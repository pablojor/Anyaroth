'use strict';

var textFunctions = require('../interface/textFunctions');
var FramedButton = require('../interface/framedButton')

var MainMenuScene = {

  init: function(seeker, dayManager){
    this._seeker = seeker;
    this._dayManager = dayManager;
  },
  create: function () {
    //fadeIn
    this.camera.flash('#000000');
    var style = require('../../assets/fonts/style.json');

    //background
    this.game.add.image(0, 0, 'mainmenubackground');

    this.selector = this.game.add.sprite(50, 50, 'cursor');

    //buttons
    this.game.add.mainMenuHUD(0, 0, this.selector, this._seeker, this._dayManager);
    this.game.add.image(0, 0, 'shines').alpha = 0.2;
    //great crystal shine particles
    var emitterCrystal = this.game.add.emitter(100, 35, 100);
    emitterCrystal.makeParticles('crystalShines', [0, 1, 2]);
    emitterCrystal.setRotation(0, 0);
    emitterCrystal.setAlpha(0.3, 0.8);
    //emitter.setScale(0.5, 1);
    emitterCrystal.gravity = 0;
    emitterCrystal.flow(2000, 100);

    this.game.add.image(4, 1, 'title');

    this.game.world.bringToTop(this.selector);

    //smoke
    /*var emitter = this.game.add.emitter(10, 100, 400);
    emitter.makeParticles('smoke', [0,1,2]);
    emitter.setRotation(0, 0);
    emitter.setAlpha(0.1, 1, 3000);
    //emitter.setScale(0.1, 1, 0.1, 1, 6000, Phaser.Easing.Quintic.Out);
    emitter.gravity = -400;
    emitter.start(false, 5000,1);
    //emitter.emitX = 0;*/

    //para ir a fullscreen pulsar F11
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.add(this.goFullscreen, this);
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.halt();


    //music
    var music = this.game.add.audio('mainmenutheme', 0.1, true);
    this.game.sound.stopAll();
    music.play();
  },

  update: function () {
    //prueba cursor
    this.selector.x = this.game.input.x;
    this.selector.y = this.game.input.y;
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

module.exports = MainMenuScene;
