#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
	static const std::string currentDateTime();
    static void init(const std::string& logFilePath);
    static void logInfo(const std::string& message);
    static void logError(const std::string& message);
    static void close();

private:
    static std::ofstream logFile;
};

#endif // LOGGER_H
