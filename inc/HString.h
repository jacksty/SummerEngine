#pragma once
#include "stdafx.h"

class HString final
{
	friend class HashManager;

	//ATTRIBUTES
private:
	/// A (probably) unique value that can be used to identify the string. Chance of collisions should be very low.
	const uint64 fingerprint;

	/// The string that this HString holds a fingerprint for.
	const std::string string;

	// CONSTRUCTORS / DESTRUCTORS
protected:
	HString(const char* cstr);
	~HString() {} // nothing special needs to be done here

	// METHODS
public:
	bool operator== (const HString& rhs) const;
	bool operator== (const std::string& rhs) const;
	bool operator== (const char* rhs) const;

	int32 compare(const HString& other) const;
	int32 compare(const std::string& other) const;
	int32 compare(const char* other) const;

private:
	static uint64 hashFunction(const char* cstr);

	// GETTERS / SETTERS
public:
	char operator[] (uint32 pos) const;
	uint32 length() const;
	uint64 getFingerprint() const;
	const std::string* getString() const;
	const char* getCString() const;
};