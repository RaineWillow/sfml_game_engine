#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>

int main()
{
	std::cout << "Got here!\n";
    sf::RenderWindow _window(sf::VideoMode(800, 480, 32), "Lighting Test");
    _window.setFramerateLimit(60);
    std::cout << "Got here!\n";

    sf::Shader lightingShader;
    sf::RenderStates renderState;

    sf::Texture texture;
    texture.loadFromFile("image.png");

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("light.png");

    sf::Sprite background;
    background.setTexture(backgroundTexture);

    while (_window.isOpen())
    {
	    std::cout << "Got here!\n";
        int x = sf::Mouse::getPosition(_window).x;
        int y = sf::Mouse::getPosition(_window).y;
	   if (sf::Shader::isAvailable()) {
		   std::cout << "Got here!\n";
	   }
        lightingShader.loadFromFile("lightingShader.frag", sf::Shader::Fragment);
	   std::cout << "Got here!\n";
        lightingShader.setParameter("exposure", 0.25f);
        lightingShader.setParameter("decay", 0.97f);
        lightingShader.setParameter("density", 0.97f);
        lightingShader.setParameter("weight", 0.5f);
        lightingShader.setParameter("lightPositionOnScreen", sf::Vector2f(0.5f, 0.5f));
        lightingShader.setParameter("myTexture", sf::Shader::CurrentTexture);
        renderState.shader = &lightingShader;
	   std::cout << "Got here!\n";

        _window.clear(sf::Color::Black);
        sprite.setPosition(x, y);
        //sprite.setColor(sf::Color::Black);
        //background.setPosition(400, 240);
        _window.draw(background);
        _window.draw(sprite, renderState);
        _window.display();
    }
    return 0;
}
