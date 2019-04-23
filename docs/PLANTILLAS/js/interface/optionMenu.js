'use strict';

var ButtonMenu = require('./buttonMenu');
var WindowFrame = require('./windowFrame');

var OptionMenu = function (game, x, y, width, height, buttonsMenu, windowSprite, parent) {
    Phaser.Group.call(this, game, parent);
    this.x = x;
    this.y = y;
    this.add(new WindowFrame(game, this, 0, 0, width, height, windowSprite));
    buttonsMenu.forEach(element => {
        let b = this.add(new ButtonMenu(this, this.game, ...element.slice(0, element.length - 1)));
        b.onInputOver.add(this.over, this, [b]);
    }, this);
    buttonsMenu.forEach(element => {
        let child = this.children.find(function (element2) { return element2.name === element[0] });

        child.leftButton =
            this.children.find(function (element2) { return element2.name === element[element.length - 1].leftButton });
        child.rightButton =
            this.children.find(function (element2) { return element2.name === element[element.length - 1].rightButton });
        child.upButton =
            this.children.find(function (element2) { return element2.name === element[element.length - 1].upButton });
        child.downButton =
            this.children.find(function (element2) { return element2.name === element[element.length - 1].downButton });
    }, this);
    this.currentButton = this.children[0]; //currentButton no está bien asignado
}

OptionMenu.prototype = Object.create(Phaser.Group.prototype);
OptionMenu.prototype.constructor = OptionMenu;


OptionMenu.prototype.goLeft = function() {
    if (this.currentButton.goLeft() !== undefined) {
        this.currentButton.onInputOut.dispatch();
        this.currentButton = this.currentButton.goLeft();
        this.currentButton.onInputOver.dispatch();
    }
}
OptionMenu.prototype.goRight = function() {
    if (this.currentButton.goRight() !== undefined) {
        this.currentButton.onInputOut.dispatch();
        this.currentButton = this.currentButton.goRight();
        this.currentButton.onInputOver.dispatch();
    }
}
OptionMenu.prototype.goUp = function() {
    if (this.currentButton.goUp() !== undefined) {
        this.currentButton.onInputOut.dispatch();
        this.currentButton = this.currentButton.goUp();
        this.currentButton.onInputOver.dispatch();
    }
}
OptionMenu.prototype.goDown = function() {
    if (this.currentButton.goDown() !== undefined) {
        this.currentButton.onInputOut.dispatch();
        this.currentButton = this.currentButton.goDown();
        this.currentButton.onInputOver.dispatch();
    }
}

OptionMenu.prototype.over = function(button) {
    if (this.children.includes(button) && this.currentButton !== button) {
        this.currentButton.onInputOut.dispatch();
        this.currentButton = button;
    }
}

OptionMenu.prototype.select = function() {
    this.currentButton.select();
}
OptionMenu.prototype.back = function() {
    this.buttons.forEach(element => {
        element.deactivate();
    });
}

OptionMenu.prototype.enter = function() {
    this.buttons.forEach(element => {
        element.activate();
    });
}

module.exports = OptionMenu;