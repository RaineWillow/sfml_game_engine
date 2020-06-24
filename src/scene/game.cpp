#include "game.hpp"

Game::Game(sf::RenderWindow * window) {
	this->_window = window;
}

Game::~Game() {
	//pass
}

void Game::update() {
	sf::Event event;
	_window->pollEvent(event);
	switch (event.type) {
		case sf::Event::Closed:
			_window->close();
			this->_isActive = false;
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Q) {
				this->_isActive = false;
				this->_myDat.id = 0;
			}
			break;
	}
}

void Game::render() {
	_window->clear(sf::Color::Black);
	//rendering happens here
	_window->display();
}
