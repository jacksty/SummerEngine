#include "stdafx.h"

#include "LogManager.h"
#include "StackAllocator.h"

int main()
{
	SE::LogManager::Startup();
	

	
	SE::LogManager::Shutdown();
	return 0;
}