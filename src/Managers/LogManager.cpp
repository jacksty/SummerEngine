#include "stdafx.h"
#include "LogManager.h"

// Setup singleton pointer
template<>
LogManager* Singleton<LogManager>::singletonPtr = nullptr;

LogManager::LogManager(std::string fname) :
	logMask(LL_ALL),
	outputFile(fname)
{
}


LogManager::~LogManager()
{
	Singleton<LogManager>::singletonPtr = nullptr;
	if (outputFile.is_open())
		outputFile.close();
}


void LogManager::log(std::string message, const uint16 flags)
{
	singletonMutex.lock();
	{
		if (outputFile.is_open() && (flags & logMask))
		{
			time_t currentTime = time(NULL);
			struct tm timeStruct;
			localtime_s(&timeStruct, &currentTime);

			outputFile << "[" << timeStruct.tm_mon + 1 << "/" << timeStruct.tm_mday << "/" << timeStruct.tm_year + 1900;
			outputFile << "@" << timeStruct.tm_hour << ":" << timeStruct.tm_min << ":" << timeStruct.tm_sec << "] ";

			if (LL_ERROR & flags)
				outputFile << "[ERROR] ";
			else if (LL_WARNING & flags)
				outputFile << "[WARNING] ";
			else if (LL_DEBUG & flags)
				outputFile << "[DEBUG] ";

			outputFile << message << std::endl;
		}
	}
	singletonMutex.unlock();
}


void LogManager::setLogFilter(const uint16 allowed)
{
	singletonMutex.lock();
	{
		logMask = allowed & LL_ALL;
	}
	singletonMutex.unlock();
}
