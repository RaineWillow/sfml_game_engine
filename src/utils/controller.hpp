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
	/*
	void mbAdd(Uint8 mb);
	void mbDown(Uint8 mb, Sint32 mx, Sint32 my);
	void mbUp(Uint8 mb, Sint32 mx, Sint32 my);
	bool getMb(Uint8 mb);
	bool getMbClicked(Uint8 mb);

	void mouseMotion(Sint32 mx, Sint32 my);

	Sint32 getMx();
	Sint32 getMy();
	*/
private:
	std::map<sf::Keyboard::Key,ButtonData> _keyList;
	//std::map<Uint8,ButtonData> _mbList;

	//Sint32 _mx;
	//Sint32 _my;

};


#endif
