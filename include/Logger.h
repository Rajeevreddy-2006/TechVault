#ifndef LOGGER_H
#define LOGGER_H

#include <string>

/*
 * Logger interface
 * Used to record program events (save, load, errors, etc.)
 * Demonstrates runtime polymorphism.
 */
class Logger {
public:
    virtual void logMessage(const std::string& msg) = 0;
    virtual ~Logger() {}
};

// Logs messages to the console
class ConsoleLogger : public Logger {
public:
    void logMessage(const std::string& msg) override;
};

// Logs messages to a file
class FileLogger : public Logger {
private:
    std::string filename;

public:
    FileLogger(std::string file);
    void logMessage(const std::string& msg) override;
};

#endif
