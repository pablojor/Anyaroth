'use strict'

var ReactiveBar = require('./reactiveBar');
var ReactiveCircleBar = require('./reactiveCircleBar');

var ActionBar = function(game, parent, x, y, enemy, frameKey){
    Phaser.Group.call(this, game, parent);
    this._enemy = enemy;
    this.x = x;
    this.y = y;
    this._nextX = 31;
    this._back = this.add(new Phaser.Image(game,0,0,'actionsBarBack'));
    this._actionContiner = this.add(new Phaser.Group(game, this));
    this._actionContiner.mask = this.add(new Phaser.Graphics(game,31,13));
    this._actionContiner.mask.beginFill(0xffffff);
    this._actionContiner.mask.drawRect(0, 0, 80, 13);
    this._actionContiner.mask.endFill();
    this._timer = game.time.create(false);
    this._onEveryHalfDeciSecond = new Phaser.Signal();
    this._timer.loop(0.1,this._onEveryHalfDeciSecond.dispatch,this._onEveryHalfDeciSecond);
    
    //ActionBar.prototype._createAction.call(this,'attack');
    //ActionBar.prototype._createAction.call(this,'block');
    this._actionCircle = this.add(new ReactiveCircleBar(this.game,this,13,13,12,[0,Math.PI*3/2, Math.PI],[0x0000FF, 0x00FF00, 0xFF0000],[1,1,1],true, 400, -Math.PI/2, function(){
        if(this._actionContiner.children[0]){
        let name = this._actionContiner.children[0].action;
        let percentage = this._enemy[name].currentTime()/this._enemy[name].totalTime()*100;
        return isNaN(percentage)?0:percentage;
        } return 0;
    }, this,this._onEveryHalfDeciSecond));
    //this._onEveryHalfDeciSecond.add(ActionBar.prototype.move,this,0,-1);
    
    this._frame = this.add(new Phaser.Image(game,0,0,'actionsBarFrame'));
    this._barShadow = this.add(new Phaser.Image(game,32,13,'actionsBarShadow'));
    this._barShadow.alpha = 0.3;
    this._actions = [];
    this._childIndex = 0;
    this._rightX = 31;
    this._active = true;
}

ActionBar.prototype = Object.create(Phaser.Group.prototype);
ActionBar.prototype.constructor = ActionBar;

ActionBar.prototype.update = function() {
    if(this._active){
    let time = this._enemy[this._enemy.actionPattern.currentAction].currentTime();
    if(!isNaN(time)){
        this._actions = [];
        this._actionContiner.removeAll(true);
        this._rightX =31-time/8*80;
        this._createAction(this._enemy.actionPattern.currentAction);
        let i = 1;
        while(this._rightX < 111){
            this._createAction(this._enemy.actionPattern.actionNumber(i));
            i++;
        }
    }
}
}

ActionBar.prototype._createAction = function(action) {
    //'blockBar''attackBar''unknownBar' 'idleBar'
    this._actions.push(this._actionContiner.add(new ReactiveBar(this.game, this,this._rightX,13,action+'Bar', function(){
        return this[action].totalTime()/(8)*100;
    },this._enemy, this._enemy.stats.onSpeedChange, 0)));
    this._actions[this._actions.length-1].action = action;
    this._rightX+=this._actions[this._actions.length-1].mask.width;
    
}
ActionBar.prototype.reUpdate = function () {
    this._actionContiner.children.forEach(function(element){
        element.changePercentage();
    });
    this._actionContiner.mask.beginFill(0xffffff);
    this._actionContiner.mask.drawRect(0, 0, 80, 13);
    this._actionContiner.mask.endFill();
}

ActionBar.prototype.move = function(movement) {
    
    this._actions.forEach(function(element){
        element.x+=movement;
        if(element.right<31){
            this._actionContiner.remove(this._actions.shift(),true);
            this._actions.shift();
        }
    },this);
    let right = false;
    if(this._actions.length<=0 || this._actions[this._actions.length-1].x+this._actions[this._actions.length-1].mask.right<111){
        //console.log(this._actions.length);
        this._createAction(this._enemy.actionPattern.actionNumber(this._actions.length-1));
    } 
    
}

ActionBar.prototype.activate = function() {
    this._active = true;
    this.reUpdate();
    this._timer.start();
}

ActionBar.prototype.deactivate = function() {
    this._active = false;
    this._actionContiner.removeAll(true);
    this._timer.stop();
}

module.exports = ActionBar;