#ifndef __COLOUR_H_
#define __COLOUR_H_

#include <stdint.h>

struct Colour
{
    Colour(uint8_t red, uint8_t green, uint8_t blue)
        : red(red), green(green), blue(blue) {}

    const uint8_t red;
    const uint8_t green;
    const uint8_t blue;
};

#endif // __COLOUR_H_
