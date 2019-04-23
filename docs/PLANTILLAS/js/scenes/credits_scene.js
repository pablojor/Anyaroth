'use strict';

var FramedButton = require('../interface/framedButton')

var backButton;
var selector;

var CreditsScene = {
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

    this.game.add.richText(10, this.game.world.height, 100, 'LightSeeker Desarrollado por Turing\'s Song Studios', style);
    this.game.add.richText(10, this.game.world.height+50, 100, 'Carlos Durán Dominguez', style);
    this.game.add.richText(10, this.game.world.height+80, 100, 'Arturo García Cárdenas', style);
    this.game.add.richText(10, this.game.world.height+120, 100, 'Agradecimientos a:', style);
    this.game.add.richText(10, this.game.world.height+160, 100, 'Nuestras madres', style);
    this.game.add.richText(10, this.game.world.height+180, 100, 'Carlos León Aznar', style);
    this.game.add.richText(10, this.game.world.height+220, 100, '¡Gracias por jugar!', style);

    backButton = this.game.world.add(new FramedButton(this.game.world, this.game, 179, 130, 'backIcon', 'backFrame', [{ callback: function () { this.MainMenuScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));

    //prueba cursor
    selector = this.game.add.sprite(50, 50, 'cursor');

    //para ir a fullscreen pulsar F11
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.add(this.goFullscreen, this);
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.halt();

    //music
    var music = this.game.add.audio('credits', 0.1, true);
    this.game.sound.stopAll();
    music.play();
  },
  update: function(){
    this.game.world.forEach(element => {
      element.y -=0.2;
    });
    backButton.y += 0.2;
  
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


module.exports = CreditsScene;
