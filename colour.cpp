#include <string>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include <unordered_map>
#include <vector>

#include "colour.h"

Colour::Colour(std::string s)
{
    if (s == "red") {
        *this = ITEDefaultColours::red;
        return;
    }

    if (s == "green") {
        *this = ITEDefaultColours::green;
        return;
    }

    if (s == "blue") {
        *this = ITEDefaultColours::blue;
        return;
    }

    if (s == "yellow") {
        *this = ITEDefaultColours::yellow;
        return;
    }

    if (s == "cyan") {
        *this = ITEDefaultColours::cyan;
        return;
    }

    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, s, boost::is_any_of(","));

    if (tokens.size() != 3)
        throw std::invalid_argument("Unable to parse colour: expected three tokens");

    std::unordered_map<std::string, uint8_t &> token_map = {
       {tokens[0], red},
       {tokens[1], green},
       {tokens[2], blue}
    };
  
    for (const auto &i : token_map) {
        auto val = std::stoi(i.first);

        if (val > 255 || val < 0)
            throw std::invalid_argument("Unable to parse colour: colour value " + i.first + " is not in range [0,255]");

        i.second = val;
    }
}
