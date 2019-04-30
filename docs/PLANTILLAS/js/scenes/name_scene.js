'use strict';

var FramedButton = require('../interface/framedButton')
var Seeker = require('../characters/seeker');
var DayManager = require('../manager/dayManager');
var selector;

var SettingsScene = {
  MainMenuScene: function () {
    this.game.add.audio('button', 0.1).play();
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('mainmenu'); }, this);
  },
  NewGame: function (seeker, name) {
    var dayManager = new DayManager(seeker, this.game);
    seeker.hp = seeker.stats.health*5;
    seeker.gems = 0;
    seeker.population = 50;
    seeker.totalGems = 100;
    seeker.day = 0;
    seeker.name = name;
    dayManager.newDay();
  },
  init: function (seeker) {
    this._tmpSeeker = seeker;
  },
  create: function () {
    //fadeIn
    this.camera.flash('#000000');

    var style = require('../../assets/fonts/style.json');

    this.game.add.image(0, 0, 'namebackground').alpha = 0.2;

    var emitter = this.game.add.emitter(100, 75, 200);
    emitter.alpha = 0.1;
    emitter.makeParticles('creationParticles', [0, 1, 2, 3, 4, 5]);
    emitter.minParticleSpeed.setTo(-100, -100);
    emitter.maxParticleSpeed.setTo(100, 100);
    emitter.setRotation(0, 0);
    emitter.gravity = 0;
    emitter.flow(20000, 100);

    var emitter2 = this.game.add.emitter(100, 75, 200);
    emitter2.alpha = 0.2;
    emitter2.makeParticles('creationParticles', [0, 1, 2, 3, 4, 5]);
    emitter2.minParticleSpeed.setTo(-100, -100);
    emitter2.maxParticleSpeed.setTo(100, 100);
    emitter2.setRotation(0, 0);
    emitter2.gravity = 0;
    emitter2.flow(20000, 100);

    var emitter3 = this.game.add.emitter(100, 75, 200);
    emitter3.alpha = 0.3;
    emitter3.makeParticles('creationParticles', [0, 1, 2, 3, 4, 5]);
    emitter3.minParticleSpeed.setTo(-100, -100);
    emitter3.maxParticleSpeed.setTo(100, 100);
    emitter3.setRotation(0, 0);
    emitter3.gravity = 0;
    emitter3.flow(20000, 100);

    this.game.add.richText(0, 5, 200, 'EL RITUAL HA COMENZADO.', style);
    this.game.add.richText(0, 16, 200, 'YA NO HAY VUELTA ATRAS.', style);
    this.game.add.richText(0, 34, 200, 'NOMBRA A TU BUSCADOR:', style);
    this.game.add.image(60, 108, 'textBox').alpha = 0.8;

    this.game.add.image(62, -30, this._tmpSeeker.spriteSheet);

    //this.backButton = this.game.world.add(new FramedButton(this.game.world, this.game, 179, 130, 'backIcon', 'backFrame', [{ callback: function () { this.MainMenuScene(); }, context: this, arguments: [] }], 0x676767, 0xffffff, 0x000000, 0x222222, 0x676767));
    this.hola = this.game.add.inputField(40, 100, {
      font: '10px Minecraft',
      width: 150,
      padding: 8,
      borderWidth: 1,
      borderColor: '#FFFFFF',
      borderRadius: 6,
      placeHolder: 'NOMBRE',
      textAlign: 'center',
      fillAlpha: 0,
      width: 100,
      height: 1,
      selectionColor: '#FF00FF',
      cursorColor: '#FFFFFF'
    });
    this.hola.text.style.fill = '#FFFFFF';
    this.hola.domElement.setMax(7, 0);
    this.hola.cursor.y += 2;
    this.hola.input.useHandCursor = false;
    //prueba cursor
    selector = this.game.add.sprite(50, 50, 'cursor');

    //para ir a fullscreen pulsar F11
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.add(this.goFullscreen, this);
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.halt();

    //input name
    this.game.input.keyboard.addKey(Phaser.Keyboard.ENTER).onDown.add(function (key, seeker, name) {
      if (this.hola.value !== ''){
        this.NewGame(seeker, this.hola.value);
        this.hola.destroy();
    }
    }, this, 0, this._tmpSeeker);

    this.hola.blockInput = false;
    this.hola.focus = false;

    PhaserInput.onKeyboardClose.add(function (seeker, name) {
      if (this.hola.value !== ''){
        this.NewGame(seeker, this.hola.value);
        this.hola.destroy();
      }
    }, this, 0, this._tmpSeeker);
    
    this.hola.focusOutOnEnter = false;


  },
  update: function () {
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
