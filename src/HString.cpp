#include "stdafx.h"
#include "HString.h"


// CONSTRUCTORS / DESTRUCTORS

HString::HString(const char* cstr) : 
	string(cstr),
	fingerprint(hashFunction(cstr))
{}

// METHODS

void HString::reinitialize(const char* cstr)
{
	string = cstr;
	fingerprint = hashFunction(cstr);
}

bool HString::operator== (const HString& rhs) const
{
	return fingerprint == rhs.getFingerprint();
}


bool HString::operator== (const std::string& rhs) const
{
	return string.compare(rhs) == 0;
}


bool HString::operator== (const char* rhs) const
{
	return string.compare(rhs) == 0;
}


int HString::compare(const HString& other) const
{
	uint64 tmp = other.getFingerprint();
	return fingerprint == tmp ? 0 : (fingerprint > tmp ? 1 : -1);
}


int HString::compare(const std::string& other) const
{
	return string.compare(other);
}


int HString::compare(const char* other) const
{
	return string.compare(other);
}


uint64 HString::hashFunction(const char* cstr)
{
	// processes string 4 characters at a time in order to build a (probably) unique fingerprint value
	uint64 hash = 0;
	uint32 idx = 0;
	uint32 len = -1;

	while (cstr[++len] != 0); // increment len until cstr[len] is the null terminator
	
	const uint32 wLength = len / 4;
	const uint64 MOD_VAL = 4294967291; // largest 32-bit prime
	const uint32* intString = reinterpret_cast<const uint32*>(cstr);

	while (idx < wLength)
	{
		hash <<= 32; // shift previous result to clear room for next 4 bytes
		hash |= intString[idx++]; // move the next for chars from cstr into the now-cleared section of hash and increment idx
		hash %= MOD_VAL; // mod hash with MOD_VAL to create fingerprint
	}

	hash <<= 32;
	hash |= intString[idx] >> ((4 - len % 4) * 8); // remove excess bits from after the end of the string
	hash %= MOD_VAL;

	return hash;
}

// GETTERS / SETTERS

char HString::operator[](uint32 idx) const
{
	return string[idx];
}


size_t HString::length() const
{
	return string.length();
}


uint64 HString::getFingerprint() const
{
	return fingerprint;
}


const std::string& HString::getString() const
{
	return string;
}
