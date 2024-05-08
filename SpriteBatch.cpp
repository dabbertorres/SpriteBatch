#include "SpriteBatch.hpp"
#include "Common.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>

namespace swift
{
	SpriteBatch::SpriteBatch(const sf::Texture& tex, unsigned int s)
	:	vertices(s * 6),
		texture(tex),
	    spriteNum(0)
	{
		sf::Vector2f texSize = static_cast<sf::Vector2f>(texture.getSize());
		for(auto i = 0u; i < vertices.size(); i += 6)
		{
            std::array<sf::Vector2f, 6> triangles = getTrianglesFromVector(texSize);
            for( int j = 0; j < 6; j++ ) { 
                vertices[i+j].texCoords = triangles[j];
            }
		}
	}
	
	const std::vector<sf::Vertex>& SpriteBatch::getVertices() const
	{
		return vertices;
	}

	std::array<sf::Vertex*, 6> SpriteBatch::addSprite()
	{
		if((spriteNum + 1) * 6 <= vertices.size())
		{
			unsigned int s = spriteNum * 6;
			spriteNum++;
			return {&vertices[s], &vertices[s + 1], &vertices[s + 2], &vertices[s + 3], &vertices[s+4], &vertices[s+5]};
		}
		else
        {
			return {nullptr};
        }
	}
	
	sf::Vector2u SpriteBatch::getTextureSize() const
	{
		return texture.getSize();
	}

	void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = &texture;
		target.draw(vertices.data(), spriteNum * 6, sf::Triangles, states);
	}
}
