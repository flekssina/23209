#ifndef SOUND_PROCESSOR_H
#define SOUND_PROCESSOR_H

#include <string>
#include <vector>
#include <memory>
#include "Converter.h"

class SoundProcessor {
public:
    SoundProcessor(const std::vector<std::string>& inputFiles, const std::vector<std::shared_ptr<Converter>>& converters);
    void process(const std::string& outputFilePath);

private:
    std::vector<std::string> inputFiles;
    std::vector<std::shared_ptr<Converter>> converters;
};

#endif // SOUND_PROCESSOR_H