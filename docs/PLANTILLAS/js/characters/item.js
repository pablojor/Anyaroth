'use strict'

var _use = function(use, that) {
    var that;
    var cuse = use;
    return function(character, enemy) {
        use.call(this, character, enemy);
        that.onUse.dispatch();
    }
}

var Item = function(name, description, key, use) {
    this.name = name;
    this.description = description;
    this.key = key;
    this.onUse = new Phaser.Signal();
    this.use = _use(use, this);
    
}

Item.prototype.destroy = function() {

}

module.exports = Item;