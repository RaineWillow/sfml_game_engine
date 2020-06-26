#ifndef Widget_Base_hpp
#define Widget_Base_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

struct WidgetData {
	int mx;
	int my;
	bool mMoved = false;

	int active = -1;
	bool clicked;
};

class WidgetBase {
public:
	virtual void update(WidgetData * data)=0;
	virtual void render(sf::RenderTexture * renderOut)=0;
};

#endif
