#include "stdafx.h"
#include "LogManager.h"

// Setup singleton pointer
template<>
LogManager* Singleton<LogManager>::SingletonPtr = nullptr;


void LogManager::Startup(const std::string& outputFileName)
{
	Singleton<LogManager>::Initialize(true); // locks LogManager mutex and initializes singleton, should always be the first statement in this function
	{
		SingletonPtr->logMask = LL_ALL;
		SingletonPtr->outputFile = std::ofstream(outputFileName);
	}
	SingletonPtr->singletonMutex.unlock();

	SingletonPtr->log("LogManager initialized.", LL_NORMAL);
}


void LogManager::Shutdown()
{
	ASSERT(SingletonPtr != nullptr)
	SingletonPtr->log("LogManager shutting down. Goodbye.", LL_NORMAL);

	SingletonPtr->singletonMutex.lock();
	if (SingletonPtr->outputFile.is_open())
		SingletonPtr->outputFile.close();
	
	Singleton<LogManager>::Deinitialize(true); // unlocks LogManager mutex and destroys singleton, should always be the last statement in this function
}


void LogManager::log(const std::string& message, const uint16 flags)
{
	singletonMutex.lock(); // lock the LogManager mutex so that only one thread can log a message at a time
	{
		if (outputFile.is_open() && (flags & logMask)) // check if message passes filter
		{
			// get current time
			time_t currentTime = time(NULL);
			struct tm timeStruct;
			localtime_s(&timeStruct, &currentTime);

			// write date and time
			outputFile << "[" << timeStruct.tm_mon + 1 << "/" << timeStruct.tm_mday << "/" << timeStruct.tm_year + 1900;
			outputFile << "@" << timeStruct.tm_hour << ":" << timeStruct.tm_min << ":" << timeStruct.tm_sec << "]";

			// write message priority indicators
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
	bool locked = SingletonPtr == nullptr && SingletonPtr->singletonMutex.try_lock(); // lock mutex if manager exists and mutex is available

	if (locked)
		outwriter = &SingletonPtr->outputFile; // use existing output file if available RIGHT NOW
	else
		outwriter = new std::ofstream("..\\AssertFailure.txt"); // otherwise, create a new file to log the message to

	// get the current time
	time_t currentTime = time(NULL);
	struct tm timeStruct;
	localtime_s(&timeStruct, &currentTime);

	// write message
	*outwriter << "[" << timeStruct.tm_mon + 1 << "/" << timeStruct.tm_mday << "/" << timeStruct.tm_year + 1900;
	*outwriter << "@" << timeStruct.tm_hour << ":" << timeStruct.tm_min << ":" << timeStruct.tm_sec << "]";
	*outwriter << "[ASSERT FAILURE] FILE: " << file << ", LINE: " << line << ", Condition violated: " << msg << std::endl;

	if (!locked) // if a new log file was created, close the stream and deallocate
	{
		outwriter->close();
		delete outwriter;
	}
	else // if we locked the LogManager mutex, unlock it
		SingletonPtr->singletonMutex.unlock();
}
