'use strict'

var ActionPattern = function (pattern, seeker, character) {
    this._currentAction = 'unknown';
    this._pattern = pattern;
    this._seeker = seeker;
    this._character = character;
    this._currentIndex = 0;
    this._totalActions = 0;
    this._pattern.forEach(element => {
        if (typeof element.repetitions === 'undefined') {
            element.repetitions = 1;
        }
        this._totalActions += element.repetitions;
    }, this);
    this._character.patternTimer = this._character.game.time.create(false); 
}

ActionPattern.prototype.actionNumber = function (number) {
    number = (this._currentIndex + number) % this._totalActions;
    let i = number;
    let j = 0;
    while (i >= this._pattern[j].repetitions) {
        i -= this._pattern[j].repetitions;
        j++;
    }
    if (typeof this._pattern[j].action === 'string') {
        return this._pattern[j].action;
    } else if (typeof this._pattern[j].action === 'function') {
        return this._pattern[j].action(this._character, this._seeker);
    }
}

Object.defineProperty(ActionPattern.prototype, 'currentAction', {
    get: function () {
        return this._currentAction = this.actionNumber(0);
    }
});

Object.defineProperty(ActionPattern.prototype, 'nextAction', {
    get: function () {
        this._currentIndex = (this._currentIndex + 1) % this._totalActions;
        return this.currentAction;
    }
});

module.exports = ActionPattern;