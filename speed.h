#ifndef __SPEED_H_
#define __SPEED_H_

#include <unordered_map>
#include <iostream>

enum class ITESpeed
{
    VERY_SLOW,
    SLOW,
    MEDIUM,
    FAST,
    VERY_FAST
};

class Speed
{
public:
    Speed(ITESpeed speed)
        : speed(speed) {};

    Speed(std::string s);

    uint8_t getDeviceSpeed() const;
    static void printUsage(std::ostream &stream);
private:
    ITESpeed speed;
};

#endif // __SPEED_H_
