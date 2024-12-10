#include "Universe.h"
#include "ArgumentParser.h"
#include "LifeGame.h"
#include <iostream>

int main(int argc, char **argv)
{
    try
    {
        Universe universe;
        ArgumentParser argument_parser;

        argument_parser.ArgumentOptions(argc, argv);
        std::string mode = argument_parser.GetGameMode();

        if (mode == "offline")
        {
            GameStart::StartOfflineGame(argument_parser, universe);
        }
        else if (mode == "default")
        {
            GameStart::StartDefaultGame(universe);
        }
        else if (mode == "input file")
        {
            GameStart::StartGameFromFile(argument_parser, universe);
        }
        else
        {
            std::cerr << "Invalid game mode specified. Supported modes: offline, default, input file." << std::endl;
        }
    }
    catch (const std::ios_base::failure &e)
    {
        std::cerr << "File error: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Out of range error: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    return 0;
}
