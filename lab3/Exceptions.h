#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class UnsupportedFormatException : public std::runtime_error {
public:
    explicit UnsupportedFormatException(const std::string& message)
        : std::runtime_error(message) {}
};

class ConfigurationException : public std::runtime_error {
public:
    explicit ConfigurationException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // EXCEPTIONS_H
