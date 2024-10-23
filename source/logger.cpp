#include "logger.h"

// Define method to log messages
void Logger::Log(const std::string& msg, LogLevel level) {
	std::string levelStr;
	switch (level) {
	case INFO:
		levelStr = "INFO";
		break;
	case WARNING:
		levelStr = "WARNING";
		break;
	case ERROR:
		levelStr = "ERROR";
		break;
	default:
		break;
	}

	// Output to console
	std::cout << GetTimestamp() << " [" << levelStr << "] " << msg << std::endl;
	// Log to file
	LogToFile("[" + levelStr + "] " + msg);
}

// Define method to get current timestamp as a string
std::string Logger::GetTimestamp() {
	time_t now = time(0);
	tm timeinfo;
	localtime_s(&timeinfo, &now);

	std::ostringstream oss;
	oss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

// Define method to log message to file
void Logger::LogToFile(const std::string& msg) {
	std::ofstream logfile("log.txt", std::ios_base::app);
	if (logfile.is_open()) {
		logfile << GetTimestamp() << " " << msg << std::endl;
		logfile.close();
	}
}
