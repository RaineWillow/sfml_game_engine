#ifndef G_TextwBox_hpp
#define G_TextwBox_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "widget_base.hpp"
#include "widget.hpp"
#include <string>
#include <chrono>

template <typename ClassType, typename Result>
class GTextBox : public Widget<ClassType, Result> {
	typedef Result (ClassType::*FunctionType)(Widget<ClassType,Result>*);
public:
	GTextBox(int id, int x, int y, double w, double h, sf::Font * font) {
		_id = id;
		_x = x;
		_y = y;
		_w = w;
		_h = h;

		wBox.setPosition(sf::Vector2f(_x, _y));
		wBox.setSize(sf::Vector2f(_w, _h));
		wBox.setFillColor(sf::Color(200, 200, 200));
		wBox.setOutlineThickness(5.0);
		wBox.setOutlineColor(sf::Color(230, 230, 230));

		text.setFont(*_font);
		text.setString(_textInput);
		text.setCharacterSize(_h/2);
		text.setFillColor(sf::Color::Black);
		text.setPosition(_x+1, _y);

		cursor.setPosition(sf::Vector2f(_x+1, _y+1));
		cursor.setSize(sf::Vector2f(_w/30, _h));
		cursor.setFillColor(sf::Color(0, 0, 0));

		_currTime = std::chrono::high_resolution_clock::now();
		std::chrono::milliseconds defDur(700);
		blinkDur = defDur;

		_textView.reset(sf::FloatRect(_x, _y, _w, _h));
		_font = font;
	}

	bool update(WidgetData * data)
	{
		if (((((data->mx >= _x) && (data->mx <= _x+_w)) && ((data->my >= _y) && (data->my <= _y+_h))))) {
			data->setHover(_id);

			if (data->clicked) {
				data->setActive(_id);
				this->callEvent("onClick");
				this->_useTitle = false;
				this->_drawCursor = true;
				_active = true;
			}

			if ((!_wasHover) && (data->mMoved)) {
				_wasHover = true;
				this->callEvent("onHover");
			}

		} else {
			if (data->clicked) {
				_active = false;
			}

			if ((_wasHover) && (data->mMoved)) {
				this->callEvent("onLeft");
				_wasHover = false;
			}
		}

		if ((data->active == _id) && (!_wasActive)) {
			_wasActive = true;
			data->textMode = true;
		} else if ((data->active != _id) && (_wasActive)) {
			_wasActive = false;
			if (_textInput == "") {
				_useTitle = true;
			}

			_drawCursor = false;
			data->textMode = false;
		}

		if ((data->active == _id) && (data->textMode == true)) {
			if ((data->textEntered == true)) {
				if (data->backSpace) {
					if (!_textInput.empty()) {
						_textInput.pop_back();
					}
				} else {
					_textInput += data->lastText;
				}
				text.setString(_textInput);
				text.setFont(*_font);
				text.setCharacterSize(_h/2);
				text.setPosition(_x+1, (_y+_h/2) - (text.getLocalBounds().height/2));
				if (text.getLocalBounds().width > _w) {
					text.setPosition(_x+1 - (text.getLocalBounds().width - _w), (_y+_h/2) - (text.getLocalBounds().height/2));
					cursor.setPosition((_x+ (text.getLocalBounds().width-_w)), _y+1);
				} else {
					text.setPosition(_x+1, (_y+_h/2) - (text.getLocalBounds().height/2));
					cursor.setPosition((_x+text.getLocalBounds().width), _y+1);
				}
				cursor.setPosition((_x+text.getLocalBounds().width), _y+1);
				_drawnCursor = true;
			}
		}
		return _active;
	}

	void render(sf::RenderTexture * renderOut) {
		sf::Sprite texSprite;
		texSprite.setTexture(renderOut->getTexture());
		_textView.setViewport(sf::FloatRect((double)_x / (double)texSprite.getTextureRect().width, (double)_y / (double)texSprite.getTextureRect().height, _w / texSprite.getTextureRect().width, _h / texSprite.getTextureRect().height));
		if (_useShape) {
			renderOut->draw(wBox);
		}

		//text output
		renderOut->setView(_textView);

		if (_useTitle) {
			renderOut->draw(title);
		}

		renderOut->draw(text);

		if (_drawCursor) {
			auto newTime = std::chrono::high_resolution_clock::now();
			auto elapsedTime(newTime-_currTime);
			//std::cout << "running! " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(elapsedTime).count() << " " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(blinkDur).count() << "\n";
			if (std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(elapsedTime).count() > std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(blinkDur).count()) {
				_currTime = newTime;
				_drawnCursor = !_drawnCursor;
			}

			if (_drawnCursor) {
				renderOut->draw(cursor);
			}
		}
	}

	void addTitle(std::string myTitle, sf::Color color) {
		_useTitle = true;
		title.setFont(*_font);
		title.setString(myTitle);
		title.setCharacterSize(_h/2);
		title.setFillColor(color);
		title.setPosition(_x+1, (_y+_h/2) - (title.getLocalBounds().height/2));
	}

	sf::Text title;
	sf::Text text;
	sf::RectangleShape wBox;
	sf::RectangleShape cursor;
	std::chrono::milliseconds blinkDur;
private:

	int _id;
	bool _wasActive = false;
	bool _wasHover = false;

	int _x;
	int _y;
	double _w;
	double _h;

	sf::Font * _font;

	bool _useTitle = false;

	bool _useShape = true;

	bool _drawCursor = false;
	std::chrono::time_point<std::chrono::high_resolution_clock> _currTime;
	bool _drawnCursor = true;

	sf::View _textView;

	std::string _textInput = "";

	bool _active = false;
};

#endif
