#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

struct coordinate_system
{
public:
    long double xscale, yscale;
    long double xpitch, ypitch;
    long double xoffset, yoffset;

public:
    coordinate_system();

    void forward(long double x, long double y, long double &xa, long double &ya);
    void backward(long double x, long double y, long double &xa, long double &ya);
};

#endif // COORDINATE_SYSTEM_H
