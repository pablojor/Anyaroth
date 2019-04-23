'use strict'

var Action = require('./action.js');
var TimeCalculations = require('./timeCalculations.js');

/**
 * 
 * @param {Character} character 
 */
var ActionFactory = function (character) {
    this.character = character;
}

/**
 * 
 * @param {number[]|string[]} frames 
 */
ActionFactory.prototype.idle = function(frames) {
    this.character.animations.add('idle', frames, true);
    this.character.idle = Action.idle;
    this.character.idle.totalTime = TimeCalculations.totalIdleTime.bind(this.character);
    this.character.idle.currentTime = TimeCalculations.currentIdleTime.bind(this.character);
}

/**
 * 
 * @param {number[]|string[]} framesPreAttacking 
 * @param {number[]|string[]} framesAttacking 
 */
ActionFactory.prototype.attack = function(framesPreAttacking, framesAttacking) {
    this.character.attack = Action.attack;
    this.character.animations.add('preAttacking', framesPreAttacking, true);
    this.character.animations.add('attacking', framesAttacking, true);
    this.character._preAttacking = Action.preAttacking;
    this.character._attacking = Action.attacking;
    this.character.attack.totalTime = TimeCalculations.totalAttackTime.bind(this.character);
    this.character.attack.currentTime = TimeCalculations.currentAttackTime.bind(this.character);
}

/**
 * 
 * @param {number[]|string[]} framesPreBlocking 
 * @param {number[]|string[]} framesBlocking 
 * @param {number[]|string[]} framesPostBlocking 
 */
ActionFactory.prototype.block = function(framesPreBlocking, framesBlocking, framesPostBlocking) {
    this.character.animations.add('preBlocking', framesPreBlocking, true);
    this.character.animations.add('blocking', framesBlocking, true);
    this.character.animations.add('postBlocking', framesPostBlocking, true);
    this.character.block = Action.block;
    this.character._preBlocking = Action.preBlocking;
    this.character._blocking = Action.blocking;
    this.character._blockingLoop = Action.blockingLoop;
    this.character._postBlocking = Action.postBlocking;
    this.character.block.totalTime = TimeCalculations.totalBlockTime.bind(this.character);
    this.character.block.currentTime = TimeCalculations.currentBlockTime.bind(this.character);
}
/**
 * 
 * @param {number[]|string[]} framesPreThornsBlocking 
 * @param {number[]|string[]} framesThornsBlocking 
 * @param {number[]|string[]} framesPostThornsBlocking 
 */
ActionFactory.prototype.thornsBlock = function(framesPreThornsBlocking, framesThornsBlocking, framesPostThornsBlocking) {
    this.character.animations.add('preThornsBlocking', framesPreThornsBlocking, true);
    this.character.animations.add('thornsBlocking', framesThornsBlocking, true);
    this.character.animations.add('postThornsBlocking', framesPostThornsBlocking, true);
    this.character.onHit.add(function(attacker,damage){
        if(this.character.isBlocking)
            attacker.hurt(this.character.stats.realDamage);
    },this);
    this.character.thornsBlock = Action.thornsBlock;
    this.character._preThornsBlocking = Action.preThornsBlocking;
    this.character._thornsBlocking = Action.thornsBlocking;
    this.character._thornsBlockingLoop = Action.thornsBlockingLoop;
    this.character._postThornsBlocking = Action.postThornsBlocking;
    this.character.thornsBlock.totalTime = TimeCalculations.totalThornsBlockTime.bind(this.character);
    this.character.thornsBlock.currentTime = TimeCalculations.currentThornsBlockTime.bind(this.character);
}
ActionFactory.prototype.useObjects = function() {
    this.character.use = Action.use;
}

/**
 * 
 * @param {number[]|string[]} framesDying 
 */
ActionFactory.prototype.die = function(framesDying) {
    this.character.animations.add('dying', framesDying, true);
    this.character.die = Action.die;
    this.character.onDeathComplete = new Phaser.Signal();
    this.character.animations._anims.dying.onComplete.add(this.character.onDeathComplete.dispatch, this.character.onDeathComplete);
}

module.exports = ActionFactory;