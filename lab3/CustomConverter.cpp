#include "CustomConverter.h"
#include <algorithm>

CustomConverter::CustomConverter() {}

void CustomConverter::apply(WavFile& wav) {
    auto& samples = wav.getSamples();
    std::reverse(samples.begin(), samples.end());
}

std::shared_ptr<Converter> CustomConverter::create(const std::vector<std::string>& params) {
    return std::make_shared<CustomConverter>();
}
