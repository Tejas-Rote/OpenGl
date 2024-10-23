#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

// Enum declaration for log levels
enum LogLevel {
	INFO, WARNING, ERROR
};

class Logger {
public:
	// Public method to log messages with specified log level
	static void Log(const std::string& msg, LogLevel level = INFO);

private:
	// Private methods for timestamp and file logging
	static std::string GetTimestamp();
	static void LogToFile(const std::string& msg);
};
