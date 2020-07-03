#include "main_menu.hpp"

MainMenu::MainMenu(ResourceManager * resMan) {
	_resManager = resMan;
	_data = new WidgetData;
	_data->active = -1;
	_data->clicked = false;

	_guiManager = new GuiManager(800, 600, _data);

	GMenu<MainMenu, void> * myMenu = new GMenu<MainMenu, void>(_guiManager->getNext(), 0, 0, 200, 600, 30);
	myMenu->setScrollable();

	_guiManager->registerWidget(myMenu);

	GButton<MainMenu, void> * startButton = new GButton<MainMenu, void>(myMenu->getNext(), 0, myMenu->getCenteredY(40), 100, 40);

	startButton->registerEvent("onHover", *this, &MainMenu::onBActive);
	startButton->registerEvent("onLeft", *this, &MainMenu::onBInactive);
	startButton->registerEvent("onClick", *this, &MainMenu::onBClick);

	startButton->useSprite(_resManager->getSprite(3));
	startButton->addTitle("Start", _resManager->getFont(1), sf::Color::Red);

	myMenu->registerWidget(startButton);

	GButton<MainMenu, void> * exitButton = new GButton<MainMenu, void>(myMenu->getNext(), 0, myMenu->getCenteredY(40), 100, 40);

	exitButton->registerEvent("onHover", *this, &MainMenu::onBActive);
	exitButton->registerEvent("onLeft", *this, &MainMenu::onBInactive);
	exitButton->registerEvent("onClick", *this, &MainMenu::onBClick);

	exitButton->useSprite(_resManager->getSprite(3));
	exitButton->addTitle("Exit", _resManager->getFont(1), sf::Color::Red);

	myMenu->registerWidget(exitButton);

	GButton<MainMenu, void> * testButton = new GButton<MainMenu, void>(myMenu->getNext(), 0, myMenu->getCenteredY(40), 100, 40);
	testButton->addTitle("Tester", _resManager->getFont(1), sf::Color::Red);
	myMenu->registerWidget(testButton);

	_controller = new Controller;
	_controller->mbAdd(sf::Mouse::Left);


}

MainMenu::~MainMenu() {
	delete _data;
	delete _guiManager;
	delete _controller;
}

void MainMenu::update(sf::RenderWindow & _window, sf::Event & event) {
	char newChar = *"";
	switch (event.type) {
		case sf::Event::KeyPressed:
			_controller->keyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			_controller->keyUp(event.key.code);
			break;
		case sf::Event::MouseButtonPressed:
			_controller->mbDown(event.mouseButton.button);
			break;
		case sf::Event::MouseButtonReleased:
			_controller->mbUp(event.mouseButton.button);
			break;
		case sf::Event::MouseMoved:
			_controller->mouseMotion(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::TextEntered:
			if (event.text.unicode < 128) {
				newChar = static_cast<char>(event.text.unicode);
			}
			break;
	}

	_data->mx = _controller->getMx();
	_data->my = _controller->getMy();

	_data->genUp = !_controller->getGen();

	_data->clicked = _controller->getMbClicked(sf::Mouse::Left);
	_data->mMoved = _controller->mMoved();

	_guiManager->recText(newChar);
	_guiManager->update();

	if (_window.pollEvent(event)) {
		this->update(_window, event);
	}
}

void MainMenu::render(sf::RenderWindow * _window) {
	_window->clear(sf::Color::Black);
	//rendering happens here
	_window->draw(_guiManager->getRenderable());
}

void MainMenu::onBActive(Widget<MainMenu, void> * instance) {
	GButton<MainMenu, void> * castContext = dynamic_cast<GButton<MainMenu, void>*>(instance);
	castContext->widgetSprite.setColor(sf::Color(255, 255, 255, 255));
}

void MainMenu::onBInactive(Widget<MainMenu, void> * instance) {
	GButton<MainMenu, void> * castContext = dynamic_cast<GButton<MainMenu, void>*>(instance);
	castContext->widgetSprite.setColor(sf::Color(255, 255, 255, 200));
}

void MainMenu::onBClick(Widget<MainMenu, void> * instance) {
	GButton<MainMenu, void> * castContext = dynamic_cast<GButton<MainMenu, void>*>(instance);
	castContext->widgetSprite.setColor(sf::Color(255, 255, 255, 200));
	int id = castContext->getId();
	if (id == 0) {
		std::cout << id;
		this->_isActive = false;
		this->_myDat.id = 2;
	} else if (id == 1) {
		this->_isActive = false;
		this->_myDat.id = -1;
	}
}
