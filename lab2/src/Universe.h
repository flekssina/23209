#pragma once

#include "Cell.h"
#include <set>

class Universe
{
private:
    std::string universe_name;
    int width = 0;
    int height = 0;
    std::set<int> survival_rls;
    std::set<int> birth_rls;
    std::set<Cell> live_cells;
    [[nodiscard]] int CntLivingNeighbours(int x, int y) const;

public:
    Universe() = default;
    void AdvanceToNextGeneration();
    [[nodiscard]] bool CellExists(const int &x, const int &y) const;
    void PrintUniverse() const;
    [[nodiscard]] std::string GetUniverseName() const;
    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    [[nodiscard]] std::set<int> GetSurvivalRules() const;
    [[nodiscard]] std::set<int> GetBirthRules() const;
    void SetUniverseName(const std::string &name);
    void SetWidth(const int &g_width);
    void SetHeight(const int &g_height);
    void AddSurvivalRule(const int &i);
    void AddBirthRule(const int &i);
    void AddCell(const int &x, const int &y);
};


