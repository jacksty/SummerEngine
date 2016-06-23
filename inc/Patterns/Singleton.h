#pragma once
#include "stdafx.h"
#include "Exception.h"

template<class T>
class Singleton
{
	// ATTRIBUTES
protected:
	/// Pointer to the one-and-only instance of the T singleton.
	static T* singletonPtr;
	std::mutex singletonMutex;

	// CONSTRUCTORS / DESTRUCTORS
public:
	Singleton() {} // do nothing
	virtual ~Singleton() {}; // do nothing

	// INITIALIZATION
protected:
	/// Constructs a statically-allocated instance of the templated singleton when called the first time. Afterwards simply sets the singletonPtr to that instance.
	inline static void initialize()
	{
		ASSERT(singletonPtr == nullptr)
		static T singletonInstance;
		singletonPtr = &singletonInstance;
	}
	/// Clears the singletonPtr for the templated singleton.
	inline static void deinitialize()
	{
		ASSERT(singletonPtr != nullptr)
		singletonPtr = nullptr;
	}

	// METHODS
public:
	/// Return a pointer to the templated singleton.
	inline static T* getSingletonPtr()
	{
		ASSERT(singletonPtr != nullptr)
		return singletonPtr;
	}
};