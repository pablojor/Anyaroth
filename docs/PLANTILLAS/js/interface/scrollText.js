'use strict'

var ReactiveRichText = require('./reactiveRichText');

var ScrollText = function(game, parent,x,y,width,height,text, style) {
    Phaser.Group.call(this, game, parent);
    this.x = x;
    this.y = y;
    this._width = width;
    this._height = height;
    this._maxHeight = height;
    this._text = this.add(new ReactiveRichText(game,0,0,width,text,style,this, []));
    this._mask = this.add(new Phaser.Graphics(game, 0, 0));
    this._mask.beginFill(0xffffff);
    this._mask.drawRect(0,0,width,height);
    this._mask.endFill();
    this._text.mask = this.mask;
    this.onReachEnd = new Phaser.Signal();
    this.onReachBegin = new Phaser.Signal();
}

ScrollText.prototype = Object.create(Phaser.Group.prototype);
ScrollText.prototype.constructor = ScrollText;

ScrollText.prototype.move = function(percentage) {
    this._text.y = -percentage*(this._text.height - this._maxHeight)/100;
    if(this._text.y >= 0 ) {
        this._text.y = 0;
        this.onReachBegin.dispatch();
    } else if(this._text.y <= this._maxHeight - this._text.height) {
        this._text.y = this._maxHeight - this._text.height;
        this.onReachEnd.dispatch();
    }
    
}

Object.defineProperty(ScrollText.prototype, 'text',{
    set: function(text) {
        this._text.text = text;
        this._text.y = 0;
    }
});
module.exports = ScrollText;
