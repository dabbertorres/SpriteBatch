#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "SpriteBatch.hpp"
#include "Sprite.hpp"

int main(int argc, char **argv)
{
	sf::RenderWindow window;
	
	window.create({800, 600, 32}, "SFML");
	
	sf::Texture texture;
	if(!texture.loadFromFile("../test.png"))
	{
		std::cerr << "error loading texture\n";
	}
	
	swift::SpriteBatch batch(texture, 3);
	
	swift::Sprite spriteOne(batch);
	spriteOne.setOrigin({spriteOne.getLocalBounds().width / 2, spriteOne.getLocalBounds().height / 2});
	spriteOne.setScale({2, 2});
	spriteOne.setPosition({400, 400});
	spriteOne.scale({0.5, 0.5});

	swift::Sprite spriteTwo(batch);
	spriteTwo.setPosition({400, 200});
    /// Should only show half spriteThree
	swift::Sprite spriteThree(batch, sf::IntRect(0, 0, 32, 64));
	spriteThree.setPosition({400, 100});
	
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if(event.key.code == sf::Keyboard::Escape)
						window.close();
					break;
				default:
					break;
			}
		}
		
		window.clear();
		window.draw(batch);
		window.display();
	}
	
	return 0;
}
