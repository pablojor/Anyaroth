#include "UIElement.h"
#include "Game.h"

//Hecho para evitar inclusion circular
UIElement::UIElement(Game* game) : _game(game) {}