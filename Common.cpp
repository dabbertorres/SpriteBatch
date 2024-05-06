#include "Common.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <ctime>
#include <cmath>


std::array<sf::Vector2f, 6> swift::getTrianglesFromVector(sf::Vector2f vec) {
    std::array<sf::Vector2f, 6> returnValue = std::array<sf::Vector2f, 6>();
    int timeTmp = time(nullptr);
    
    /// Triangle 1
    returnValue[0] = {0, 0};     /// Top Left
    returnValue[1] = {vec.x, 0}; /// Top Right
    returnValue[2] = {0, vec.y}; /// Bottom Left
    /// Triangle 2
    returnValue[3] = {vec.x, 0}; /// Top Right
    returnValue[4] = vec;              /// Bottom Right
    returnValue[5] = {0, vec.y}; /// Bottom Left
    return returnValue;
}

std::array<sf::Vector2f, 6> swift::getTrianglesFromRect(sf::FloatRect vec) {
    std::array<sf::Vector2f, 6> returnValue = std::array<sf::Vector2f, 6>();
    int timeTmp = time(nullptr);

    /// Triangle 1
    returnValue[0] = {0,                  0}; /// Top Left
    returnValue[1] = {vec.width,          0}; /// Top Right
    returnValue[2] = {0,         vec.height}; /// Bottom Left
    /// Triangle 2
    returnValue[3] = {vec.width,          0}; /// Top Right
    returnValue[4] = {vec.width, vec.height}; /// Bottom Right
    returnValue[5] = {0,         vec.height}; /// Bottom Left

    for( int i = 0; i < 6; i++ ) { 
        returnValue[i].x += vec.left;
        returnValue[i].y += vec.top;
    }
    return returnValue;
}
