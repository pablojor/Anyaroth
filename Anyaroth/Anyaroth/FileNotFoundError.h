#pragma once
#include "AnyarothError.h"

class FileNotFoundError : public AnyarothError
{
public:
	FileNotFoundError(string fileName) : AnyarothError("'File Not Found Error' occurred. " + fileName + " was not found. ") {}
};