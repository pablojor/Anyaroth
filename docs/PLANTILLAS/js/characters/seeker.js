'use strict';

var Character = require('./character.js');
var SeekerActionFactory = require('./actionSeekerFactory.js');
var Item = require('./item');
var Items = require('../../assets/items/items');
/**
 * 
 */
/**
 * 
 * @param {Phaser.Game} game - 
 * @param {number} x - 
 * @param {number} y -
 * @param {string} name -
 * @param {Stats} stats -
 * @param {string} spriteSheet -
*/
var Seeker = function (game, x, y, name, stats, items, spriteSheet, actions, particles) {
    Character.call(this, game, x, y, name, stats, spriteSheet,[], particles);
    this.addAction = new SeekerActionFactory(this);
    
    for(var action in actions){
        this.addAction[action](...actions[action]);
    }
    this.day = 0;
    this.gems = 42;
    this.population = 103;
    this.totalGems = 569;
    this.items = new Array(6);
    for(let i = 0; i < 6; i++){
        this.items[i] = Items[items[i]];
    }
    this._timePaused = 0;
}

Seeker.prototype = Object.create(Character.prototype);
Seeker.prototype.constructor = Seeker;

Seeker.prototype.stop = function(){
    for(let action in this.coolDown){
        this.coolDown[action].pause();
    }
    this.coolDownTimer.pause();
    this.animations.paused = true;
    this._timePaused = Date.now();
}

Seeker.prototype.start = function(){
    this._timePaused = Date.now() - this._timePaused;

    for(let action in this.coolDown){
        this.coolDown[action].nexTick+=this._timePaused;
        this.coolDown[action].resume();
    }
    this.coolDownTimer.resume();
    this.animations.paused = false;
}

module.exports = Seeker;