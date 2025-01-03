#include <iostream>
#include <string>
#include <vector>
#include "SoundProcessor.h"
#include "ConfigParser.h"
#include "Exceptions.h"

void printUsage() {
    std::cout << "Usage: sound_processor -c <config.txt> <output.wav> <input1.wav> [<input2.wav> ...]\n";
    std::cout << "Supported converters:\n";
    std::cout << "  mute <start> <end> - Silence the audio in the given interval.\n";
    std::cout << "  mix $<input_index> <insert_time> - Mix input file into the primary stream.\n";
    std::cout << "  custom - Apply a reverse effect to the audio.\n";
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 5 || std::string(argv[1]) != "-c") {
            printUsage();
            return 1;
        }

        std::string configFilePath = argv[2];
        std::string outputFilePath = argv[3];
        std::vector<std::string> inputFiles;
        for (int i = 4; i < argc; ++i) {
            inputFiles.push_back(argv[i]);
        }

        ConfigParser configParser(configFilePath);

        auto converters = configParser.parse(inputFiles);

        SoundProcessor processor(inputFiles, converters);
        processor.process(outputFilePath);

        std::cout << "Processing completed successfully.\n";
        return 0;

    } catch (const UnsupportedFormatException& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    } catch (const ConfigurationException& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 3;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 4;
    }
}
