/*
put this code snipets where needed for better information

logInfo("Server started.");
logWarning("Client disconnected unexpectedly.");
logError("Unable to open file: data.txt");
*/

// logHandler.cpp

#include <iostream>
#include <fstream>
#include <ctime>
#include <mutex>

// Define logging levels
enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

// Mutex for thread-safe logging
std::mutex logMutex;

// Log error message to file
void logMessage(LogLevel level, const std::string& message) {
    // Define log file name based on log level
    std::string logFileName;
    switch (level) {
        case LogLevel::INFO:
            logFileName = "info.log";
            break;
        case LogLevel::WARNING:
            logFileName = "warning.log";
            break;
        case LogLevel::ERROR:
            logFileName = "error.log";
            break;
    }

    // Acquire lock for thread-safe logging
    std::lock_guard<std::mutex> lock(logMutex);

    // Open log file
    std::ofstream logfile(logFileName, std::ios::app);
    if (!logfile.is_open()) {
        std::cerr << "Error: Unable to open log file." << std::endl;
        return;
    }

    // Get current timestamp
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    // Write log message to file
    logfile << "[" << timestamp << "] ";
    switch (level) {
        case LogLevel::INFO:
            logfile << "[INFO] ";
            break;
        case LogLevel::WARNING:
            logfile << "[WARNING] ";
            break;
        case LogLevel::ERROR:
            logfile << "[ERROR] ";
            break;
    }
    logfile << message << std::endl;

    // Close log file
    logfile.close();
}

// Log informational message
void logInfo(const std::string& message) {
    logMessage(LogLevel::INFO, message);
}

// Log warning message
void logWarning(const std::string& message) {
    logMessage(LogLevel::WARNING, message);
}

// Log error message
void logError(const std::string& message) {
    logMessage(LogLevel::ERROR, message);
}
