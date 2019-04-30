'use strict';

var FramedButton = require('../interface/framedButton')

var selector;

var FullscreenScene = {
  IntroScene: function () {
    this.game.add.audio('button', 0.1).play();
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('intro'); }, this);
  },

  create: function () {
    //fadeIn
    this.camera.flash('#000000');

    var style = require('../../assets/fonts/style.json');




    this.game.add.richText(60, 39, 80, "fullscreen?", style);

    //Controles para cambiar de escenas
    this.acceptButton = this.game.world.add(new FramedButton(this.game.world, this.game, 60, 70, 'backIcon', 'backFrame', [{ callback: function () { this.game.scale.startFullScreen(false);this.IntroScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));
    this.ignoreButton = this.game.world.add(new FramedButton(this.game.world, this.game, 120, 70, 'backIcon', 'backFrame', [{ callback: function () { this.game.scale.stopFullScreen();this.IntroScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));


    //prueba cursor
    selector = this.game.add.sprite(50, 50, 'cursor');

    //music
    var music = this.game.add.audio('shoptheme', 0.1, true);
    this.game.sound.stopAll();
    music.play();
  },
  update: function () {
    //prueba cursor
    selector.x = this.game.input.x;
    selector.y = this.game.input.y;
  }
};


module.exports = FullscreenScene;
