#pragma once
#include "stdafx.h"
#include "Singleton.h"
#include "HString.h"

namespace SE
{
#define LOG_MANAGER LogManager::GetSingletonPtr()
#define LOG_EXCEPTION(ex) LOG_MANAGER->log(ex.getString(), LL_ERROR);

#define LOGFILE_GENERAL_DEFAULT "..\\EngineLog.txt"


	class LogManager final : public Singleton<LogManager>
	{
		// CONSTANTS
	public:
		static const u16 LL_NONE = 0x0;
		static const u16 LL_NORMAL = 0x1;
		static const u16 LL_DEBUG = 0x2;
		static const u16 LL_WARNING = 0x4;
		static const u16 LL_ERROR = 0x8;
		static const u16 LL_ALL = 0xF;

		// ATTRIBUTES
	private:
		/// File that messages will be printed to.
		std::ofstream outputFile;
		/// Filters which messages will be printed based message flags.
		u16 logMask;

		// INITIALIZATION
	public:
		/// Custom initialization behavior for this manager singleton.
		static void Startup(const std::string& outputFileName = LOGFILE_GENERAL_DEFAULT);
		/// Custom deinitialization behavior for this manager singleton.
		static void Shutdown();

		// METHODS
	public:
		/// Prints message to log file if not caught by filter.
		void log(const std::string& message, const u16 flags = LL_NORMAL);
		/// Set the filter to a different set of flags. Messages are printed if appropriate flag is 1.
		void setLogFilter(const u16 allowed = LL_ALL);

		/// Treats this message as highest-priority and logs it to the existing log file if one exists, otherwise it creates a new log file called AssertFailure.txt and logs the message there.
		static void LogAssertionFailure(const std::string& message, const char* filename, int line);
	};
}
