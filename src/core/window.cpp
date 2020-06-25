#include "window.hpp"
Window::Window(int w, int h, std::string title) {
	_window = new sf::RenderWindow(sf::VideoMode(w, h), title);
	_window->setVerticalSyncEnabled(true);
	_window->setFramerateLimit(60);

	Scene * game = new Game();
	Scene * menu = new MainMenu();
	_scenes.insert(std::make_pair(1, menu));
	_scenes.insert(std::make_pair(2, game));
	_doingScenes = true;
}

Window::~Window() {
	for (auto const& x : _scenes) {
		delete x.second;
	}
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

	int currScene = 1;
	while (_doingScenes) {
		SceneData nextScene = _scenes[currScene]->run(*_window);
		if (nextScene.id == 0) {
			_window->close();
			_isRunning = false;
			_doingScenes = false;
		} else {
			if (_scenes.find(nextScene.id) == _scenes.end()) {
				std::cout << "Tried to access non-existent scene. " << nextScene.id << "\n";
				_doingScenes = false;
			} else {
				currScene = nextScene.id;
			}
		}
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
