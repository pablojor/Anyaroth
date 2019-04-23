'use strict'
/**
 * 
 */
var Action = {
    /**
     * 
     */
    idle() {
        this.onRest.dispatch();
        this.play('idle', this.stats.frameRate, true);
    },
    /**
     * 
     * @param {Character} target 
     */
    attack(target) {
        this._preAttacking(target);
    },
    /**
     * 
     * @param {Character} target 
     */
    preAttacking(target) {
        this.animations.play('preAttacking', this.stats.frameRate, false);
        this.animations._anims.preAttacking.onComplete.add(this._attacking, this, 0, target);
    },
    /**
     * 
     * @param {Character} target 
     */
    attacking(target) {
        this.animations.play('attacking', this.stats.frameRate, false);
        if (arguments[2] !== null) {
            arguments[2].hit(this.stats.realDamage,this);
        };
        this.animations._anims.attacking.onComplete.add(this.idle, this);

    },
    /**
     * 
     */
    block() {
        this._preBlocking();
    },
    /**
     * 
     */
    preBlocking() {
        this.animations.play('preBlocking', this.stats.frameRate, false);
        this.animations._anims.preBlocking.onComplete.add(this._blocking, this);
    },
    /**
     * 
     */
    blocking() {
        this.isBlocking = true;
        this.animations.play('blocking', this.stats.frameRate, true);
        this.animations._anims.blocking.onLoop.add(this._blockingLoop, this);
    },
    /**
     * 
     */
    blockingLoop() {
        if (this.animations._anims.blocking.loopCount >= (this.stats.blockingTime / this.animations._anims.blocking._frames.length * this.stats.frameRate / Phaser.Timer.SECOND)){
            this._postBlocking();
        }
    },
    /**
     * 
     */
    postBlocking() {
        this.isBlocking = false;
        this.animations.play('postBlocking', this.stats.frameRate, false);
        this.animations._anims.postBlocking.onComplete.add(this.idle, this);
    },
    /**
     * 
     */
    block() {
        this._preBlocking();
    },
    /**
     * 
     */
    preBlocking() {
        this.animations.play('preBlocking', this.stats.frameRate, false);
        this.animations._anims.preBlocking.onComplete.add(this._blocking, this);
    },
    /**
     * 
     */
    blocking() {
        this.isBlocking = true;
        this.animations.play('blocking', this.stats.frameRate, true);
        this.animations._anims.blocking.onLoop.add(this._blockingLoop, this);
    },
    /**
     * 
     */
    blockingLoop() {
        if (this.animations._anims.blocking.loopCount >= (this.stats.blockingTime / this.animations._anims.blocking._frames.length * this.stats.frameRate / Phaser.Timer.SECOND)){
            this._postBlocking();
        }
    },
    /**
     * 
     */
    postBlocking() {
        this.isBlocking = false;
        this.animations.play('postBlocking', this.stats.frameRate, false);
        this.animations._anims.postBlocking.onComplete.add(this.idle, this);
    },/**
    * 
    */
   thornsBlock() {
       this._preThornsBlocking();
   },
   /**
    * 
    */
   preThornsBlocking() {
       this.animations.play('preThornsBlocking', this.stats.frameRate, false);
       this.animations._anims.preThornsBlocking.onComplete.add(this._thornsBlocking, this);
   },
   /**
    * 
    */
   thornsBlocking() {
       this.isBlocking = true;
       this.animations.play('thornsBlocking', this.stats.frameRate, true);
       this.animations._anims.thornsBlocking.onLoop.add(this._thornsBlockingLoop, this);
   },
   /**
    * 
    */
   thornsBlockingLoop() {
       if (this.animations._anims.thornsBlocking.loopCount >= (this.stats.blockingTime / this.animations._anims.thornsBlocking._frames.length * this.stats.frameRate / Phaser.Timer.SECOND)){
           this._postThornsBlocking();
       }
   },
   /**
    * 
    */
   postThornsBlocking() {
       this.isBlocking = false;
       this.animations.play('postThornsBlocking', this.stats.frameRate, false);
       this.animations._anims.postThornsBlocking.onComplete.add(this.idle, this);
   },
    /**
     * 
     */
    die() {
        this.animations.play('dying', 10, false);
        this.onDeath.dispatch();
    },

    /**
     * 
     */
    use(object, target) {
        let item;
        if(typeof object === 'string') {
            item = this.items.findIndex(function(element){
                return element.name === object;
            });
            object = item;
        }

        if( object >= 0 && object < 2) {
            item = this.items[object];
            item.use.call(this, this, target);
            this.items.splice(object,1);
        }
    }
}

module.exports = Action;