#include "ConfigParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "MuteConverter.h"
#include "MixerConverter.h"
#include "CustomConverter.h"
#include "Exceptions.h"

ConfigParser::ConfigParser(const std::string& configPath)
    : filePath(configPath) {}

std::vector<std::shared_ptr<Converter>> ConfigParser::parse(const std::vector<std::string>& inputFiles) {
    std::ifstream configFile(filePath);
    if (!configFile.is_open()) {
        throw ConfigurationException("Could not open configuration file: " + filePath);
    }

    std::vector<std::shared_ptr<Converter>> converters;
    std::string line;

    while (std::getline(configFile, line)) {
        std::istringstream lineStream(line);
        std::string command;
        lineStream >> command;

        if (command.empty() || command[0] == '#') {
            continue; // Игнорируем пустые строки и комментарии
        }

        std::vector<std::string> params;
        std::string param;
        while (lineStream >> param) {
            params.push_back(param);
        }

        if (command == "mute") {
            converters.push_back(MuteConverter::create(params));
        } else if (command == "mix") {
            converters.push_back(MixerConverter::create(params, inputFiles));
        } else if (command == "custom") {
            converters.push_back(CustomConverter::create(params));
        } else {
            throw ConfigurationException("Unknown command in config: " + command);
        }
    }

    return converters;
}
