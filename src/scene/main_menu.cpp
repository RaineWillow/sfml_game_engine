#include "main_menu.hpp"

MainMenu::MainMenu(ResourceManager * resMan) {
	_resManager = resMan;
	_data = new WidgetData;
	_data->active = -1;
	_data->clicked = false;

	GButton<MainMenu, void> * startButton = new GButton<MainMenu, void>(_data, 0, _resManager->getSprite(3), 0, 0, 0.4, 0.4,
		*this,
		&MainMenu::onBActive,
		&MainMenu::onBInactive,
		&MainMenu::onBClick
	);
	_widgets.push_back(startButton);

	GButton<MainMenu, void> * exitButton = new GButton<MainMenu, void>(_data, 1, _resManager->getSprite(3), 0, 100, 0.4, 0.4,
	 	*this,
		&MainMenu::onBActive,
		&MainMenu::onBInactive,
		&MainMenu::onBClick
	);
	_widgets.push_back(exitButton);

	_controller = new Controller;
	_controller->keyAdd(sf::Keyboard::Up);
	_controller->keyAdd(sf::Keyboard::Down);
	_controller->keyAdd(sf::Keyboard::Z);


}

MainMenu::~MainMenu() {
	delete _data;
	delete _controller;
	for (int i = 0; i < (int)_widgets.size(); i++) {
		delete _widgets[i];
	}
}

void MainMenu::update(sf::RenderWindow & _window, sf::Event & event) {
	switch (event.type) {
		case sf::Event::KeyPressed:
			_controller->keyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			_controller->keyUp(event.key.code);
			break;
	}

	if (_controller->getKeyClicked(sf::Keyboard::Down)) {
		if (_data->active < (int)_widgets.size()-1) {
			_data->active++;
		}
	}

	if (_controller->getKeyClicked(sf::Keyboard::Up)) {
		if (_data->active > 0) {
			_data->active--;
		}
	}

	_data->clicked = _controller->getKeyClicked(sf::Keyboard::Z);

	for (int i = 0; i < (int)_widgets.size(); i++) {
		_widgets[i]->update();
	}
}

void MainMenu::render(sf::RenderWindow * _window) {
	_window->clear(sf::Color::Black);
	//rendering happens here
	for (int i = 0; i < (int)_widgets.size(); i++) {
		_widgets[i]->render(_window);
	}
}

void MainMenu::onBActive(Widget<MainMenu, void> * instance) {
	GButton<MainMenu, void> * castContext = dynamic_cast<GButton<MainMenu, void>*>(instance);
	//castContext->widgetSprite.scale(1.2, 1.2);
	castContext->widgetSprite.setColor(sf::Color(255, 255, 255, 255));
	std::cout << "called";
}

void MainMenu::onBInactive(Widget<MainMenu, void> * instance) {
	GButton<MainMenu, void> * castContext = dynamic_cast<GButton<MainMenu, void>*>(instance);
	//castContext->widgetSprite.setScale(castContext->ww, castContext->wh);
	castContext->widgetSprite.setColor(sf::Color(255, 255, 255, 128));
	std::cout << "called";
}

void MainMenu::onBClick(Widget<MainMenu, void> * instance) {
	GButton<MainMenu, void> * castContext = dynamic_cast<GButton<MainMenu, void>*>(instance);
	//castContext->widgetSprite.setScale(castContext->ww, castContext->wh);
	castContext->widgetSprite.setColor(sf::Color(255, 255, 255, 128));
	int id = castContext->getId();
	if (id == 0) {
		this->_isActive = false;
		this->_myDat.id = 2;
	} else if (id == 1) {
		this->_isActive = false;
		this->_myDat.id = -1;
	}
}
