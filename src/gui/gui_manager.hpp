#ifndef Gui_Manager_hpp
#define Gui_Manager_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "widget_base.hpp"
#include <iostream>
#include <vector>

class GuiManager {
public:
	GuiManager(int w, int h, WidgetData * data);
	~GuiManager();

	void registerWidget(WidgetBase * widget);
	int getNext();

	void recText(char myChar);

	void update();
	sf::Sprite getRenderable();

private:
	WidgetData * _data;
	std::vector<WidgetBase*> _widgets;
	sf::RenderTexture _guiTexture;
};


#endif
