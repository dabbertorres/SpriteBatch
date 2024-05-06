#ifndef COMMON_HPP
#define COMMON_HPP
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
namespace swift 
{
    std::array<sf::Vector2f, 6> getTrianglesFromVector(sf::Vector2f vec);
    std::array<sf::Vector2f, 6> getTrianglesFromRect(sf::FloatRect vec);
}
#endif
