'use strict'

var ParticleFactory = function (character) {
    this.character = character;
}

ParticleFactory.prototype.blood = function (x = this.character.width / 2, y = this.character.width / 2, radius = 5, emittedBlood = 'redBlood') {

    this.character.bleed = this.character.game.add.emitter(this.character.x + x, this.character.y + y, 1000);
    this.character.bleed.makeParticles(emittedBlood);
    this.character.bleed.radius = radius;
    this.character.bleed.x = this.character.bleed.emitX;
    this.character.bleed.y = this.character.bleed.emitY;
    this.character.bleed.gravity = 200;
    this.character.bleed.minParticleScale = 1;
    this.character.bleed.maxParticleScale = 2;
    this.character.bleed.bounce = 0;

    

    //this.character.game.worldbleed.particleBringToTop = true;
    //this.character.game.world.bringToTop(this.character.bleed);


    //let b = this.character.game.world.bringToTop(this.character.bleed);
    //console.log(b);
    this.character._damaged = function (damage) {
        this.bleed.parent.bringToTop(this.bleed);
        let angle = this.game.rnd.angle();
        let radius = this.game.rnd.frac() * this.bleed.radius;
        this.bleed.emitX = radius * Math.sin(Math.PI / 180 * angle) + this.bleed.x;
        this.bleed.emitY = radius * Math.cos(Math.PI / 180 * angle) + this.bleed.y;
        this.bleed.flow(2000, 1, 20, damage * 10, true);

    };

}

module.exports = ParticleFactory;