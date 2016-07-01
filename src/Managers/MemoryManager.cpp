#include "stdafx.h"
#include "MemoryManager.h"

namespace SE
{
	// Setup singleton pointer
	template<>
	MemoryManager* Singleton<MemoryManager>::SingletonPtr = nullptr;


	void MemoryManager::Startup()
	{
		Singleton<MemoryManager>::Initialize();
	}


	void MemoryManager::Shutdown()
	{
		Singleton<MemoryManager>::Deinitialize();
	}
}
