#ifndef WAV_FILE_H
#define WAV_FILE_H

#include <string>
#include <vector>

class WavFile {
public:
    explicit WavFile(const std::string& filePath);
    void save(const std::string& filePath);
    std::vector<int16_t>& getSamples();
    const std::vector<int16_t>& getSamples() const;

private:
    std::string filePath;
    std::vector<int16_t> samples;
    int sampleRate;

    void load();
};

#endif // WAV_FILE_H
