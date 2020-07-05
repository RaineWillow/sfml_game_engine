#include "main_menu.hpp"

MainMenu::MainMenu(ResourceManager * resMan) {
	_resManager = resMan;
	_data = new WidgetData;
	_data->active = -1;
	_data->clicked = false;

	_guiManager = new GuiManager(800, 600, _data);

	GMenu<MainMenu, void> * myMenu = new GMenu<MainMenu, void>(_guiManager->getNext(), 400, 100, 120, 400, 30);
	myMenu->setScrollable();
	GMenu<MainMenu, void> * testMenu = new GMenu<MainMenu, void>(_guiManager->getNext(), 100, 0, 120, 400, 30);
	testMenu->setScrollable();

	_guiManager->registerWidget(myMenu);
	_guiManager->registerWidget(testMenu);

	GButton<MainMenu, void> * startButton = new GButton<MainMenu, void>(15, 0, myMenu->getCenteredY(40), 100, 40);

	startButton->registerEvent("onHover", *this, &MainMenu::onBActive);
	startButton->registerEvent("onLeft", *this, &MainMenu::onBInactive);
	startButton->registerEvent("onClick", *this, &MainMenu::onBClick);

	startButton->addTitle("Start", _resManager->getFont(1), sf::Color(200, 200, 255));

	myMenu->registerWidget(startButton);

	GButton<MainMenu, void> * exitButton = new GButton<MainMenu, void>(16, 0, myMenu->getCenteredY(40), 100, 40);

	exitButton->registerEvent("onHover", *this, &MainMenu::onBActive);
	exitButton->registerEvent("onLeft", *this, &MainMenu::onBInactive);
	exitButton->registerEvent("onClick", *this, &MainMenu::onBClick);

	exitButton->addTitle("Exit", _resManager->getFont(1), sf::Color(200, 200, 255));

	myMenu->registerWidget(exitButton);

	GButton<MainMenu, void> * testButton = new GButton<MainMenu, void>(myMenu->getNext(), 0, myMenu->getCenteredY(40), 100, 40);
	testButton->addTitle("Tester", _resManager->getFont(1), sf::Color(200, 200, 255));
	myMenu->registerWidget(testButton);
/*
	for (int i = 0; i < 15; i++) {
		GButton<MainMenu, void> * makeButton = new GButton<MainMenu, void>(myMenu->getNext(), 0, myMenu->getCenteredY(40), 100, 40);
		std::ostringstream str1;
		str1 << i;
		makeButton->addTitle("Test " + str1.str(), _resManager->getFont(1), sf::Color(200, 200, 255));
		makeButton->registerEvent("onHover", *this, &MainMenu::onBActive);
		makeButton->registerEvent("onLeft", *this, &MainMenu::onBInactive);
		myMenu->registerWidget(makeButton);
	}

	for (int i = 0; i < 17; i++) {
		GButton<MainMenu, void> * makeButton = new GButton<MainMenu, void>(testMenu->getNext(), 0, testMenu->getCenteredY(40), 100, 40);
		std::ostringstream str1;
		str1 << i;
		makeButton->addTitle("Test " + str1.str(), _resManager->getFont(1), sf::Color(200, 200, 255));
		makeButton->registerEvent("onHover", *this, &MainMenu::onBActive);
		makeButton->registerEvent("onLeft", *this, &MainMenu::onBInactive);
		testMenu->registerWidget(makeButton);
	}
*/

	GTextBox<MainMenu, void> * textBox = new GTextBox<MainMenu, void>(testMenu->getNext(), 0, testMenu->getCenteredY(20), 100, 20, _resManager->getFont(1));
	textBox->addTitle("Enter Text Here...", sf::Color(130, 130, 130));
	testMenu->registerWidget(textBox);

	_controller = new Controller;
	_controller->mbAdd(sf::Mouse::Left);


}

MainMenu::~MainMenu() {
	delete _data;
	delete _guiManager;
	delete _controller;
}

void MainMenu::update(sf::RenderWindow & _window, sf::Event & event, bool happened) {
	char newChar = *"";
	if (happened) {
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
			case sf::Event::MouseWheelScrolled:
				_controller->mouseScrolled(event.mouseWheelScroll.delta);
				break;
		}
	}

	_data->mx = _controller->getMx();
	_data->my = _controller->getMy();

	_data->genUp = !_controller->getGen();

	_data->clicked = _controller->getMbClicked(sf::Mouse::Left);
	_data->mMoved = _controller->mMoved();

	_data->mDelta = _controller->mouseDelta();

	_guiManager->recText(newChar);
	_guiManager->update();

	if (_window.pollEvent(event)) {
		this->update(_window, event, true);
	}
}

void MainMenu::render(sf::RenderWindow * _window) {
	_window->clear(sf::Color::Black);
	//rendering happens here
	_window->draw(_guiManager->getRenderable());
}

void MainMenu::onBActive(Widget<MainMenu, void> * instance) {
	GButton<MainMenu, void> * castContext = dynamic_cast<GButton<MainMenu, void>*>(instance);
	castContext->wBox.setFillColor(sf::Color(255, 255, 255, 255));
}

void MainMenu::onBInactive(Widget<MainMenu, void> * instance) {
	GButton<MainMenu, void> * castContext = dynamic_cast<GButton<MainMenu, void>*>(instance);
	castContext->wBox.setFillColor(sf::Color(40, 75, 145, 255));
}

void MainMenu::onBClick(Widget<MainMenu, void> * instance) {
	GButton<MainMenu, void> * castContext = dynamic_cast<GButton<MainMenu, void>*>(instance);
	castContext->widgetSprite.setColor(sf::Color(255, 255, 255, 200));
	int id = castContext->getId();
	if (id == 15) {
		std::cout << id;
		this->_isActive = false;
		this->_myDat.id = 2;
	} else if (id == 16) {
		this->_isActive = false;
		this->_myDat.id = -1;
	}
}
