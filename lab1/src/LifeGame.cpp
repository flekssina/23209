#include "LifeGame.h"
#include <sstream>
#include <fstream>
#include <stdexcept>

void FileHandler::LoadCellFromFile(Universe &universe, const std::string &line)
{
    std::istringstream stream(line);
    int x, y;
    if (stream >> x >> y)
    {
        universe.AddCell(x, y);
    }
    else
    {
        throw std::invalid_argument("Invalid cell format: " + line);
    }
}

void FileHandler::LoadSizeFromFile(Universe &universe, const std::string &line)
{
    size_t delimiter_pos = line.find('/');
    if (delimiter_pos != std::string::npos) {
        universe.SetWidth(std::stoi(line.substr(3, delimiter_pos - 3)));
        universe.SetHeight(std::stoi(line.substr(delimiter_pos + 1)));
    }
    else
    {
        throw std::invalid_argument("Invalid size format: " + line);
    }
}

void FileHandler::LoadRulesFromFile(Universe &universe, const std::string &line)
{
    size_t pos_b = line.find('B');
    size_t pos_s = line.find('S');

    if (pos_b != std::string::npos && pos_s != std::string::npos)
    {
        for (size_t i = pos_b + 1; i < pos_s; ++i)
        {
            if (isdigit(line[i]))
            {
                universe.AddBirthRule(line[i] - '0');
            }
        }

        for (size_t i = pos_s + 1; i < line.size(); ++i)
        {
            if (isdigit(line[i]))
            {
                universe.AddSurvivalRule(line[i] - '0');
            }
        }
    }
    else
    {
        throw std::invalid_argument("Invalid rule format: " + line);
    }
}

void FileHandler::LoadNameFromLine(Universe &universe, const std::string &line)
{
    if (line.size() > 3)
    {
        universe.SetUniverseName(line.substr(3));
    }
    else
    {
        throw std::invalid_argument("Invalid name format: " + line);
    }
}

void FileHandler::LoadUniverseFromFile(Universe &universe, const std::string &path)
{
    std::ifstream input_file(path);
    if (!input_file)
    {
        throw std::ios_base::failure("Failed to open file: " + path);
    }

    std::string line;
    while (std::getline(input_file, line))
    {
        if (line.rfind("#N ", 0) == 0)
        {
            LoadNameFromLine(universe, line);
        }
        else if (line.rfind("#S ", 0) == 0)
        {
            LoadSizeFromFile(universe, line);
        }
        else if (line.rfind("#R ", 0) == 0)
        {
            LoadRulesFromFile(universe, line);
        }
        else if (line.rfind("#Universe", 0) == 0)
        {
            continue;
        }
        else if (!line.empty() && line[0] != '#')
        {
            LoadCellFromFile(universe, line);
        }
    }

    input_file.close();
}

void FileHandler::SaveUniverseToFile(const Universe &universe, const std::string &path)
{
    std::ofstream output_file(path);
    if (!output_file)
    {
        throw std::ios_base::failure("Failed to open file: " + path);
    }

    output_file << "#Universe 1.06" << std::endl;
    output_file << "#N " << universe.GetUniverseName() << std::endl;

    output_file << "#R B";
    for (int birth : universe.GetBirthRules())
    {
        output_file << birth;
    }
    output_file << "/S";
    for (int survival : universe.GetSurvivalRules())
    {
        output_file << survival;
    }
    output_file << std::endl;

    output_file << "#S " << universe.GetWidth() << "/" << universe.GetHeight() << std::endl;

    for (int x = 0; x < universe.GetWidth(); ++x)
    {
        for (int y = 0; y < universe.GetHeight(); ++y)
        {
            if (universe.CellExists(x, y))
            {
                output_file << x << " " << y << std::endl;
            }
        }
    }

    output_file.close();
}

void GameCommandHandler::HandleGameCommands(Universe &universe)
{
    while (true)
    {
        std::string command;
        std::getline(std::cin, command);

        if (command == "exit")
        {
            break;
        }
        else if (command == "help")
        {
            std::cout << "dump <filename> - save universe to file;\n"
                         "tick <n> - calculate n (default 1) iterations and print result;\n"
                         "exit - finish game;\n"
                         "help - print help about commands.\n";
        }
        else if (command.rfind("dump ", 0) == 0)
        {
            std::string path = "../examples/" + command.substr(5);
            FileHandler::SaveUniverseToFile(universe, path);
        }
        else if (command.rfind("tick", 0) == 0)
        {
            int cnt_iterations = 1;

            if (command.size() > 4)
            {
                try
                {
                    cnt_iterations = std::stoi(command.substr(5));
                }
                catch (const std::invalid_argument &)
                {
                    std::cout << "Invalid tick command.\n";
                    continue;
                }
            }

            for (int i = 0; i < cnt_iterations; ++i)
            {
                universe.AdvanceToNextGeneration();
            }

            universe.PrintUniverse();
        }
        else
        {
            std::cout << "Unknown command. Use 'help' for a list of commands.\n";
        }
    }
}

void GameStart::StartOfflineGame(ArgumentParser &argumentParser, Universe &universe)
{
    std::string path = "../examples/" + argumentParser.GetInputFilePath();
    FileHandler::LoadUniverseFromFile(universe, path);

    for (int i = 0; i < argumentParser.GetCntOfIterations(); ++i)
    {
        universe.AdvanceToNextGeneration();
    }

    path = "../examples/" + argumentParser.GetOutputFilePath();
    FileHandler::SaveUniverseToFile(universe, path);
}

void GameStart::StartDefaultGame(Universe &universe)
{
    FileHandler::LoadUniverseFromFile(universe, "../examples/input.universe");
    universe.PrintUniverse();
    GameCommandHandler::HandleGameCommands(universe);
}

void GameStart::StartGameFromFile(ArgumentParser &argumentParser, Universe &universe)
{
    std::string path = "../examples/" + argumentParser.GetInputFilePath();
    FileHandler::LoadUniverseFromFile(universe, path);
    universe.PrintUniverse();
    GameCommandHandler::HandleGameCommands(universe);
}
