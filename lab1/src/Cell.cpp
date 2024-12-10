#include "Cell.h"

Cell::Cell(int x, int y) : x(x), y(y) {}

bool Cell::operator<(const Cell &rhs) const
{
    return x < rhs.x || (x == rhs.x && y < rhs.y);
}
