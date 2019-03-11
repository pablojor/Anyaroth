#pragma once
#include "AnyarothError.h"

class SDLError : public AnyarothError
{
public:
	SDLError() : AnyarothError("'SDL Error' occurred. ") {}

	const string SDL_GetError() const throw()
	{
		return " Problem with SDL initializers. ";
	}

	const string IMGG_GetError() const throw()
	{
		return " Problem with the textured images. ";
	}

	const string TTF_GetError() const throw()
	{
		return " Problem with TTF library. ";
	}
};