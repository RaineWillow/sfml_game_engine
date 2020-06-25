#include "main_menu.hpp"

MainMenu::MainMenu() {
	//this->_window = window;
}

MainMenu::~MainMenu() {
	std::cout << "destroyed\n";
}

void MainMenu::update(sf::RenderWindow & _window, sf::Event & event) {
	switch (event.type) {
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::E) {
				std::cout << "E was pushed\n";
				this->_isActive = false;
				this->_myDat.id = 2;
			}
			break;
	}
}

void MainMenu::render(sf::RenderWindow & _window) {
	_window.clear(sf::Color::Black);
	//rendering happens here
}
