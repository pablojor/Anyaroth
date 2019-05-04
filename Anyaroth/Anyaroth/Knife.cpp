#include "Knife.h"
#include "Game.h"

Knife::Knife(Game * game) : Melee(game, { 15, 0 }, ENEMIES, 5, 20, 10, Knife_Weapon)
{
}

Knife::~Knife()
{
}
