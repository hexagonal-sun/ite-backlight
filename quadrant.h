#ifndef __QUADRANT_H_
#define __QUADRANT_H_

enum class ITEQuadrant
{
    FAR_LEFT = 1,
    LEFT = 2,
    RIGHT = 3,
    FAR_RIGHT = 4,
};

constexpr std::array<ITEQuadrant, 4> allQuadrants = {ITEQuadrant::FAR_LEFT,
                                                     ITEQuadrant::LEFT,
                                                     ITEQuadrant::RIGHT,
                                                     ITEQuadrant::FAR_RIGHT};

#endif // __QUADRANT_H_
