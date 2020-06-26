#include "gui_manager.hpp"

GuiManager::GuiManager(int w, int h) {
	_guiTexture.create(w, h);
}

GuiManager::~GuiManager() {
	for (int i = 0; i < (int)_widgets.size(); i++) {
		delete _widgets[i];
	}
}

void GuiManager::registerWidget(WidgetBase * widget) {
	_widgets.push_back(widget);
}

int GuiManager::getNext() {
	return (int)_widgets.size();
}
void GuiManager::update(WidgetData * data) {
	for (int i = 0; i < (int)_widgets.size(); i++) {
		_widgets[i]->update(data);
	}
}

sf::Sprite GuiManager::getRenderable() {
	_guiTexture.clear(sf::Color(0, 0, 0, 0));
	for (int i = 0; i < (int)_widgets.size(); i++) {
		_widgets[i]->render(&_guiTexture);
	}
	_guiTexture.display();
	sf::Sprite spr;
	spr.setTexture(_guiTexture.getTexture());
	return spr;
}
