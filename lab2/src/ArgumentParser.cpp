#include "ArgumentParser.h"

std::string ArgumentParser::GetGameMode() const
{
    return mode;
}

std::string ArgumentParser::GetInputFilePath() const
{
    return input_file_path;
}

std::string ArgumentParser::GetOutputFilePath() const
{
    return output_file_path;
}

int ArgumentParser::GetCntOfIterations() const
{
    return iterations_cnt;
}

void ArgumentParser::ArgumentOptions(int argc, char **argv)
{
    if (argc == 1)
    {
        this->mode = "default";
    }
    else if (argc == 2)
    {
        this->mode = "input file";
        this->input_file_path = argv[1];
    }
    else if (argc == 6) {
        this->mode = "offline";
        this->input_file_path = argv[1];
        for (int i = 2; i < argc; ++i)
        {
            if (strcmp(argv[i], "--iterations") == 0 || strcmp(argv[i], "-i") == 0)
            {
                this->iterations_cnt = std::stoi(argv[i + 1]);
                ++i;
            }
            else if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0)
            {
                this->output_file_path = argv[i + 1];
                ++i;
            }
            else
            {
                throw std::invalid_argument("Invalid arguments. Correct format: ./GameOfLife <input_file> -i <iterations> -o <output_file>");
            }
        }
    }
    else
    {
        throw std::invalid_argument("Invalid arguments. Correct format: ./GameOfLife <input_file> -i <iterations> -o <output_file>");
    }
}
