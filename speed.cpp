#include <unordered_map>
#include <string>
#include <stdexcept>
#include "speed.h"

static const std::unordered_map<std::string, ITESpeed> speedStringMap = {
    {"0", ITESpeed::VERY_SLOW},
    {"1", ITESpeed::SLOW},
    {"2", ITESpeed::MEDIUM},
    {"3", ITESpeed::FAST},
    {"4", ITESpeed::VERY_FAST},
};

const static std::unordered_map<ITESpeed, uint8_t> speedMap = {
    {ITESpeed::VERY_SLOW, 0x0a},
    {ITESpeed::SLOW,      0x07},
    {ITESpeed::MEDIUM,    0x05},
    {ITESpeed::FAST,      0x03},
    {ITESpeed::VERY_FAST, 0x01}
};

Speed::Speed(std::string s)
{
    auto result = speedStringMap.find(s);

    if (result == speedStringMap.end())
        throw std::invalid_argument("unable to parse speed specifier" + s);

    speed = result->second;
}

uint8_t Speed::getDeviceSpeed() const
{
    return speedMap.at(speed);
}

void Speed::printUsage(std::ostream &stream)
{
    stream << "A SPEED specifies how quickly a style plays.\n";
    stream << "There are five different speeds specified with a number\n";
    stream << "in the range [0,4]. Each number maps to a speed with:\n";
    stream << "\n";
    stream << "  \"0\": very slow\n";
    stream << "  \"1\": slow\n";
    stream << "  \"2\": medium\n";
    stream << "  \"3\": fast\n";
    stream << "  \"4\": very fast\n";
}
