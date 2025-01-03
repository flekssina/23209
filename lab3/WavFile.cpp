#include "WavFile.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>

WavFile::WavFile(const std::string& filePath) : filePath(filePath), sampleRate(44100) {
    load();
}

void WavFile::save(const std::string& outputFilePath) {
    std::ofstream file(outputFilePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open output file: " + outputFilePath);
    }

    
    uint32_t dataChunkSize = samples.size() * sizeof(int16_t);
    uint32_t fileSize = 36 + dataChunkSize;

    file.write("RIFF", 4);
    file.write(reinterpret_cast<const char*>(&fileSize), 4);
    file.write("WAVEfmt ", 8);

    uint32_t fmtChunkSize = 16;
    uint16_t audioFormat = 1; // PCM
    uint16_t numChannels = 1; // Mono
    uint32_t byteRate = sampleRate * numChannels * sizeof(int16_t);
    uint16_t blockAlign = numChannels * sizeof(int16_t);
    uint16_t bitsPerSample = 16;

    file.write(reinterpret_cast<const char*>(&fmtChunkSize), 4);
    file.write(reinterpret_cast<const char*>(&audioFormat), 2);
    file.write(reinterpret_cast<const char*>(&numChannels), 2);
    file.write(reinterpret_cast<const char*>(&sampleRate), 4);
    file.write(reinterpret_cast<const char*>(&byteRate), 4);
    file.write(reinterpret_cast<const char*>(&blockAlign), 2);
    file.write(reinterpret_cast<const char*>(&bitsPerSample), 2);

    // Write data chunk header
    file.write("data", 4);
    file.write(reinterpret_cast<const char*>(&dataChunkSize), 4);

    // Write samples
    file.write(reinterpret_cast<const char*>(samples.data()), dataChunkSize);
}

std::vector<int16_t>& WavFile::getSamples() {
    return samples;
}

const std::vector<int16_t>& WavFile::getSamples() const {
    return samples;
}

void WavFile::load() {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open input file: " + filePath);
    }

    char header[44];
    file.read(header, 44);
    if (std::strncmp(header, "RIFF", 4) != 0 || std::strncmp(header + 8, "WAVE", 4) != 0) {
        throw std::runtime_error("Invalid WAV file format: " + filePath);
    }

    uint16_t audioFormat = *reinterpret_cast<uint16_t*>(header + 20);
    uint16_t numChannels = *reinterpret_cast<uint16_t*>(header + 22);
    uint32_t sampleRateFromFile = *reinterpret_cast<uint32_t*>(header + 24);
    uint16_t bitsPerSample = *reinterpret_cast<uint16_t*>(header + 34);

    if (audioFormat != 1 || numChannels != 1 || sampleRateFromFile != 44100 || bitsPerSample != 16) {
        throw std::runtime_error("Unsupported WAV file format: " + filePath);
    }

    uint32_t dataChunkSize = *reinterpret_cast<uint32_t*>(header + 40);
    samples.resize(dataChunkSize / sizeof(int16_t));
    file.read(reinterpret_cast<char*>(samples.data()), dataChunkSize);
}
