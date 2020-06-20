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

void Colour::printUsage(std::ostream &stream)
{
    stream << "A COLOUR specifier is defined as three numeric values in the range\n";
    stream << "[0, 255]. Each colour value is seperated by a ',' character and the\n";
    stream << "values represent how much of the red, green and blue's respecitve\n";
    stream << "colour channels are active.\n";
    stream << "\n";
    stream << "For example, for pure red use the string \"255,0,0\".  For cyan use\n";
    stream << "the string \"0,255,255\". There are also the following predefined\n";
    stream << "colours avilable:\n";
    stream << "\n";
    stream << "  - red\n";
    stream << "  - green\n";
    stream << "  - blue\n";
    stream << "  - yellow\n";
    stream << "  - cyan\n";
    stream << "\n";
    stream << "to specify one, use the colour name as the COLOUR specifier.\n";
}
