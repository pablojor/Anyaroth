'use strict';

//PREGUNTAS
// - ¿Hay alguna manera para evitar la carga repetida? Quiero que, cuando tenga absolutamente todo cargado, se de a start.
//   y poner pantalla de carga(sin conocer porcentaje jeje).
//BUGS
// ActionBar


var IntroScene = require('./scenes/intro_scene.js');
var MainMenuScene = require('./scenes/mainmenu_scene.js');
var CombatScene = require('./scenes/combat_scene.js');
var EventScene = require('./scenes/event_scene.js');
var CreditsScene = require('./scenes/credits_scene.js');
var SettingsScene = require('./scenes/settings_scene.js');
var ShopScene = require('./scenes/shop_scene.js');
var CreationScene = require('./scenes/creation_scene.js');
var NameScene = require('./scenes/name_scene.js');
var FullscreenScene = require('./scenes/fullscreen_scene.js');
var TextFunctions = require('./interface/textFunctions');
 var webFontLoading = {
  active: function() {
    var game = new Phaser.Game(200, 150, Phaser.AUTO, 'game');
    webFontLoading.game = game;
    game.state.add('boot', BootScene);
    game.state.add('preloader', PreloaderScene);
    game.state.add('intro', IntroScene);
    game.state.add('mainmenu', MainMenuScene);
    game.state.add('combat', CombatScene);
    game.state.add('event', EventScene);
    game.state.add('credits', CreditsScene);
    game.state.add('settings', SettingsScene);
    game.state.add('shop', ShopScene);
    game.state.add('creation', CreationScene);
    game.state.add('name', NameScene);
    game.state.add('fullscreen', FullscreenScene);
    game.state.start('boot');
  },
  custom: {
    families: ['Minecraft'],
    urls: ["assets/fonts/webFonts/stylesheet.css"]
  }
};

var WebFont = require('webfontloader');


var BootScene = {
  preload: function () {
    require('./gameFactory')(Phaser);
    // scale the game 4x
    this.game.scale.scaleMode = Phaser.ScaleManager.USER_SCALE;
    this.game.scale.setUserScale(4, 4);
    // enable crisp rendering
    this.game.renderer.renderSession.roundPixels = true;
    Phaser.Canvas.setImageRenderingCrisp(this.game.canvas);

    // load here assets required for the loading screen
    this.game.load.image('preloader_bar', 'temporal%20images/preloader_bar.png');
  },

  create: function () {
    this.game.state.start('preloader');
  }
};


var PreloaderScene = {
  preload: function () {
    this.loadSignal = new Phaser.Signal();
    this.loadingText = this.game.add.richText(50, 120, 100, TextFunctions.Tremble(2,5,1,'Cargando...'), require('../assets/fonts/style.json'));
    this.loadingBar = this.game.add.reactiveBar(this.game.world,15,135,'preloader_bar',function(){
      return  this._audioLoad*0.88+this._otherLoad*0.12;
    },this,this.loadSignal);
    this.loadingBar.width = 170;
    this._audioLoad = 0;
    this._otherLoad = 0;
    this.game.load.onFileComplete.add(function(progress, file, key, success){
      this._otherLoad = progress;
      this.loadSignal.dispatch();
    },this);
    this.load.onFileComplete.add(function(progress, file, key, success){
      this._audioLoad = progress;
      this.loadSignal.dispatch();
    },this);
    // TODO: load here the assets for the game
    //IMAGES
        this.game.load.script('filter', 'https://cdn.rawgit.com/photonstorm/phaser-ce/master/filters/Pixelate.js');
      //INTRO
        this.game.load.spritesheet('intro1', 'assets/images/intro/intro1.png', 57, 107);
        this.game.load.spritesheet('intro2', 'assets/images/intro/intro2.png', 57, 80);
        this.game.load.spritesheet('intro3', 'assets/images/intro/intro3.png', 140, 80);
        this.game.load.spritesheet('intro4', 'assets/images/intro/intro4.png', 140, 80);
      //INTERFACE
        this.game.load.spritesheet('logo', 'assets/images/interface/logo.png', 61, 69);
        this.game.load.spritesheet('infoWindow', 'assets/images/interface/infoWindow.png', 5, 5);
        this.game.load.image('itemFrame','assets/images/interface/itemFrame.png');
        this.game.load.image('emptyItem','assets/images/interface/emptyItem.png');
        this.game.load.image('backIcon','assets/images/interface/backIcon.png');
        this.game.load.image('backFrame','assets/images/interface/backFrame.png');
        this.game.load.image('title','assets/images/interface/title.png');
        this.game.load.image('statPoint','assets/images/interface/statPoint.png');
        this.game.load.image('emptyStatPoint','assets/images/interface/emptyStatPoint.png');
        this.game.load.image('blockedIcon','assets/images/interface/blockedIcon.png');
        this.game.load.image('textBox','assets/images/interface/textBox.png');
        //Event Images
        this.game.load.image('fungiCaveAttackEventImage','assets/images/interface/fungiattack_eventimage.png');
        this.game.load.image('ritualEventImage','assets/images/interface/ritual_eventimage.png');
        this.game.load.image('ritualAcceptedEventImage','assets/images/interface/ritualaccepted_eventimage.png');
        this.game.load.image('ritualDeniedEventImage','assets/images/interface/ritualdenied_eventimage.png');
        this.game.load.image('eventImageError','assets/images/interface/eventImageError.png');
        this.game.load.image('undershineEventImage','assets/images/interface/undershine_eventimage.png');
        this.game.load.image('spiderEventImage','assets/images/interface/spider_eventimage.png');
        this.game.load.image('spiderAttackEventImage','assets/images/interface/spiderattack_eventimage.png');
        this.game.load.image('fungiCaveEventImage','assets/images/interface/fungicave_eventimage.png');
        this.game.load.image('fungiCavePotionEventImage','assets/images/interface/potionfound_eventimage.png');
        this.game.load.image('lordRagno1EventImage','assets/images/interface/lordragno_eventimage.png');
        this.game.load.image('lordRagno2EventImage','assets/images/interface/lordragno2_eventimage.png');
        this.game.load.image('lordRagno3EventImage','assets/images/interface/lordragno3_eventimage.png');
        
        
        //Actions Bar
        this.game.load.image('actionsBarFrame','assets/images/interface/actionsBarFrame.png');
        this.game.load.image('actionsBarBack','assets/images/interface/actionsBarBack.png');
        this.game.load.image('actionsBarShadow','assets/images/interface/actionsBarShadow.png');
        this.game.load.image('blockBar','assets/images/interface/blockBar.png'); 
        this.game.load.image('thornsBlockBar','assets/images/interface/thornsBlockBar.png');
        this.game.load.image('attackBar','assets/images/interface/attackBar.png');
        this.game.load.image('unknownBar','assets/images/interface/unknownBar.png');
        this.game.load.image('idleBar','assets/images/interface/idleBar.png');
        //HUDs
        this.game.load.image('interface','assets/images/interface/combatinterfaceback.png');
        this.game.load.image('eventinterface','assets/images/interface/eventinterfaceback.png');
        this.game.load.image('creationinterface','assets/images/interface/creationinterface.png');
        //HUDs scroll
        this.game.load.spritesheet('sliderBackground','assets/images/interface/sliderbackground.png',6,5);
        this.game.load.spritesheet('slider','assets/images/interface/slider.png',6,3);
        //Cursor
        this.game.load.spritesheet('cursor','assets/images/interface/cursor.png',7,7);
        //HealthBar
        this.game.load.image('healthBar','assets/images/interface/healthBar.png');
        this.game.load.image('damageBar','assets/images/interface/damageBar.png');
        this.game.load.image('emptyBar','assets/images/interface/emptyBar.png');
        this.game.load.image('healBar','assets/images/interface/healBar.png')
        this.game.load.image('frameBar','assets/images/interface/frameBar.png');
        //Action Icon
        this.game.load.image('attackIcon','assets/images/interface/attackIcon.png');
        this.game.load.image('blockIcon','assets/images/interface/blockIcon.png');
        this.game.load.image('ultimateIcon','assets/images/interface/ultimateIcon.png');
        //Items Bag
        this.game.load.image('itemIcon','assets/images/interface/itemIcon.png');
        this.game.load.image('itemIcon2','assets/images/interface/itemIcon2.png');
        //Items Shop
        this.game.load.image('shopItemIcon','assets/images/interface/shopItemIcon.png');
        //Stats Icons
        this.game.load.image('damageIcon','assets/images/interface/damageIcon.png');
        this.game.load.image('defenseIcon','assets/images/interface/defenseIcon.png');
        this.game.load.image('speedIcon','assets/images/interface/speedIcon.png');
        this.game.load.image('healthIcon','assets/images/interface/healthIcon.png');
        this.game.load.image('perceptionIcon','assets/images/interface/perceptionIcon.png');
        this.game.load.image('gemIcon','assets/images/interface/gemIcon.png');
        this.game.load.image('villageGemIcon','assets/images/interface/villageGemIcon.png');
        this.game.load.image('populationIcon','assets/images/interface/populationIcon.png');
        //Buttons
        this.game.load.spritesheet('button','assets/images/interface/button.png',32,32);
        this.game.load.image('actionFrame', 'assets/images/interface/actionFrame.png');
        this.game.load.image('optionBack','assets/images/interface/optionback.png');
        this.game.load.image('optionFrame','assets/images/interface/optionFrame.png');
        this.game.load.image('pauseButton','assets/images/interface/pauseButton.png');
        this.game.load.image('pauseButtonFrame','assets/images/interface/pauseButtonFrame.png');
        this.game.load.spritesheet('shop','assets/images/interface/shop.png',51,64);
        this.game.load.spritesheet('shopFrame', 'assets/images/interface/shopFrame.png');
        this.game.load.spritesheet('door', 'assets/images/interface/door.png',27,49);
        this.game.load.spritesheet('doorFrame', 'assets/images/interface/doorFrame.png');
        this.game.load.spritesheet('settings', 'assets/images/interface/settings.png',24,53);
        this.game.load.spritesheet('settingsFrame', 'assets/images/interface/settingsFrame.png');
        this.game.load.spritesheet('tavern', 'assets/images/interface/tavern.png',47,23);
        this.game.load.spritesheet('tavernFrame', 'assets/images/interface/tavernFrame.png');
        this.game.load.spritesheet('crystal', 'assets/images/interface/crystal.png',39,65);
        this.game.load.spritesheet('crystalFrame', 'assets/images/interface/crystalFrame.png');
        this.game.load.image('arrow', 'assets/images/interface/arrow.png');
        this.game.load.image('arrowFrame', 'assets/images/interface/arrowFrame.png');
        this.game.load.image('ritualButton', 'assets/images/interface/ritualButton.png');
        this.game.load.image('ritualFrame', 'assets/images/interface/ritualFrame.png');

      //BACKGROUNDS
      this.game.load.image('mainmenubackground', 'assets/images/backgrounds/mainmenubackground.png');
      this.game.load.image('watercombatbackground', 'assets/images/backgrounds/watercombatbackground.png');
      this.game.load.image('combatbackground', 'assets/images/backgrounds/combatbackground.png');
      this.game.load.image('firecombatbackground', 'assets/images/backgrounds/firecombatbackground.png');
      this.game.load.image('eventbackground', 'assets/images/backgrounds/eventbackground.png');
      this.game.load.image('shines', 'assets/images/backgrounds/shines.png');
      this.game.load.image('creationbackground', 'assets/images/backgrounds/creationbackground.png');
      this.game.load.image('namebackground', 'assets/images/backgrounds/namebackground.png');
      //PARTICLES
      this.game.load.image('redBlood','assets/images/particles/redBlood.png');
      this.game.load.image('greenBlood','assets/images/particles/greenBlood.png');
      this.game.load.image('blueBlood','assets/images/particles/blueBlood.png');
      this.game.load.image('cianBlood','assets/images/particles/cianBlood.png');
      this.game.load.spritesheet('crystalShines','assets/images/particles/crystalShines.png',3,3);
      this.game.load.spritesheet('smoke','assets/images/particles/smoke.png',4,4);
      this.game.load.spritesheet('creationParticles','assets/images/particles/creationParticles.png',8,8);
      //CHARACTERS
        //Seeker
        this.game.load.spritesheet('seekerBruteAnimations','assets/images/seeker/seekerBruteAnimations.png',80,120);
        this.game.load.spritesheet('seekerHarpyAnimations','assets/images/seeker/seekerHarpySiluette.png',80,120);
        this.game.load.spritesheet('seekerWarlockAnimations','assets/images/seeker/seekerWarlockSiluette.png',80,120);
        this.game.load.spritesheet('seekerBruteSiluette','assets/images/seeker/seekerBruteSiluette.png',80,120);
        this.game.load.spritesheet('seekerHarpySiluette','assets/images/seeker/seekerHarpySiluette.png',80,120);
        this.game.load.spritesheet('seekerWarlockSiluette','assets/images/seeker/seekerWarlockSiluette.png',80,120);
        //Enemies
        this.game.load.spritesheet('lordRagnoAnimations', 'assets/images/enemies/lordRagnoAnimations.png',80,120);
        this.game.load.spritesheet('fungiAnimations', 'assets/images/enemies/fungiAnimations.png',80,120);
        this.game.load.spritesheet('spiderAnimations', 'assets/images/enemies/spiderAnimations.png',80,120);
    //SOUNDS
      //Effects
      this.load.audio('attacking', ['assets/sounds/attacking.wav']);
      this.load.audio('preAttacking', ['assets/sounds/preAttacking.wav']);
      this.load.audio('blocking', ['assets/sounds/blocking.wav']);
      this.load.audio('button', ['assets/sounds/buttonPressed.wav']);
      //Music
      this.load.audio('bosstheme', ['assets/music/bosstheme.mp3']);
      this.load.audio('firetheme', ['assets/music/firetheme.mp3']);
      this.load.audio('shoptheme', ['assets/music/shoptheme.mp3']);
      this.load.audio('watertheme', ['assets/music/watertheme.mp3']);
      this.load.audio('credits', ['assets/music/creditstheme.mp3']);
      this.load.audio('mainmenu', ['assets/music/mainmenutheme.mp3']);
      this.load.audio('intro', ['assets/music/introtheme.mp3']);
      this.load.audio('logo', ['assets/music/logo.mp3']);
      this.load.audio('credits', ['assets/music/creditstheme.mp3']);
      this.load.audio('mainmenutheme', ['assets/music/mainmenutheme.mp3']);
      this.load.audio('textfire', ['assets/music/textfire.mp3']);
      this.load.audio('textwater', ['assets/music/textwater.mp3']);
      this.load.audio('textboss', ['assets/music/textboss.mp3']);

    //PLUGINS
      this.game.add.plugin(PhaserInput.Plugin);
  },

  create: function () {
      this.game.scale.fullScreenScaleMode = Phaser.ScaleManager.SHOW_ALL;
      PreloaderScene.game.state.start('intro');
      
  }

};
WebFont.load(webFontLoading);

window.onload = function () {
  

};