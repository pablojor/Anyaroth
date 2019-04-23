'use strict'

var TimerAlterations = {
    newStart(timer) {
        this.coolDown[timer].addOnceStart(this, timer);
        this.coolDown[timer].start();
    }
}

module.exports = TimerAlterations;