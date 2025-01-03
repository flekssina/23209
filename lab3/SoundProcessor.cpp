#include "SoundProcessor.h"
#include "WavFile.h"
#include <stdexcept>

SoundProcessor::SoundProcessor(const std::vector<std::string>& inputFiles, const std::vector<std::shared_ptr<Converter>>& converters)
    : inputFiles(inputFiles), converters(converters) {}

void SoundProcessor::process(const std::string& outputFilePath) {
    if (inputFiles.empty()) {
        throw std::runtime_error("No input files provided.");
    }

    WavFile primaryStream(inputFiles[0]);

    for (const auto& converter : converters) {
        converter->apply(primaryStream);
    }

    primaryStream.save(outputFilePath);
}
