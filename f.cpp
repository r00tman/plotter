#include "f.h"

#include <cmath>

bool f(long double x, long double y) {
    bool line1 = x-y>=0;
    bool rect1 = x >= 3 && x <= 5.5 && y >= -4 && y <= 2;
    bool circle1 = (x+3.5)*(x+3.5)+(y-2.5)*(y-2.5)<=1.5*1.5;
    bool parabola1 = y*y-1 + 2 * x < 0;
    bool parabola2 = 1.5*(x+1.5)*(x+1.5)+y-2<=0;
    bool parabola2_vertex_right = x >= -1.5;
    bool line2 = 4*(x+1)-y <= 0;
    bool diamond1 = fabsl(y+2)/1.5+fabsl(x)/3.5 <= 1;

    //return circle1;
    bool area1 = diamond1 && parabola1 && !parabola2 && !line2;
    bool area2 = parabola1 && line2 && !circle1 && !diamond1 && !parabola2 && !parabola2_vertex_right;
    bool area3 = !diamond1 && parabola2 && line2 && line1;
    bool area4 = !diamond1 && !rect1 && line1 && !parabola1 && parabola2_vertex_right && !parabola2;
    return area1 || area2 || area3 || area4;
}
