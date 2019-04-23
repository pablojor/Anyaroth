'use strict'

var DayFunctions = {
    NextDay: function(seeker, dayManager) {
        seeker.day++;
        dayManager.newDay();
    },
    Combat: function(seeker, dayManager, enemy, background, music, end) {
        dayManager._game.state.start('combat',true, false, seeker, dayManager, enemy, background, music, end);
    },
    Event: function(seeker, dayManager, evento){
        dayManager._game.state.start('event', true, false, seeker, dayManager,...Object.values(evento(seeker, dayManager)));
    }
}

module.exports = DayFunctions;