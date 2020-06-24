#ifndef Window_hpp
#define Window_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "../scene/scene.hpp"
#include "../scene/game.hpp"
#include <string>
#include <map>

class Window {
public:
	Window(int w, int h, std::string title);
	~Window();
	void update();
	void render();
	void run();
	bool running();
private:
	sf::RenderWindow * _window;
	bool _isRunning;
	std::map<int, Scene *> _scenes;
};

#endif
