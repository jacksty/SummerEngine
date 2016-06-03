#pragma once
#include "stdafx.h"

#include "Singleton.h"
#include "HString.h"

class HashManager final : public Singleton<HashManager>
{
	// ATTRIBUTES
private:
	std::vector<HString> hStrings;

	// CONSTRUCTORS / DESTRUCTORS
public:
	HashManager();
	~HashManager();

	// METHODS
public:


};