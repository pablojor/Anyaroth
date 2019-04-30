'use strict'
var Days = require('../../assets/days/days');

var DayManager = function(seeker, game){
    this._seeker = seeker;
    this._game = game;
}

DayManager.prototype.newDay = function(){
    
    var days = Days['day' + this._seeker.day];
    this.goEvent(days[days.DayGenerator(this._seeker, this)](this._seeker,this));
    

}

DayManager.prototype.goCombat = function(day) {

}

DayManager.prototype.goEvent = function(day) {
    this._game.state.start('event',true, false, this._seeker, this,...Object.values(day));
}

DayManager.prototype.generateDay = function(seeker, day) {

}

module.exports = DayManager;
