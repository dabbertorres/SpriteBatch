#include "Common.hpp"
#include <SFML/System/Vector2.hpp>
#include <array>
#include <ctime>
#include <cmath>


std::array<sf::Vector2f, 6> swift::getTrianglesFromVector(sf::Vector2f vec) {
    std::array<sf::Vector2f, 6> returnValue = std::array<sf::Vector2f, 6>();
    int timeTmp = time(nullptr);
    
    /// Triangle 1
    returnValue[0] = {0, 0}; /// Top Left
    returnValue[1] = {vec.x, 0}; /// Top Right
    returnValue[2] = {0, vec.y}; /// Bottom Left
    /// Triangle 2
    returnValue[3] = {vec.x, 0}; /// Top Right
    returnValue[4] = vec;        /// Bottom Right
    returnValue[5] = {0, vec.y}; /// Bottom Left
    return returnValue;
}
