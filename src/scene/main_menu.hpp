#ifndef Main_Menu_hpp
#define Main_Menu_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "scene.hpp"

class MainMenu : public Scene {
public:
	MainMenu(); //
	~MainMenu();
	void update(sf::RenderWindow & _window);
	void render(sf::RenderWindow & _window);
private:
	//sf::RenderWindow * _window;
};

#endif
