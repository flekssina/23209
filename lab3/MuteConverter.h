#ifndef MUTE_CONVERTER_H
#define MUTE_CONVERTER_H

#include "Converter.h"
#include <memory>
#include <vector>
#include <string>

class MuteConverter : public Converter {
public:
    MuteConverter(double start, double end);
    void apply(WavFile& wav) override;

    // Фабрика для создания объекта
    static std::shared_ptr<Converter> create(const std::vector<std::string>& params);

private:
    double start;
    double end;
};

#endif // MUTE_CONVERTER_H
