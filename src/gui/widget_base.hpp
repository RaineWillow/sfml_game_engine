#ifndef Widget_Base_hpp
#define Widget_Base_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

struct WidgetData {
	int active;
	bool clicked;
};

class WidgetBase {
public:
	virtual void update()=0;
	virtual void render(sf::RenderWindow * _window)=0;
};

#endif
