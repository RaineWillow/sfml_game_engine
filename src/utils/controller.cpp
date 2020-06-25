#include "controller.hpp"

void Controller::keyAdd(sf::Keyboard::Key qKey) {
	if (_keyList.find(qKey) == _keyList.end()) {
		ButtonData data = {false, false};
		_keyList.insert({ qKey, data });
	} else {
		std::cout << "key is already watched!\n";
	}
}

void Controller::keyDown(sf::Keyboard::Key qKey) {
	if (_keyList.find(qKey) == _keyList.end()) {
		std::cout << "key input not in list of watched keys, add the key to the watched keys list\n";
	} else {
		_keyList[qKey].down = true;
	}
}

void Controller::keyUp(sf::Keyboard::Key qKey) {
	if (_keyList.find(qKey) == _keyList.end()) {
		std::cout << "key input not in list of watched keys, add the key to the watched keys list\n";
	} else {
		if (_keyList[qKey].down) {
			_keyList[qKey].clicked = true;
		}
		_keyList[qKey].down = false;
	}
}

bool Controller::getKey(sf::Keyboard::Key qKey) {
	if (_keyList.find(qKey) == _keyList.end()) {
		std::cout << "key input not in list of watched keys, add the key to the watched keys list\n";
	} else {
		return _keyList[qKey].down;
	}
	return false;
}

bool Controller::getKeyClicked(sf::Keyboard::Key qKey) {
	if (_keyList.find(qKey) == _keyList.end()) {
		std::cout << "key input not in list of watched keys, add the key to the watched keys list\n";
	} else {
		if (_keyList[qKey].clicked) {
			_keyList[qKey].clicked = false;
			return true;
		} else {
			return false;
		}
	}
	return false;
}

/*
void Controller::mbAdd(Uint8 mb) {
	std::cout << "added\n";
	if (_mbList.find(mb) == _mbList.end()) {
		ButtonData data = {false, false};
		_mbList.insert({ mb, data });
	} else {
		std::cout << "mouse button is already watched!\n";
	}
}

void Controller::mbDown(Uint8 mb, Sint32 mx, Sint32 my) {
	_mx = mx;
	_my = my;
	if (_mbList.find(mb) == _mbList.end()) {
		std::cout << "mouse button is not in list of watched buttons, add the button 1.\n";
	} else {
		_mbList[mb].down = true;
	}
}

void Controller::mbUp(Uint8 mb, Sint32 mx, Sint32 my) {
	_mx = mx;
	_my = my;
	if (_mbList.find(mb) == _mbList.end()) {
		std::cout << "mouse button is not in list of watched buttons, add the button 2.\n";
	} else {
		_mbList[mb].down = false;
		_mbList[mb].clicked = true;
	}
}

bool Controller::getMb(Uint8 mb) {
	if (_mbList.find(mb) == _mbList.end()) {
		std::cout << "mouse button is not in list of watched buttons, add the button 3.\n";
	} else {
		return _mbList[mb].down;
	}
	return false;
}

bool Controller::getMbClicked(Uint8 mb) {
	if (_mbList.find(mb) == _mbList.end()) {
		std::cout << "mouse button is not in list of watched buttons, add the button 4.\n";
	} else {
		if (_mbList[mb].clicked) {
			_mbList[mb].clicked = false;
			return true;
		} else {
			return false;
		}
	}
	return false;
}

void Controller::mouseMotion(Sint32 mx, Sint32 my){
	_mx = mx;
	_my = my;
}

Sint32 Controller::getMx() {
	return _mx;
}

Sint32 Controller::getMy() {
	return _my;
}
*/
