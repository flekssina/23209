#include "MixerConverter.h"
#include "WavFile.h"
#include <stdexcept>
#include <algorithm>

MixerConverter::MixerConverter(const std::string& inputFile, double insertTime)
    : inputFile(inputFile), insertTime(insertTime) {}

void MixerConverter::apply(WavFile& wav) {
    WavFile mixStream(inputFile);
    auto& primarySamples = wav.getSamples();
    auto& mixSamples = mixStream.getSamples();
    int sampleRate = 44100; 

    size_t insertIndex = static_cast<size_t>(insertTime * sampleRate);
    insertIndex = std::min(insertIndex, primarySamples.size());

    for (size_t i = 0; i < mixSamples.size() && (i + insertIndex) < primarySamples.size(); ++i) {
        primarySamples[i + insertIndex] = (primarySamples[i + insertIndex] + mixSamples[i]) / 2;
    }
}

std::shared_ptr<Converter> MixerConverter::create(const std::vector<std::string>& params, const std::vector<std::string>& inputFiles) {
    if (params.size() < 2) {
        throw std::invalid_argument("MixerConverter requires 2 parameters: input and insert time.");
    }

    std::string input = params[0];
    double insertTime = std::stod(params[1]);

   
    if (!input.empty() && input[0] == '$') {
        int index = std::stoi(input.substr(1)) - 1; // Преобразуем $n в индекс
        if (index < 0 || index >= inputFiles.size()) {
            throw std::invalid_argument("Invalid file index: " + input);
        }
        input = inputFiles[index];
    }

    return std::make_shared<MixerConverter>(input, insertTime);
}
