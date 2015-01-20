#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "SpriteBatch.hpp"

namespace swift
{
	class Sprite
	{
		public:
			Sprite(SpriteBatch& batch);
			Sprite(SpriteBatch& batch, const sf::IntRect& texRect);
			~Sprite();

			void move(const sf::Vector2f& offset);
			void rotate(float a);
			void scale(const sf::Vector2f& factor);

			sf::IntRect getTextureRect() const;
			sf::Color getColor() const;
			sf::Vector2f getPosition() const;
			float getRotation() const;
			sf::Vector2f getScale() const;
			sf::Vector2f getOrigin() const;

			sf::FloatRect getLocalBounds() const;
			sf::FloatRect getGlobalBounds() const;

			void setTextureRect(const sf::IntRect& texRect);
			void setColor(const sf::Color& color);
			void setPosition(const sf::Vector2f& pos);
			void setRotation(float a);
			void setScale(const sf::Vector2f& scale);
			void setOrigin(const sf::Vector2f& o);

		private:
			std::array<sf::Vertex*, 4> vertices;
			sf::Vector2f origin;
			sf::Vector2f scaleFactor;
			float angle;
	};
}

#endif // SPRITE_HPP
