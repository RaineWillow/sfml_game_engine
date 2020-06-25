#ifndef Main_Menu_hpp
#define Main_Menu_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "../core/resource_manager.hpp"
#include "../utils/controller.hpp"
#include "../gui/widget_base.hpp"
#include "../gui/widget.hpp"
#include "../gui/g_button.hpp"
#include <vector>
#include <iostream>
#include "scene.hpp"

class MainMenu : public Scene {
public:
	MainMenu(ResourceManager * resMan);
	~MainMenu();
	void update(sf::RenderWindow & _window, sf::Event & event);
	void render(sf::RenderWindow * _window);

	void onBActive(Widget<MainMenu, void> * instance);
	void onBInactive(Widget<MainMenu, void> * instance);
	void onBClick(Widget<MainMenu, void> * instance);
private:
	ResourceManager * _resManager;
	Controller * _controller;
	std::vector<WidgetBase*> _widgets;
	WidgetData * _data;
};

#endif
