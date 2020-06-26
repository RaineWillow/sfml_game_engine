#ifndef Gui_Manager_hpp
#define Gui_Manager_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "widget_base.hpp"
#include <vector>

class GuiManager {
public:
	GuiManager(int w, int h);
	~GuiManager();

	void registerWidget(WidgetBase * widget);
	int getNext();

	void update(WidgetData * data);
	sf::Sprite getRenderable();

private:
	std::vector<WidgetBase*> _widgets;
	sf::RenderTexture _guiTexture;
};


#endif
