#include "stdafx.h"
#include "LogManager.h"

// Setup singleton pointer
template<>
LogManager* Singleton<LogManager>::singletonPtr = nullptr;


void LogManager::Startup(const std::string& outputFileName)
{
	Singleton<LogManager>::initialize();

	singletonPtr->logMask = LL_ALL;
	singletonPtr->outputFile = std::ofstream(outputFileName);
	
	singletonPtr->log("LogManager initialized.", LL_NORMAL);
}


void LogManager::Shutdown()
{
	ASSERT(singletonPtr != nullptr)
	singletonPtr->log("LogManager shutting down. Goodbye.", LL_NORMAL);

	if (singletonPtr->outputFile.is_open())
		singletonPtr->outputFile.close();
	
	Singleton<LogManager>::deinitialize();
}


void LogManager::log(const std::string& message, const uint16 flags)
{
	singletonMutex.lock();
	{
		if (outputFile.is_open() && (flags & logMask))
		{
			time_t currentTime = time(NULL);
			struct tm timeStruct;
			localtime_s(&timeStruct, &currentTime);

			outputFile << "[" << timeStruct.tm_mon + 1 << "/" << timeStruct.tm_mday << "/" << timeStruct.tm_year + 1900;
			outputFile << "@" << timeStruct.tm_hour << ":" << timeStruct.tm_min << ":" << timeStruct.tm_sec << "]";

			if (LL_ERROR & flags)
				outputFile << "[ERROR] ";
			else if (LL_WARNING & flags)
				outputFile << "[WARNING] ";
			else if (LL_DEBUG & flags)
				outputFile << "[DEBUG] ";
			else
				outputFile << " ";

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


void LogManager::LogAssertionFailure(const std::string& msg, const char* file, int line)
{
	std::ofstream* outwriter;
	bool deallocOutwriter = singletonPtr == nullptr;

	if (singletonPtr == nullptr)
		outwriter = new std::ofstream("..\\AssertFailure.txt");
	else
		outwriter = &singletonPtr->outputFile; //writes to the existing output file, if one is available

	time_t currentTime = time(NULL);
	struct tm timeStruct;
	localtime_s(&timeStruct, &currentTime);

	*outwriter << "[" << timeStruct.tm_mon + 1 << "/" << timeStruct.tm_mday << "/" << timeStruct.tm_year + 1900;
	*outwriter << "@" << timeStruct.tm_hour << ":" << timeStruct.tm_min << ":" << timeStruct.tm_sec << "]";
	*outwriter << "[ASSERT FAILURE] FILE: " << file << ", LINE: " << line << ", Condition violated: " << msg << std::endl;

	if (deallocOutwriter)
	{
		outwriter->close();
		delete outwriter;
	}
}
