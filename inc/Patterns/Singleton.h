#pragma once
#include "stdafx.h"

namespace SE
{
	template<class T>
	class Singleton
	{
		// ATTRIBUTES
	protected:
		/// Pointer to the one-and-only instance of the T singleton.
		static T* SingletonPtr;

		/// Mutex belonging to and controlling access to the one-and-only T singleton.
		std::mutex singletonMutex;


		// INITIALIZATION
	protected:
		/// Constructs a statically-allocated instance of the templated singleton when called the first time. Afterwards simply sets the singletonPtr to that instance.
		inline static void Initialize(bool shouldLockMutex = false)
		{
			static_assert(std::is_base_of<Singleton<T>, T>::value, "Invalid singleton type. Singleton<T> must be the base of T."); // enforces CRTP
			
			static T SingletonInstance;

			if (shouldLockMutex)
				SingletonInstance.singletonMutex.lock();

			SingletonPtr = &SingletonInstance;
		}
		/// Clears the singletonPtr for the templated singleton.
		inline static void Deinitialize(bool isMutexLockedByThisThread = false)
		{
			if (!isMutexLockedByThisThread)
				SingletonPtr->singletonMutex.lock();

			T* ptr = SingletonPtr;
			SingletonPtr = nullptr;

			ptr->singletonMutex.unlock();
		}

		// METHODS
	public:
		/// Return a pointer to the templated singleton.
		inline static T* GetSingletonPtr()
		{
			return SingletonPtr;
		}
	};
}
