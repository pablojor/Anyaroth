'use strict';

var FramedButton = require('../interface/framedButton')

var selector;

var SettingsScene = {
  MainMenuScene: function () {
    this.game.add.audio('button', 0.1).play();
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function(){this.game.state.start('mainmenu');}, this);
  },
  init: function(seeker, dayManager){
    this._seeker = seeker;
    this._dayManager = dayManager;
  },
  create: function () {
    //fadeIn
    this.camera.flash('#000000');
    
    var style = require('../../assets/fonts/style.json');

    this.game.add.richText(10, 10, 50, 'VIDEO', style);
    this.game.add.richText(20, 30, 100, 'Pantalla completa', style);

    this.game.add.richText(10, 70, 50, 'AUDIO', style);
    this.game.add.richText(25, 90, 100, 'Volumen de sonido', style);
    this.game.add.richText(25, 110, 100, 'Volumen de música', style);


    this.backButton = this.game.world.add(new FramedButton(this.game.world, this.game, 179, 130, 'backIcon', 'backFrame', [{ callback: function () { this.MainMenuScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));

    //prueba cursor
    selector = this.game.add.sprite(50, 50, 'cursor');

    //para ir a fullscreen pulsar F11
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.add(this.goFullscreen, this);
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.halt();
    
    this.game.sound.stopAll();
  },
  update: function(){
  //prueba cursor
  selector.x = this.game.input.x;
  selector.y = this.game.input.y;
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


module.exports = SettingsScene;
