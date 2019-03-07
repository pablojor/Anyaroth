#pragma once
#include "AnyarothError.h"

class FileFormatError : public AnyarothError
{
public:
	FileFormatError(string error) : AnyarothError("'File Format Error' occurred. Problem with " + error) {}
};