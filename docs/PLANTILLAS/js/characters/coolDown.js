'use strict'

var TimerAlterations = require('./timerAlterations');
/**
 * 
 */
var CoolDown = {
    /**
     * 
     * @param {number} time 
     */
    addAllTime(event) {
        this.coolDown[event].nextTick = this[event].coolDownTime() + this.coolDown[event]._now;
        this.coolDown[event].start();
        this.coolDown[event].onStart.dispatch();
        for (let timer in this.coolDown) {
            if(timer!==event){
                if (this.coolDown[timer].running) {
                    this.coolDown[timer].nextTick += this.coolDown[event].global();
                } else {
                    this.coolDown[timer].start();
                    this.coolDown[timer].onStart.dispatch();
                    this.coolDown[timer].nextTick = this.coolDown[event].global() + this.coolDown[event]._now;
                    CoolDown.signalEmiter.call(this, timer);
                }
            }
            
        }
    },
    signalEmiter(event) {
        if (this.coolDown[event].nextTick > this.coolDown[event]._now) {
            this.coolDown[event].onWhile.dispatch();
            this.coolDownTimer.add(this.frameRate, CoolDown.signalEmiter, this, event);
            this.coolDownTimer.start();
        } else {
            this.coolDown[event].stop();
            this.coolDown[event].onWhile.dispatch();
            this.coolDown[event].onEnd.dispatch();
        }
    },
    /**
     * 
     */
    stopAll() {

    },

    toRealCoolDown(animationTime, coolDown) {
        return Math.max(animationTime, coolDown);
    }
}

module.exports = CoolDown;