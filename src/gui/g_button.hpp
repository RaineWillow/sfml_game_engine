#ifndef G_Button_hpp
#define G_Button_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "widget_base.hpp"
#include "widget.hpp"
#include <string>

template <typename ClassType, typename Result>
class GButton : public Widget<ClassType, Result>
{
	typedef Result (ClassType::*FunctionType)(Widget<ClassType,Result>*);
public:
	GButton(int id, int x, int y, double w, double h)
	{
		_id = id;
		_lastId = -1;
		_x = x;
		_y = y;
		_w = w;
		_h = h;
	}

	void useSprite(sf::Sprite setSprite) {
		widgetSprite = setSprite;
		this->widgetSprite.setPosition(_x, _y);
		this->widgetSprite.setScale(_w / this->widgetSprite.getTextureRect().width, _h / this->widgetSprite.getTextureRect().height);
		this->widgetSprite.setColor(sf::Color(255, 255, 255, 200));
		_useSprite = true;
	}

	void update(WidgetData * data)
	{
		if (((((data->mx >= _x) && (data->mx <= _x+_w)) && ((data->my >= _y) && (data->my <= _y+_h))))) {
			data->active = _id;

			if (data->clicked) {
				this->callEvent("onClick");
			}

			if ((!_wasActive) && (data->mMoved)) {
				std::cout << "working!\n";
				_wasActive = true;
				this->callEvent("onActive");
			}

		} else {
			if ((_wasActive) && ((data->mMoved))) {
				this->callEvent("onInactive");
				_wasActive = false;
			}
		}
/*
		if ((data->active == _id)) {

			if (data->clicked == true) {
				this->callEvent("onClick");
			}

			if (_lastId != data->active) {
				_wasActive = true;
				this->callEvent("onActive");
			}
		} else {
			if (_lastId != data->active) {
				if (_wasActive) {
					this->callEvent("onInactive");
					_wasActive = false;
				}
			}
		}

		_lastId = data->active;
*/
	}

	void render(sf::RenderTexture * renderOut) {
		if (_useSprite) {
			renderOut->draw(widgetSprite);
		}

		if (_drawText) {
			title.setOrigin(title.getLocalBounds().width/2, title.getLocalBounds().height/2);
			title.setPosition(_x+_w/2, _y+_h/2);
			renderOut->draw(title);
		}

	}

	void addTitle(std::string myTitle, sf::Font * font, sf::Color color) {
		_drawText = true;
		title.setFont(*font);
		title.setString(myTitle);
		title.setCharacterSize(_h/2);
		title.setFillColor(color);
	}

	int getId() {
		return _id;
	}

	sf::Sprite widgetSprite;
	sf::Text title;

private:
	int _id;
	int _lastId;
	int _lastHover;
	bool _wasActive = false;

	int _x;
	int _y;
	double _w;
	double _h;

	bool _useSprite = false;

	bool _drawText;

};


#endif
