#ifndef __COLOUR_H_
#define __COLOUR_H_

#include <stdint.h>
#include <string.h>

struct Colour
{
    constexpr Colour(uint8_t red, uint8_t green, uint8_t blue)
        : red(red), green(green), blue(blue) {}

    Colour(std::string s);

    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

namespace ITEDefaultColours
{
    constexpr Colour red(0xff, 0x00, 0x00);
    constexpr Colour green(0x00, 0xff, 0x00);
    constexpr Colour blue(0x00, 0x00, 0xff);
    constexpr Colour yellow(0xff, 0xff, 0x00);
    constexpr Colour cyan(0x00, 0xff, 0xff);
}

#endif // __COLOUR_H_
