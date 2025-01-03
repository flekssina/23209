#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <vector>
#include <memory>
#include "Converter.h"

class ConfigParser {
public:
    ConfigParser(const std::string& configPath);
    std::vector<std::shared_ptr<Converter>> parse(const std::vector<std::string>& inputFiles);

private:
    std::string filePath;
};

#endif // CONFIG_PARSER_H