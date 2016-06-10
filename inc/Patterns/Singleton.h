#pragma once
#include "stdafx.h"
#include "Exception.h"

template<class T>
class Singleton
{
protected:
	static T* singletonPtr;
	std::mutex singletonMutex;

public:
	Singleton()
	{
		if (singletonPtr != nullptr)
			throw Exception(__FILE__, __LINE__, "Singleton already exists!");
		singletonPtr = static_cast<T*>(this);
	}

	virtual ~Singleton()
	{
		singletonPtr = nullptr;
	}

public:
	static T* getSingletonPtr()
	{
		if (singletonPtr == nullptr)
			throw Exception(__FILE__, __LINE__, "Singleton does not exist!");
		return singletonPtr;
	}
};