'use strict'

var Character = require('./character');
var ActionPattern = require('./actionPattern');

var Enemy = function(game, x, y, name, stats, spriteSheet, actions, particles, seeker, pattern){
    Character.call(this, game, x, y, name, stats, spriteSheet, actions, particles);
    this.actionPattern = new ActionPattern(pattern, seeker, this);
    this.seeker = seeker;
    this._lastActionEvent;
    this.seeker.onDeath.add(function(){
        this.act = function () { 
            this.idle();
        };
        this.game.time.events.remove(this._lastActionEvent);
    },this);
    this.onDeath.add(function() {
        this.act = function () {};
        this.patternTimer.removeAll();
    }, this)
}

Enemy.prototype = Object.create(Character.prototype);
Enemy.prototype.constructor = Enemy;

Enemy.prototype.act = function() {
    this[this.actionPattern.nextAction](this.seeker);

    this._lastActionEvent = this.patternTimer.add(this[this.actionPattern.currentAction].totalTime()*1000, this.act, this);
    this.patternTimer.start();
    
}

Enemy.prototype.stop = function(){
    this.patternTimer.pause();
    this.animations.paused = true;
}

Enemy.prototype.start = function(){
    this.patternTimer.resume();
    this.animations.paused = false;
}

module.exports = Enemy;