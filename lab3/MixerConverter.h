#ifndef MIXER_CONVERTER_H
#define MIXER_CONVERTER_H

#include "Converter.h"
#include <memory>
#include <vector>
#include <string>

class MixerConverter : public Converter {
public:
    MixerConverter(const std::string& inputFile, double insertTime);
    void apply(WavFile& wav) override;

    // Фабрика для создания объекта
    static std::shared_ptr<Converter> create(const std::vector<std::string>& params, const std::vector<std::string>& inputFiles);

private:
    std::string inputFile;
    double insertTime;
};

#endif // MIXER_CONVERTER_H