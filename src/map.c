#include "map.h"
#include "window.h"

bool is_point_inside_map(int x, int y)
{
    return (x >= 0 && x <= WIN_WIDTH) &&
           (y >= 0 && y <= WIN_HEIGHT);
}