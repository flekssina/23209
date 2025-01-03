#ifndef CUSTOM_CONVERTER_H
#define CUSTOM_CONVERTER_H

#include "Converter.h"
#include <memory>
#include <vector>
#include <string>

class CustomConverter : public Converter {
public:
    CustomConverter();
    void apply(WavFile& wav) override;

    // Фабрика для создания объекта
    static std::shared_ptr<Converter> create(const std::vector<std::string>& params);
};

#endif // CUSTOM_CONVERTER_H
