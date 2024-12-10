#include "Universe.h"
#include <iostream>

int Universe::CntLivingNeighbours(int x, int y) const
{
    int count = 0;
    int g_width = this->width;
    int g_height = this->height;

    for (int offset_x = -1; offset_x <= 1; ++offset_x)
    {
        for (int offset_y = -1; offset_y <= 1; ++offset_y)
        {
            if (offset_x == 0 && offset_y == 0)
            {
                continue;
            }

            int neighbour_x = (x + offset_x + g_width) % g_width;
            int neighbour_y = (y + offset_y + g_height) % g_height;

            if (CellExists(neighbour_x, neighbour_y))
            {
                ++count;
            }
        }
    }
    return count;
}

bool Universe::CellExists(const int &x, const int &y) const
{
    Cell cell(x, y);
    return this->live_cells.count(cell) > 0;
}

void Universe::AdvanceToNextGeneration()
{
    std::set<Cell> nxt_generation;

    for (int x = 0; x < this->width; ++x)
    {
        for (int y = 0; y < this->height; ++y)
        {
            int living_neighbours = CntLivingNeighbours(x, y);

            if (CellExists(x, y))
            {
                if (this->survival_rls.count(living_neighbours) > 0)
                {
                    nxt_generation.insert(Cell(x, y));
                }
            }

            else if (this->birth_rls.count(living_neighbours) > 0)
            {
                nxt_generation.insert(Cell(x, y));
            }
        }
    }

    this->live_cells = std::move(nxt_generation);
}

void Universe::PrintUniverse() const
{
    std::cout << universe_name << std::endl;

    std::cout << "Board size: " << width << " x " << height << std::endl;

    std::cout << "Birth / Survival: ";
    for (const auto& rule : birth_rls)
    {
        std::cout << rule;
    }
    std::cout << "/";
    for (const auto& rule : survival_rls)
    {
        std::cout << rule;
    }
    std::cout << std::endl;

    for (int i = 0; i < width + 2; ++i)
    {
        std::cout << "/ ";
    }
    std::cout << std::endl;
    for (int x = 0; x < height; ++x)
    {
        std::cout << "| ";
        for (int y = 0; y < width; ++y) {
            std::cout << (CellExists(x, y) ? "* " : "  ");
        }
        std::cout << "|" << std::endl;
    }

    for (int i = 0; i < width + 2; ++i)
    {
        std::cout << "/ ";
    }
    std::cout << std::endl;
}

std::string Universe::GetUniverseName() const
{
    return universe_name;
}

int Universe::GetWidth() const
{
    return width;
}

int Universe::GetHeight() const
{
    return height;
}

std::set<int> Universe::GetSurvivalRules() const
{
    return survival_rls;
}

std::set<int> Universe::GetBirthRules() const
{
    return birth_rls;
}

void Universe::SetUniverseName(const std::string &name)
{
    this->universe_name = name;
}

void Universe::SetWidth(const int &g_width)
{
    if (g_width <= 0)
    {
        throw std::invalid_argument("Board width must be positive.");
    }
    this->width = g_width ;
}

void Universe::SetHeight(const int &g_height)
{
    if (g_height <= 0) {
        throw std::invalid_argument("Board height must be positive.");
    }
    this->height = g_height;
}

void Universe::AddSurvivalRule(const int &i)
{
    if (i < 0 || i > 8)
    {
        throw std::invalid_argument("Survival rule must be between 0 and 8.");
    }
    survival_rls.insert(i);
}

void Universe::AddBirthRule(const int &i)
{
    if (i < 0 || i > 8)
    {
        throw std::invalid_argument("Birth rule must be between 0 and 8.");
    }
    birth_rls.insert(i);
}

void Universe::AddCell(const int &x, const int &y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        throw std::out_of_range("Cell coordinates must be within the board size.");
    }
    Cell cell(x, y);
    live_cells.insert(cell);
}
