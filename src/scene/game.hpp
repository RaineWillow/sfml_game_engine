#ifndef Game_hpp
#define Game_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "scene.hpp"

class Game : public Scene {
public:
	Game(sf::RenderWindow * window);
	~Game();
	void update();
	void render();
private:
	sf::RenderWindow * _window;

};

#endif
