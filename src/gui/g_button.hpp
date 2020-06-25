#ifndef G_Button_hpp
#define G_Button_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "widget_base.hpp"
#include "widget.hpp"

template <typename ClassType, typename Result>
class GButton : public Widget<ClassType, Result>
{
	typedef Result (ClassType::*FunctionType)(Widget<ClassType,Result>*);
public:
	GButton(WidgetData * data, int id, sf::Sprite mySprite, int x, int y, double w, double h,
		ClassType& object,
		FunctionType onActive,
		FunctionType onInactive,
		FunctionType onClick)
	{
		_data = data;
		_id = id;
		_lastId = -1;
		widgetSprite = mySprite;
		this->widgetSprite.setPosition(x, y);
		this->widgetSprite.setScale(w, h);
		this->widgetSprite.setColor(sf::Color(255, 255, 255, 128));
		ww = w;
		wh = h;

		this->registerEvent("onActive", object, onActive);
		this->registerEvent("onInactive", object, onInactive);
		this->registerEvent("onClick", object, onClick);
	}

	void update()
	{
		if ((_data->active == _id)) {
			if (_data->clicked == true) {
				this->callEvent("onClick");
			}

			if (_lastId != _data->active) {
				std::cout << "pop " << _lastId << " " << _data->active << "\n";
				_wasActive = true;
				this->callEvent("onActive");
			}
		} else {
			if (_wasActive) {
				this->callEvent("onInactive");
				_wasActive = false;
			}
		}
		_lastId = _data->active;
	}

	void render(sf::RenderWindow * _window) {
		_window->draw(widgetSprite);
	}

	int getId() {
		return _id;
	}

	sf::Sprite widgetSprite;
	bool ww;
	bool wh;

private:
	WidgetData * _data;
	int _id;
	int _lastId;
	bool _wasActive = false;
};


#endif
