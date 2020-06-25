#include "main_menu.hpp"

MainMenu::MainMenu() {
	//this->_window = window;
}

MainMenu::~MainMenu() {
	std::cout << "destroyed\n";
}

void MainMenu::update(sf::RenderWindow & _window) {
	sf::Event event;
	_window.pollEvent(event);
	switch (event.type) {
		case sf::Event::Closed:
			_window.close();
			this->_isActive = false;
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::E) {
				this->_isActive = false;
				this->_myDat.id = 2;
			}
			break;
	}
}

void MainMenu::render(sf::RenderWindow & _window) {
	_window.clear(sf::Color::Black);
	//rendering happens here
	_window.display();
}
