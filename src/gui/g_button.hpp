#ifndef G_Button_hpp
#define G_Button_hpp
#include "SDL2/SDL.h"
#include "widget_base.hpp"
#include "widget.hpp"

template <typename ClassType, typename Result>
class GButton : public Widget<ClassType, Result>
{
	typedef Result (ClassType::*FunctionType)(WidgetBase*);
public:
	GButton(SDL_Renderer * renderer, SDL_Texture * texture, int x, int y, int w, int h, ClassType& object, FunctionType onClick)
	{
		_renderer = renderer;
		_texture = texture;
		_x = x;
		_y = y;
		_h = h;
		_w = w;
		this->registerEvent("onClick", object, onClick);
	}

	void update()
	{
		if (((*_mx >= _x) && (*_mx <= _x+_width)) && ((*_my >= _y) && (*_my <= _y+_height))) {
			if (*clicked == true) {
				this->callEvent("onClick");
			}
		}
	}

	void render()
	{
		SDL_Rect buttonRect;
		buttonRect.w = _width;
		buttonRect.h = _height;
		buttonRect.x = _x;
		buttonRect.y = _y;
		SDL_RenderCopy(renderer, texture, NULL, &buttonRect);
	}

private:

	SDL_Renderer * _renderer;
	SDL_Texture * _texture;
	int _x;
	int _y;
	int _w;
	int _h;
};


#endif
