#include "game.hpp"

Game::Game(){//sf::RenderWindow * window) {
	//_window = window;
}

Game::~Game() {
	//pass
}

void Game::update(sf::RenderWindow & _window, sf::Event & event) {
	switch (event.type) {
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Q) {
				this->_isActive = false;
				this->_myDat.id = 1;
			}
			break;
	}
}

void Game::render(sf::RenderWindow * _window) {
	_window->clear(sf::Color::Black);
	//rendering happens here
}
