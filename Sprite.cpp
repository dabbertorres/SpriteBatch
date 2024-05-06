#include "Sprite.hpp"
#include "Common.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace swift
{
	Sprite::Sprite(SpriteBatch& batch)
	:	origin(0, 0),
	    scaleFactor(1, 1),
	    angle(0)
	{
		vertices = batch.addSprite();
		
		if(vertices[0] == nullptr)
			throw nullptr;
		
		sf::Vector2u texSize = batch.getTextureSize();

        std::array<sf::Vector2f, 6> triangles = getTrianglesFromVector(sf::Vector2f(texSize));
        for( int i = 0; i < 6; i++ ) { 
            vertices[i]->position = triangles[i];
        }
	}

	Sprite::Sprite(SpriteBatch& batch, const sf::IntRect& texRect)
	:	Sprite(batch)
	{
        this->setTextureRect(texRect);
	}

	Sprite::~Sprite()
	{
		for(auto& v : vertices)
		{
			v->color = {0, 0, 0, 0};
			v->position = {0, 0};
		}
	}

	void Sprite::move(const sf::Vector2f& offset)
	{
		for(auto & v : vertices)
		{
			v->position += offset;
		}
	}

	void Sprite::rotate(float a)
	{
		angle += a;
		
		setRotation(angle);
	}

	void Sprite::scale(const sf::Vector2f& factor)
	{
		setScale({scaleFactor.x * factor.x, scaleFactor.y * factor.y});
	}

	sf::IntRect Sprite::getTextureRect() const
	{
		return {static_cast<sf::Vector2i>(vertices[0]->texCoords), static_cast<sf::Vector2i>(vertices[2]->texCoords - vertices[0]->texCoords)};
	}

	sf::Color Sprite::getColor() const
	{
		return vertices[0]->color;
	}

	sf::Vector2f Sprite::getPosition() const
	{
		return vertices[0]->position + origin;
	}

	float Sprite::getRotation() const
	{
		return angle;
	}

	sf::Vector2f Sprite::getScale() const
	{
		return scaleFactor;
	}

	sf::Vector2f Sprite::getOrigin() const
	{
		return origin;
	}

	sf::FloatRect Sprite::getLocalBounds() const
	{
		return {vertices[0]->texCoords, vertices[2]->texCoords - vertices[0]->texCoords};
	}

	sf::FloatRect Sprite::getGlobalBounds() const
	{
		return {vertices[0]->position + origin, vertices[2]->position - vertices[0]->position};
	}


	void Sprite::setTextureRect(const sf::IntRect& texRect)
	{
        std::array<sf::Vector2f, 6> triangles = getTrianglesFromRect(sf::FloatRect(texRect));
        for( int i = 0; i < 6; i++ ) { 
            vertices[i]->texCoords = triangles[i];
        }
	}

	void Sprite::setColor(const sf::Color& color)
	{
		for(auto& v : vertices)
			v->color = color;
	}

	void Sprite::setPosition(const sf::Vector2f& pos)
	{
		sf::Vector2f topLeft = vertices[0]->position;
		
		for(auto& v : vertices)
			v->position = pos + v->position - topLeft - origin;
	}

	void Sprite::setRotation(float a)
	{
		angle = a;
		
		if(angle < 0)
			angle += 360 * (static_cast<int>(angle) / 360);
		else if(angle > 360)
			angle -= 360 * (static_cast<int>(angle) / 360);
			
		constexpr float PI = 3.14159265359f;
		
		// get the local coordinates
		std::array<sf::Vector2f, 6> verts;
		for(int i = 0; i < 6; i++)
			verts[i] = vertices[i]->position - vertices[0]->position - origin;
		
		std::array<sf::Vector2f, 6> newVerts;
		for(int i = 0; i < 6; i++)
		{
			newVerts[i] = {	verts[i].x * std::cos(angle * PI / 180.f) - verts[i].y * std::sin(angle * PI / 180.f), 
							verts[i].x * std::sin(angle * PI / 180.f) + verts[i].y * std::cos(angle * PI / 180.f)};
			newVerts[i] += origin + vertices[0]->position;
		}
		
		for(int i = 5; i >= 0; i--)
			vertices[i]->position = newVerts[i];
	}

	void Sprite::setScale(const sf::Vector2f& scale)
	{
		sf::Vector2f topLeft = vertices[0]->position;
		
		for(auto & v : vertices)
		{
			sf::Vector2f dist = v->position - topLeft - origin;
			dist.x *= scale.x / scaleFactor.x;
			dist.y *= scale.y / scaleFactor.y;
			v->position = dist + topLeft + origin;
		}
		
		origin.x *= scale.x / scaleFactor.x;
		origin.y *= scale.y / scaleFactor.y;
		
		scaleFactor = scale;
	}

	void Sprite::setOrigin(const sf::Vector2f& o)
	{
		origin = o;
	}
}
