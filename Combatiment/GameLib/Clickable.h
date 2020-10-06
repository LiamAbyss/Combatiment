#ifndef INCLUDE_CLICKABLE
#define INCLUDE_CLICKABLE

#include <SFML/Graphics.hpp>
#include "Hitbox.h"

enum class ClickType
{
	ONDOWN = 0,
	ONRELEASE = 1
};

enum class MouseButton
{
	LEFT = sf::Mouse::Left,
	MIDDLE = sf::Mouse::Middle,
	RIGHT = sf::Mouse::Right
};

class Clickable : public Hitboxed
{
protected:
	sf::RenderWindow* window;
	sf::Event* ev;
	std::vector<ClickType> clickTypes = std::vector<ClickType>(1, ClickType::ONRELEASE);
	std::vector<MouseButton> mouseButtons = std::vector<MouseButton>(1, MouseButton::LEFT);
	

public:
	bool isClicked();
	virtual void onClick() = 0;
	void setWindow(sf::RenderWindow* window);
	void setEvent(sf::Event* ev);
	std::vector<ClickType>& getClickTypes();
	std::vector<MouseButton>& getMouseButtons();
};

#endif // !INCLUDE_CLICKABLE