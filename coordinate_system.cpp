#include "coordinate_system.h"

coordinate_system::coordinate_system()
{
}

void coordinate_system::forward(long double x, long double y, long double &xa, long double &ya)
{
    xa = (x + xpitch) * xscale + xoffset;
    ya = (y + ypitch) * yscale + yoffset;
}

void coordinate_system::backward(long double x, long double y, long double &xa, long double &ya)
{
    xa = ((x - xoffset) / xscale) - xpitch;
    ya = ((y - yoffset) / yscale) - ypitch;
}
