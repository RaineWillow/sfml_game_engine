#include "window.hpp"
Window::Window(int w, int h, std::string title) {
	_window = new sf::RenderWindow(sf::VideoMode(w, h), title);
	_window->setVerticalSyncEnabled(true);
	_window->setFramerateLimit(60);
	
}

Window::~Window() {
	delete _window;
}

void Window::update() {
	sf::Event event;
	_window->pollEvent(event);
	switch (event.type) {
		case sf::Event::Closed:
			_window->close();
			_isRunning = false;
			break;
	}
}

void Window::render() {
	_window->clear(sf::Color::Black);
	//rendering happens here
	_window->display();
}

void Window::run() {
	while (_window->isOpen()) {
		update();
		render();
	}
}

bool Window::running() {
	return _isRunning;
}
