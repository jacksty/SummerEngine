#include "stdafx.h"

#include "LogManager.h"

int main()
{
	new LogManager("EngineLog.txt");

	delete LOG_MANAGER;

	return 0;
}