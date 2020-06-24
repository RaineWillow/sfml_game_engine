#ifndef Window_hpp
#define Window_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <string>

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
};

#endif
