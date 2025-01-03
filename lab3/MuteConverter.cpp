#include "MuteConverter.h"
#include <stdexcept>
#include <algorithm>

MuteConverter::MuteConverter(double start, double end) : start(start), end(end) {}

void MuteConverter::apply(WavFile& wav) {
    auto& samples = wav.getSamples();
    int sampleRate = 44100; // Assuming 44100 Hz
    size_t startIndex = static_cast<size_t>(start * sampleRate);
    size_t endIndex = static_cast<size_t>(end * sampleRate);

    startIndex = std::min(startIndex, samples.size());
    endIndex = std::min(endIndex, samples.size());

    for (size_t i = startIndex; i < endIndex; ++i) {
        samples[i] = 0;
    }
}

std::shared_ptr<Converter> MuteConverter::create(const std::vector<std::string>& params) {
    if (params.size() < 2) {
        throw std::invalid_argument("MuteConverter requires 2 parameters: start and end.");
    }
    double start = std::stod(params[0]);
    double end = std::stod(params[1]);
    return std::make_shared<MuteConverter>(start, end);
}
