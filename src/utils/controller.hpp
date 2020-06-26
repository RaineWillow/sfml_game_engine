#ifndef Controller_hpp
#define Controller_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>

struct ButtonData{
	bool down;
	bool clicked;
};

class Controller {
public:
	//keyboard functions-------------------------------------------------------
	void keyAdd(sf::Keyboard::Key qKey);
	void keyDown(sf::Keyboard::Key qKey);
	void keyUp(sf::Keyboard::Key qKey);
	bool getKey(sf::Keyboard::Key qKey);
	bool getKeyClicked(sf::Keyboard::Key qKey);

	//mouse functions----------------------------------------------------------

	void mbAdd(sf::Mouse::Button mb);
	void mbDown(sf::Mouse::Button mb);
	void mbUp(sf::Mouse::Button mb);
	bool getMb(sf::Mouse::Button mb);
	bool getMbClicked(sf::Mouse::Button mb);

	void mouseMotion(int mx, int my);
	bool mMoved();

	int getMx();
	int getMy();
private:
	std::map<sf::Keyboard::Key,ButtonData> _keyList;
	std::map<sf::Mouse::Button,ButtonData> _mbList;

	int _mx;
	int _my;
	bool _mMoved = false;

};


#endif
