'use strict'

var TimeCalculations = {
    totalAttackTime: function() {
        return (this.animations._anims.preAttacking._frames.length + this.animations._anims.attacking._frames.length) / this.stats.frameRate;
    },
    currentAttackTime: function() {
        switch (this.animations.currentAnim.name) {
            case 'preAttacking':
                return (this.animations._anims.preAttacking.currentFrame.index - this.animations._anims.preAttacking._frames[0]) / this.stats.frameRate;
            case 'attacking':
                return (this.animations._anims.attacking.currentFrame.index - this.animations._anims.attacking._frames[0] + this.animations._anims.preAttacking._frames.length) / this.stats.frameRate;
            default:
                return NaN;
        }
    },
    totalBlockTime: function() {
        return ((this.animations._anims.preBlocking._frames.length + this.animations._anims.postBlocking._frames.length)
            / this.stats.frameRate) + this.stats.blockingTime/Phaser.Timer.SECOND;
    },
    currentBlockTime: function() {
        switch (this.animations.currentAnim.name) {
            case 'preBlocking':
                return (this.animations._anims.preBlocking.currentFrame.index - this.animations._anims.preBlocking._frames[0]) / this.stats.frameRate;
            case 'blocking':
                return (this.animations._anims.preBlocking.currentFrame.index - this.animations._anims.blocking._frames[0] + this.animations._anims.blocking.loopCount * this.animations._anims.blocking._frames.length
                    + this.animations._anims.preBlocking._frames.length) / this.stats.frameRate;
            case 'postBlocking':
                return (this.animations._anims.preBlocking.currentFrame.index - this.animations._anims.postBlocking._frames[0] +
                    this.animations._anims.preBlocking._frames.length) / this.stats.frameRate
                    + this.stats.blockingTime/Phaser.Timer.SECOND;
            default:
                return NaN;
        }
    },
    totalThornsBlockTime: function() {
        return ((this.animations._anims.preThornsBlocking._frames.length + this.animations._anims.postThornsBlocking._frames.length)
            / this.stats.frameRate) + this.stats.blockingTime/Phaser.Timer.SECOND;
    },
    currentThornsBlockTime: function() {
        switch (this.animations.currentAnim.name) {
            case 'preThornsBlocking':
                return (this.animations._anims.preThornsBlocking.currentFrame.index - this.animations._anims.preThornsBlocking._frames[0]) / this.stats.frameRate;
            case 'thornsBlocking':
                return (this.animations._anims.preThornsBlocking.currentFrame.index - this.animations._anims.thornsBlocking._frames[0] + this.animations._anims.thornsBlocking.loopCount * this.animations._anims.thornsBlocking._frames.length
                    + this.animations._anims.preThornsBlocking._frames.length) / this.stats.frameRate;
            case 'postThornsBlocking':
                return (this.animations._anims.preThornsBlocking.currentFrame.index - this.animations._anims.postThornsBlocking._frames[0] +
                    this.animations._anims.preThornsBlocking._frames.length) / this.stats.frameRate
                    + this.stats.blockingTime/Phaser.Timer.SECOND;
            default:
                return NaN;
        }
    },
    totalIdleTime: function(){
        return (this.animations._anims.idle._frames.length)/this.stats.frameRate;
    },
    currentIdleTime: function(){
        if(this.animations.currentAnim.name == 'idle'){
            return (this.animations._anims.idle.currentFrame.index - this.animations._anims.idle._frames[0]) / this.stats.frameRate
        } else
            return NaN;
    }
}

module.exports = TimeCalculations;