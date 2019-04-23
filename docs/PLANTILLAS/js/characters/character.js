/**
* @author       Carlos Durán Domínguez <carduran@ucm.es>
* @copyright    2018 Turing's Songs Studios© 
* @license      {}
*/

'use strict';

var ActionFactory = require('./actionFactory');
var ParticleFactory = require('./particleFactory.js');
var Stats = require('./stats');
/**
 * A Character is an instance...jeje
*/

/**
 * 
 * @param {Phaser.Game} game - 
 * @param {number} x - 
 * @param {number} y -
 * @param {string} name -
 * @param {Stats} stats -
 * @param {string} spriteSheet -
 * @param {string, arguments} actions -
*/
var Character = function (game, x, y, name, stats, spriteSheet, actions, particles) {
    Phaser.Sprite.call(this, game, x, y, spriteSheet)
    this._name = name;
    this.onNameChange = new Phaser.Signal();
    this.stats = new Stats(stats.damage,stats.defense,stats.speed,stats.health,stats.perception,stats.tempDamage,stats.tempDefense,stats.tempSpeed,stats.tempHealth,stats.tempPerception);
    this.stats.onSpeedChange.add(function(){
        this.animations.currentAnim.delay = 1000 /this.stats.frameRate;
    }, this)
    
    this.hp = stats.currentHp===undefined?this.stats.maxHp:stats.currentHp;
    this.game = game;
    this.isBlocking = false;
    //Signals 
    this.onHpChange = new Phaser.Signal();
    this.onRest = new Phaser.Signal();
    this.onDeath = new Phaser.Signal();
    this.onHit = new Phaser.Signal();
    //ref to Factories
    this.addAction = new ActionFactory(this);
    this.addParticle = new ParticleFactory(this);

    for(var action in actions){
        this.addAction[action](...actions[action]);
    }
    
    for(var particle in particles){
        this.addParticle[particle](...particles[particle]);
    }
}

Character.prototype = Object.create(Phaser.Sprite.prototype);
Character.prototype.constructor = Character;

/**
 * 
 * @param {number} damage -
 */
Character.prototype.hit = function (damage, attacker) {
    this.onHit.dispatch(attacker, damage);
    this.hurt(damage);
}

/**
 * 
 * @param {number} damage -
 */
Character.prototype.hurt = function (damage) {
    damage = this.isBlocking ? this.stats.damagedNotBlocked(damage) : damage;
    this.game.camera.shake(damage / 200, damage * 20);
    this.hp = Math.max(0, this.hp - damage);
    this.onHpChange.dispatch(-damage);
    if (damage > 0) {
        this._damaged(damage);
    }
    if (this.hp === 0) {
        this.die();
    }
}

Character.prototype.heal = function(heal) {
    this.hp = Math.min(this.stats.maxHp,this.hp+heal);
    this.onHpChange.dispatch(heal);
}

/**
 * 
 * @param {number} damage -
 */
Character.prototype._damaged = function(damage) {

}

Character.prototype.die = function() {
    this.animations.stop();
    this.onDeath.dispatch();
}

Character.prototype.idle = function() {
    this.animations.stop();
    this.onRest.dispatch();
}

Object.defineProperty(Character.prototype, 'frameRate',{
    get: function() {
        return this.stats.frameRate;
    }
});

Object.defineProperty(Character.prototype, 'name',{
    get: function() {
        return this._name;
    },
    set: function(value) {
        this.onNameChange.dispatch();
        this._name = value;
    }
});

module.exports = Character;