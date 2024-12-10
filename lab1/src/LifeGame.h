#pragma once

#include "Universe.h"
#include "ArgumentParser.h"
#include <iostream>
#include <string>

class FileHandler
{
public:
    static void LoadCellFromFile(Universe &universe, const std::string &line);
    static void LoadSizeFromFile(Universe &universe, const std::string &line);
    static void LoadRulesFromFile(Universe &universe, const std::string &line);
    static void LoadNameFromLine(Universe &universe, const std::string &line);
    static void LoadUniverseFromFile(Universe &universe, const std::string &path);
    static void SaveUniverseToFile(const Universe &universe, const std::string &path);
};

class GameCommandHandler
{
public:
    static void HandleGameCommands(Universe &universe);
};

class GameStart
{
public:
    static void StartOfflineGame(ArgumentParser &argumentParser, Universe &universe);
    static void StartDefaultGame(Universe &universe);
    static void StartGameFromFile(ArgumentParser &argumentParser, Universe &universe);
};
