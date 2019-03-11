#include "AmmoPackage.h"

string AmmoPackage::getType() const
{
	switch (_type) //Si eso continuar
	{
		case PistolaBasica:
			return "PistolaBasica";
			break;
		case EscopetaBasica:
			return "EscopetaBasica";
			break;
		case Rifle:
			return "Rifle";
			break;
		default:
			break;
	}
}