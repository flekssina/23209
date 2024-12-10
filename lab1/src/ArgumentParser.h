#pragma once

#include <iostream>
#include "Universe.h"

class ArgumentParser
{
private:
    std::string mode;
    std::string input_file_path;
    std::string output_file_path;
    int iterations_cnt = 0;
public:
    ArgumentParser() = default;

    [[nodiscard]] std::string GetGameMode() const;

    [[nodiscard]] std::string GetInputFilePath() const;

    [[nodiscard]] std::string GetOutputFilePath() const;

    [[nodiscard]] int GetCntOfIterations() const;

    void ArgumentOptions(int argc, char **argv);
};


