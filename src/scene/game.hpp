#ifndef Game_hpp
#define Game_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "scene.hpp"

class Game : public Scene {
public:
	Game(); //
	~Game();
	void update(sf::RenderWindow & _window);
	void render(sf::RenderWindow & _window);
private:
	//sf::RenderWindow * _window;

};

#endif
