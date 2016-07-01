#pragma once
#include "stdafx.h"
#include "Singleton.h"

namespace SE
{
	class MemoryManager final : public Singleton<MemoryManager>
	{
		// INITIALIZATION
	public:
		/// Custom initialization behavior for this manager singleton.
		static void Startup();
		/// Custom deinitialization behavior for this manager singleton.
		static void Shutdown();
	};
}
