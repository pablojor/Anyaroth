'use strict';

var selector;

var IntroScene = {
  MainMenuScene: function () {
    this.game.add.audio('button', 0.1).play();
    this.game.camera.fade('#000000');
    this.game.camera.onFadeComplete.add(function () { this.game.state.start('mainmenu'); }, this);
  },

  appear(object, duration, delay, funct) {
    object.alpha = 0;

    var tween = this.game.add.tween(object).to({ alpha: 1 }, 2000, Phaser.Easing.Linear.None, true, delay);
    tween.onComplete.add(function () {
      if (funct && (typeof funct == "function")) {
        funct();
      }
      this.game.add.tween(object).to({ alpha: 0 }, 2000, Phaser.Easing.Linear.None, true, duration);
    }
      , this);
  },

  create: function () {
    var style = require('../../assets/fonts/style.json');
    //color de background
    this.game.stage.backgroundColor = "#31261a";
    //stop music
    this.game.sound.stopAll();

    //logo music
    var logomusic = this.game.add.audio('logo', 0.1, false);
    logomusic.play();

    //intro music
    var intro = this.game.add.audio('intro', 0.1, false);
    this.game.add.tween(intro).to({}, 7500, "Linear", true, 7500).onStart.add(function () { intro.play(); }, this);

    this.appear(this.game.add.sprite(70, 30, 'logo')
      .animations.add('play', Array.apply(null, { length: 22 }).map(Function.call, Number))
      ._parent.play('play', 7)._parent, 4000);
    this.appear(this.game.add.richText(60, 100, 80, "TURING'S SONG STUDIOS", style), 1000, 3000);

    this.appear(this.game.add.richText(60, 40, 80, "Cuenta la leyenda...", style), 2000, 9000);
    this.appear(this.game.add.richText(60, 80, 80, "...que hace mucho tiempo...", style), 2000, 10000);

    var intro1 = this.game.add.sprite(20, 20, 'intro1');
    intro1.animations.add('play', [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]);
    this.appear(intro1, 3000, 17000, function () { intro1.play('play', 4) });
    this.appear(this.game.add.richText(90, 50, 100, "...una gran bola de fuego alimentaba al mundo con sus rayos desde el cielo...", style), 3000, 17000);

    var intro2 = this.game.add.sprite(130, 30, 'intro2');
    intro2.animations.add('play', [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
    this.appear(intro2, 3000, 24000, function () { intro2.play('play', 6) });
    this.appear(this.game.add.richText(10, 50, 100, "...y que las gemas de luz no eran necesarias para poder sobrevivir.", style), 3000, 24000);

    var intro3 = this.game.add.sprite(30, 10, 'intro3');
    intro3.animations.add('play', [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24]);
    this.appear(intro3, 9000, 32000, function () { intro3.play('play', 6) });
    this.appear(this.game.add.richText(25, 100, 150, "Tras la Gran Guerra, el suelo dónde alzamos nuestros reinos...", style), 3000, 32000);
    this.appear(this.game.add.richText(25, 132, 150, "...desapareció.", style), 3000, 38000);

    var intro4 = this.game.add.sprite(30, 60, 'intro4');
    intro4.animations.add('play', [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24]);
    this.appear(intro4, 11000, 46000, function () { intro4.play('play', 6) });
    this.appear(this.game.add.richText(25, 10, 150, "Los spilianos somos los únicos supervivientes. Hemos evolucionado para no ser los últimos, pero...", style), 3000, 46000);
    this.appear(this.game.add.richText(25, 10, 150, "...las gemas de luz escasean en la aldea, y cada vez hay menos spilianos...", style), 3000, 54000);

    this.appear(this.game.add.richText(50, 50, 100, "Necesitamos tu ayuda. Has sido elegido por el Gran Cristal.", style), 3000, 62000);
    this.appear(this.game.add.richText(50, 60, 100, "Por favor... no nos falles...", style), 3000, 70000);

    //espera a que acabe intro
    this.game.time.events.add(Phaser.Timer.SECOND * 80, this.MainMenuScene, this);

    //para ir a fullscreen pulsar F11
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.add(this.goFullscreen, this);
    this.game.input.keyboard.addKey(Phaser.Keyboard.F11).onDown.halt();

    

    //this.game.add.optionMenu([['botonDeAbajo',165,115,'button',this.MainMenuScene,this,1,0,2,1,{}]]);


    //prueba cursor
    //selector = this.game.add.sprite(50, 50, 'cursor');

    //Controles para cambiar de escenas
    this.game.input.keyboard.addKey(Phaser.Keyboard.SPACEBAR).onDown.add(this.MainMenuScene, this);
    this.game.input.keyboard.addKey(Phaser.Keyboard.ENTER).onDown.add(this.MainMenuScene, this);
    this.game.input.keyboard.addKey(Phaser.Keyboard.ESC).onDown.add(this.MainMenuScene, this);
  },
  update: function () {
    //prueba cursor
    //selector.x = this.game.input.x;
    //selector.y = this.game.input.y;
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




module.exports = IntroScene;
