#ifndef Scene_hpp
#define Scene_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

struct SceneData {
	int id = 0;
	std::vector<std::string> args;
};

class Scene {
public:

	virtual void update(sf::RenderWindow & _window)=0;
	virtual void render(sf::RenderWindow & _window)=0;

	SceneData run(sf::RenderWindow & _window) {
		while (_isActive) {
			this->update(_window);
			this->render(_window);
		}
	return _myDat;
	}

	bool _isActive = true;
	SceneData _myDat;
};

#endif
