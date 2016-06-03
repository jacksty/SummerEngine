#pragma once
#include "stdafx.h"

class HString final
{
	friend class HashManager;

	//ATTRIBUTES
private:
	const uint64 hash;
	const std::string string;

	// CONSTRUCTORS / DESTRUCTORS
protected:
	HString(const char* cstr, uint32 argc, uint64 sHash);
	~HString() {};

	// METHODS
public:
	static bool operator== (const HString& lhs, const HString& rhs);
	static bool operator== (const HString& lhs, const std::string& rhs);
	static bool operator== (const std::string& lhs, const HString& rhs);
	static bool operator== (const HString& lhs, const char* rhs);
	static bool operator== (const char* lhs, const HString& rhs);

	char operator[] (uint32 pos);

	int32 compare(const HString& other) const;
	int32 compare(const std::string& other) const;
	int32 compare(const char* other) const;

	uint32 length();

	// GETTERS / SETTERS
public:
	const uint64 getHash();
	const std::string* getString();
	const char* getCString();
};