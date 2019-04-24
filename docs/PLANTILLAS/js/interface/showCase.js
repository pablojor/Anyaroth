'use strict'

var StatMarker = require('./statMarker');
var RichText = require('./richText');

var ShowCase = function(game, parent, x, y, characters) {
    Phaser.Group.call(this,game,parent);
    
    let style = { "font": "Minecraft", "fill": "#FFFFFF", "fontSize": 10, "align": 'center' };
    let style2 = { font: 'Minecraft', fill: '#000000', fontSize: 10 };

    this.x = x;
    this.y = y;
    this._healthMarker = this.add(new StatMarker(game, this,22,76,2,5,0,'statPoint','emptyStatPoint',0xb60000));
    this._damageMarker = this.add(new StatMarker(game, this,22,91,2,5,0,'statPoint','emptyStatPoint',0xcf6e1a));
    this._defenseMarker = this.add(new StatMarker(game, this,22,106,2,5,0,'statPoint','emptyStatPoint',0x14879f));
    this._speedMarker = this.add(new StatMarker(game, this,22,121,2,5,0,'statPoint','emptyStatPoint',0xe5d40a));
    this._perceptionMarker = this.add(new StatMarker(game, this,22,136,2,5,0,'statPoint','emptyStatPoint',0x4ce742));
    this._characters = characters;
    this._nameText = this.add( new RichText(game, 0, 56, 200, "", style));


    this._attackIcon = this.add(new Phaser.Image(game,64,75+2,''));
    this._attackText = this.add( new RichText(game, 86, 97-24, 110, "", style2, this));
    this._blockIcon = this.add(new Phaser.Image(game,64,100+2,''));
    this._blockText = this.add( new RichText(game,86, 123-24, 110, "", style2, this));
    this._ultimateIcon = this.add(new Phaser.Image(game,64,125+2,''));
    this._ultimateText = this.add( new RichText(game,86, 148-24, 110, "", style2, this));
    this._image = this.add(new Phaser.Image(game,62,-70,''));
    this._reemplaceImage = this.add(new Phaser.Image(game,-80,-70,''));
    this._current = 0;
    this._image.loadTexture('seeker'+Object.keys(this._characters)[this._current]+'Animations');
    
    this.onBeginRotation = new Phaser.Signal();
    this.onEndRotation = new Phaser.Signal();
    ShowCase.prototype.showCharacter.call(this, Object.keys(this._characters)[this._current]);
}

ShowCase.prototype = Object.create(Phaser.Group.prototype);
ShowCase.prototype.constructor = ShowCase;

ShowCase.prototype.rotate = function(direction) {
    if(direction!==0){
        this.onBeginRotation.dispatch();
        let newdirection = direction<0?direction+Object.keys(this._characters).length: direction;
        let oldS = Object.keys(this._characters)[this._current];
        this._current = (this._current+newdirection)%Object.keys(this._characters).length;
        let newS = Object.keys(this._characters)[this._current];
        this._image.loadTexture('seeker'+newS+'Siluette');
        this._image.x = direction > 0 ? -80 : 230;
        this._reemplaceImage.loadTexture('seeker'+oldS+'Siluette');
        this._reemplaceImage.x = 62;
        this.game.add.tween(this._image).to({x:[direction > 0 ? -80 : 230,62]}, 400,"Sine.easeInOut", true, 0);
        this.game.add.tween(this._reemplaceImage).to({x:[62,direction > 0 ? 230 : -80]}, 400,"Sine.easeInOut", true, 0).onComplete.
        add(function(){
            ShowCase.prototype.showCharacter.call(this, Object.keys(this._characters)[this._current]);
            this.onEndRotation.dispatch();
        }, this);
    }
}

ShowCase.prototype.showCharacter = function(character) {
    this._nameText.text = character.toUpperCase();
    if(this._characters[character].avaliable) {
        this._attackIcon.loadTexture(this._characters[character].attack.icon);
        this._attackText.text = this._characters[character].attack.description;
        this._blockIcon.loadTexture(this._characters[character].block.icon);
        this._blockText.text = this._characters[character].block.description;
        this._ultimateIcon.loadTexture(this._characters[character].ultimate.icon);
        this._ultimateText.text = this._characters[character].ultimate.description;
        this._image.loadTexture('seeker'+character+'Animations');
        this._healthMarker.currentPoints = this._characters[character].stats.health;
        this._damageMarker.currentPoints = this._characters[character].stats.damage;
        this._defenseMarker.currentPoints = this._characters[character].stats.defense;
        this._speedMarker.currentPoints = this._characters[character].stats.speed;
        this._perceptionMarker.currentPoints = this._characters[character].stats.perception;
    } else {

        this._attackIcon.loadTexture('blockedIcon');
        this._attackText.text = '?????\n?????';
        this._blockIcon.loadTexture('blockedIcon');
        this._blockText.text = '?????\n?????';
        this._ultimateIcon.loadTexture('blockedIcon');
        this._ultimateText.text = '?????\n?????';
        this._image.loadTexture('seeker'+character+'Siluette');
        this._healthMarker.currentPoints = 0;
        this._damageMarker.currentPoints = 0;
        this._defenseMarker.currentPoints = 0;
        this._speedMarker.currentPoints = 0;
        this._perceptionMarker.currentPoints = 0;
    }
}

ShowCase.prototype.isAvaliable = function(){
    return this._characters[Object.keys(this._characters)[this._current]].avaliable;
}

ShowCase.prototype.character = function() {
    return this._characters[Object.keys(this._characters)[this._current]];
}

module.exports = ShowCase;