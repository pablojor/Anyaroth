'use strict';

var selector;

var Stats = require('../characters/stats');
var EventScene = {
  MainMenuScene: function () {
    this.game.state.start('mainmenu');

  },
  init: function(seeker, dayManager, text, image, options, music){
    this._seeker = seeker;
    this._dayManager = dayManager;
    this._text = text;
    this._image = image;
    this._options = options;
    this._music = music;
  },
  create: function () {
    //fadeIn
    this.camera.flash(0x000000);

    var style = {
                  "font": "Minecraft",
                  "fill": "#fff",
                  "fontSize": 10,
                  "align":"center"
                }
    
    //render background
    this.game.add.sprite(0, 0, 'eventbackground');

    this.seeker = this.game.add.seeker( 0, -8, this._seeker.name, this._seeker.stats, this._seeker.items, this._seeker.spriteSheet, this._seeker.actions);
    this.seeker.hp = this._seeker.hp;
    this.seeker.gems = this._seeker.gems;
    this.seeker.population = this._seeker.population;
    this.seeker.totalGems = this._seeker.totalGems;
    this.seeker.day = this._seeker.day;
    this.HUD = this.game.add.eventHUD(this.seeker, this._dayManager, this._text, this._options, this._image);

    //music
    if(this._music!=''){
    var music = this.game.add.audio(this._music, 0.1, true);
    this.game.sound.stopAll();
    music.play();
    }

    //para ir a fullscreen pulsar F11
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.add(this.goFullscreen, this);
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.halt();

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

  goFullscreen: function() {

    if (this.game.scale.isFullScreen) {
      this.game.scale.stopFullScreen();
    }
    else {
      this.game.scale.startFullScreen(false);
    }
  
  }
};


module.exports = EventScene;
