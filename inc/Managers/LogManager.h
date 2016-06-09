#pragma once
#include "stdafx.h"
#include "Singleton.h"

class LogManager final : public Singleton<LogManager>
{
	// CONSTANTS
public:
	static const uint16 LL_NONE = 0x0;
	static const uint16 LL_NORMAL = 0x1;
	static const uint16 LL_DEBUG = 0x2;
	static const uint16 LL_WARNING = 0x4;
	static const uint16 LL_ERROR = 0x8;
	static const uint16 LL_ALL = 0xF;

	// ATTRIBUTES
private:
	/// File that messages will be printed to.
	std::ofstream outputFile;

	/// Filters which messages will be printed based message flags.
	uint8 logMask;

	// CONSTRUCTORS / DESTRUCTORS
public:
	LogManager(std::string logFileName);
	~LogManager();

	// METHODS
public:
	/// Prints message to log file if not caught by filter.
	void log(std::string message, const uint16 flags = LL_NORMAL);

	/// Set the filter to a different set of flags. Messages are printed if appropriate flag is 1.
	void setLogFilter(const uint16 allowed = LL_ALL);
};
