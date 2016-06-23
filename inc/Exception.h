#pragma once
#include "stdafx.h"

class Exception
{
protected:
	std::string description;
	std::string fileName;
	unsigned int line;

public:
	Exception(std::string file, unsigned int lineNumber, std::string desc) :
		description(description),
		fileName(file),
		line(lineNumber)
	{

	}

public:
	inline std::string getString()
	{
		std::stringstream stringBuilder;
		stringBuilder << "'" << description << "; [" << fileName << "@" << line << "]";
		return stringBuilder.str();
	}
};
