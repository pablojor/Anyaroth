'use strict'

var Stats = function (damage, defense, speed, health, perception, tempDamage = undefined, tempDefense = undefined, tempSpeed = undefined, tempHealth = undefined, tempPerception = undefined) {
    this._damage = damage;
    this._tempDamage = tempDamage === undefined ? damage : tempDamage;
    this.onDamageChange = new Phaser.Signal();
    this._defense = defense;
    this._tempDefense = tempDefense === undefined ? defense : tempDefense;
    this.onDefenseChange = new Phaser.Signal();
    this._speed = speed;
    this._tempSpeed = tempSpeed === undefined ? speed : tempSpeed;
    this.onSpeedChange = new Phaser.Signal();
    this._health = health;
    this._tempHealth = tempHealth === undefined ? health : tempHealth;
    this.onHealthChange = new Phaser.Signal();
    this._perception = perception;
    this._tempPerception = tempPerception === undefined ? perception : tempPerception;
    this.onPerceptionChange = new Phaser.Signal();
}

Stats.prototype.damagedNotBlocked = function (damage) {
    return Math.max(0, damage - this.realBlock);
}

Object.defineProperty(Stats.prototype, 'frameRate', {
    get: function () {
        return 10 + this.tempSpeed / ((this.tempSpeed + 100)) * 50;
    }
});

Object.defineProperty(Stats.prototype, 'realBlock', {
    get: function () {
        return this.tempDefense * 2;
    }
});

Object.defineProperty(Stats.prototype, 'realDamage', {
    get: function () {
        return this.tempDamage * 2;
    }
});

Object.defineProperty(Stats.prototype, 'blockingTime', {
    get: function () {
        return Phaser.Timer.SECOND / 2 + Phaser.Timer.SECOND * this.tempHealth / ((this.tempHealth + 9)) * 2;
    }
});

Object.defineProperty(Stats.prototype, 'maxHp', {
    get: function () {
        return this._tempHealth * 5;
    }
});

Object.defineProperty(Stats.prototype, 'tempDamage', {
    get: function () {
        return this._tempDamage;
    },
    set: function (value) {
        this._tempDamage = value;
        this.onDamageChange.dispatch();
    }
});

Object.defineProperty(Stats.prototype, 'damage', {
    get: function () {
        return this._damage;
    },
    set: function (value) {
        this._damage = value;
        this.onDamageChange.dispatch();
    }
});

Stats.prototype.resetDamage = function () {
    this.damage = this.tempDamage;
};

Stats.prototype.updateDamage = function () {
    this.tempDamage = this.damage;
};

Object.defineProperty(Stats.prototype, 'defense', {
    get: function () {
        return this._defense;
    },
    set: function (value) {
        this._defense = value;
        this.onDefenseChange.dispatch();
    }
});

Object.defineProperty(Stats.prototype, 'tempDefense', {
    get: function () {
        return this._tempDefense;
    },
    set: function (value) {
        this._tempDefense = value;
        this.onDefenseChange.dispatch();
    }
});

Stats.prototype.resetDefense = function () {
    this.defense = this.tempDefense;
};

Stats.prototype.updateDefense = function () {
    this.tempDefense = this.defense;
};

Object.defineProperty(Stats.prototype, 'speed', {
    get: function () {
        return this._speed;
    },
    set: function (value) {
        this._speed = value;
        this.onSpeedChange.dispatch();
    }
});

Object.defineProperty(Stats.prototype, 'tempSpeed', {
    get: function () {
        return this._tempSpeed;
    },
    set: function (value) {
        this._tempSpeed = value;
        this.onSpeedChange.dispatch();
    }
});

Stats.prototype.resetSpeed = function () {
    this.speed = this.tempSpeed;
};

Stats.prototype.updateSpeed = function () {
    this.tempSpeed = this.speed;
};

Object.defineProperty(Stats.prototype, 'health', {
    get: function () {
        return this._health
    },
    set: function (value) {
        this._health = value;
        this.onHealthChange.dispatch();
    }
});

Object.defineProperty(Stats.prototype, 'tempHealth', {
    get: function () {
        return this._tempHealth
    },
    set: function (value) {
        this._tempHealth = value;
        this.onHealthChange.dispatch();
    }
});

Stats.prototype.resetHealth = function () {
    this.health = this.tempHealth;
};

Stats.prototype.updateHealth = function () {
    this.tempHealth = this.health;
};


Object.defineProperty(Stats.prototype, 'perception', {
    get: function () {
        return this._perception
    },
    set: function (value) {
        this._perception = value;
        this.onPerceptionChange.dispatch();
    }
});

Object.defineProperty(Stats.prototype, 'tempPerception', {
    get: function () {
        return this._tempPerception
    },
    set: function (value) {
        this._tempPerception = value;
        this.onPerceptionChange.dispatch();
    }
});

Object.defineProperty(Stats.prototype, 'coolDownFactor', {
    get: function () {
        return (99-this.tempSpeed)/98;
    }
});

Stats.prototype.resetPerception = function () {
    this.perception = this.tempPerception;
};

Stats.prototype.updatePerception = function () {
    this.tempPerception = this.perception;
};

Stats.prototype.reset = function () {
    this.resetDamage();
    this.resetDefense();
    this.resetHealth();
    this.resetSpeed();
    this.resetPerception();
};

Stats.prototype.update = function () {
    this.updateDamage();
    this.updateDefense();
    this.updateHealth();
    this.updateSpeed();
    this.updatePerception();
};

module.exports = Stats;