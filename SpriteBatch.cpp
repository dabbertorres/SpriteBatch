#include "SpriteBatch.hpp"

namespace swift
{
	SpriteBatch::SpriteBatch(const sf::Texture& tex, unsigned int s)
	:	vertices(s * 4),
		texture(tex),
	    spriteNum(0)
	{
		sf::Vector2f texSize = static_cast<sf::Vector2f>(texture.getSize());
		for(auto i = 0u; i < vertices.size(); i += 4)
		{
			vertices[i].texCoords = {0, 0};
			vertices[i + 1].texCoords = {texSize.x, 0};
			vertices[i + 2].texCoords = texSize;
			vertices[i + 3].texCoords = {0, texSize.y};
		}
	}
	
	const std::vector<sf::Vertex>& SpriteBatch::getVertices() const
	{
		return vertices;
	}

	std::array<sf::Vertex*, 4> SpriteBatch::addSprite()
	{
		if((spriteNum + 1) * 4 <= vertices.size())
		{
			unsigned int s = spriteNum * 4;
			spriteNum++;
			return {&vertices[s], &vertices[s + 1], &vertices[s + 2], &vertices[s + 3]};
		}
		else
			return {nullptr};
	}
	
	sf::Vector2u SpriteBatch::getTextureSize() const
	{
		return texture.getSize();
	}

	void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = &texture;
		target.draw(vertices.data(), spriteNum * 4, sf::Quads, states);
	}
}