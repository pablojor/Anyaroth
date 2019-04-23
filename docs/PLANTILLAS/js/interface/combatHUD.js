'use strict'

var EnemyCombatHUD = require('./enemyCombatHUD');
var SeekerCombatHUD = require('./seekerCombatHUD');
var FramedButton = require('./framedButton');
var OptionMenu = require('./optionMenu');
var RichText = require('./richText');

var CombatHUD = function (game, parent, x, y, seeker, enemy) {
    Phaser.Group.call(this, game, parent);
    this.x = x;
    this.y = y;
    this.frame = this.add(new Phaser.Image(game, 0, 0, 'interface'));
    this._seekerHUD = this.add(new SeekerCombatHUD(game, this, 0, 0, seeker, enemy));
    this._enemyHUD = this.add(new EnemyCombatHUD(game, this, 0, 0, seeker, enemy));
    this._pause = false;
    this._seeker = seeker;
    this._enemy = enemy;
    this.pauseButton = this.add(new FramedButton(this, game, 190, 2, 'pauseButton', 'pauseButtonFrame', [{ callback: CombatHUD.prototype._pause, context: this, arguments: [] }], 0xFFFFFF, 0x000000, 0x676767, 0x222222, 0x676767));
    this.pauseMenu = this.add(new OptionMenu(game, 40, 15, 120, 120, [
        ['hola', 10, 16, 'optionBack', 'optionFrame',
            [{ callback: CombatHUD.prototype._pause, context: this, arguments: [] }],
            0x000000, 0xFFFFFF, 0x5C5C5C, 0x111111, 0xAAAAAA,
            { leftButton: undefined, rightButton: undefined, upButton: undefined, downButton: undefined }],
        ['hola', 10, 30, 'optionBack', 'optionFrame',
            [{ callback: this.game.state.start, context: this.game.state, arguments: ['mainmenu'] }],
            0x000000, 0xFFFFFF, 0x5C5C5C, 0x111111, 0xAAAAAA,
            { leftButton: undefined, rightButton: undefined, upButton: undefined, downButton: undefined }],
    ], 'infoWindow', this));
    this.pauseMenu.visible = false;
    this.pauseMenu.add(new RichText(game, 0, 5, 120, 'PAUSA', { align: 'center' }, this));
    this.pauseMenu.add(new RichText(game, 0, 16, 120, 'VOLVER', { align: 'center' }, this));
    this.pauseMenu.add(new RichText(game, 0, 30, 120, 'IR AL MENU', { align: 'center' }, this));
}


CombatHUD.prototype = Object.create(Phaser.Group.prototype);
CombatHUD.prototype.constructor = CombatHUD;

CombatHUD.prototype._pause = function () {
    if (this._pause) {
        this._seeker.start();
        this._enemy.start();
        this.pauseMenu.visible = false;
        this._seekerHUD.unFreeze();
        this.pauseButton._button.inputEnabled = true;
    } else {
        this._seeker.stop();
        this._enemy.stop();
        this.pauseMenu.visible = true;
        this._seekerHUD.freeze();
        this.pauseButton._button.inputEnabled = false;
        this.pauseButton.changeFrameFrame('Out')
    }
    this._pause = !this._pause;
}

CombatHUD.prototype.deactivate = function () {
    this._seekerHUD.deactivate();
    this._enemyHUD.deactivate();
}

CombatHUD.prototype.activate = function () {
    this._seekerHUD.activate();
    this._enemyHUD.activate();
}

module.exports = CombatHUD;