#pragma once
#include "stdafx.h"

class HString final
{
	friend class HashManager;

	// ATTRIBUTES
private:
	/// A (probably) unique value that can be used to identify the string. Chance of collisions should be very low.
	uint64 fingerprint;
	/// The string that this HString holds a fingerprint for.
	std::string string;

	// CONSTRUCTORS / DESTRUCTORS
public:
	HString(const char* cstr);
	~HString() {} // nothing special needs to be done here

	// METHODS
public:
	/// Returns true if the fingerprints for these two strings are equal, otherwise returns false. Does not absolutely guarantee that the strings are actually equal.
	bool operator== (const HString& rhs) const;
	/// Returns true if these two strings are exactly equal, otherwise false.
	bool operator== (const std::string& rhs) const;
	/// Returns true if these two strings are exactly equal, otherwise false.
	bool operator== (const char* rhs) const;

	/// Returns 0 if this string matches the other string.
	int compare(const HString& other) const;
	/// Returns 0 if this string matches the other string.
	int compare(const std::string& other) const;
	/// Returns 0 if this string matches the other string.
	int compare(const char* other) const;
private:
	/// Creates a (probably) unique fingerprint for the given string.
	static uint64 hashFunction(const char* cstr);
protected:
	/// Reinitializes this object with the new parameter.
	void reinitialize(const char* cstr);

	// GETTERS / SETTERS
public:
	char operator[] (uint32 pos) const;
	size_t length() const;
	uint64 getFingerprint() const;
	const std::string& getString() const;

	// IMPLICIT CONVERSION
public:
	operator const std::string&() const { return string; };
};
