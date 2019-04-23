'use strict';

var FramedButton = require('../interface/framedButton')

var CreationScene = {
  create: function () {
    //fadeIn
    this.camera.flash('#000000');

    var style = require('../../assets/fonts/style.json');

    //background
    this.game.add.image(0, 0, 'creationbackground');

    //prueba cursor
    this.selector = this.game.add.sprite(50, 50, 'cursor');

    this.game.add.creationHUD(0, 0, this.selector, this);
    
    this.game.world.bringToTop(this.selector);

    //para ir a fullscreen pulsar F11
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.add(this.goFullscreen, this);
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.halt();

    //music
    var music = this.game.add.audio('intro', 0.1, true);
    this.game.sound.stopAll();
    music.play();
  },
  update: function () {
    //prueba cursor
    this.selector.x = this.game.input.x;
    this.selector.y = this.game.input.y;
  },
  shutdown: function() {
    this.game.camera.onFadeComplete.removeAll();
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


module.exports = CreationScene;
