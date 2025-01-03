#ifndef CONVERTER_H
#define CONVERTER_H

#include "WavFile.h"

class Converter {
public:
    virtual ~Converter() = default;
    virtual void apply(WavFile& wav) = 0;
};

#endif // CONVERTER_H
