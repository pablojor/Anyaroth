#include "Knife.h"
#include "Game.h"

Knife::Knife(Game * game) : Melee(game, { 15, 0 }, ENEMIES, 8, 22, 12, Knife_Weapon)
{
}

Knife::~Knife() {}