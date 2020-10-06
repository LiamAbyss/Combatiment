#include "Clickable.h"

bool Clickable::isClicked()
{
	bool ok = false;
	if (ev->type == sf::Event::MouseButtonReleased)
	{
		if (std::find(clickTypes.begin(), clickTypes.end(), ClickType::ONRELEASE) != clickTypes.end())
		{
				if (std::find(mouseButtons.begin(), mouseButtons.end(), MouseButton::LEFT) != mouseButtons.end())
				{
					if (ev->mouseButton.button == sf::Mouse::Left)
						ok = true;
				}
				if (std::find(mouseButtons.begin(), mouseButtons.end(), MouseButton::RIGHT) != mouseButtons.end())
				{
					if (ev->mouseButton.button == sf::Mouse::Right)
						ok = true;
				}
				if (std::find(mouseButtons.begin(), mouseButtons.end(), MouseButton::MIDDLE) != mouseButtons.end())
				{
					if (ev->mouseButton.button == sf::Mouse::Middle)
						ok = true;
				}
		}
	}
	if (ev->type == sf::Event::MouseButtonPressed)
	{
		if (std::find(clickTypes.begin(), clickTypes.end(), ClickType::ONDOWN) != clickTypes.end())
		{
				if (std::find(mouseButtons.begin(), mouseButtons.end(), MouseButton::LEFT) != mouseButtons.end())
				{
					if (ev->mouseButton.button == sf::Mouse::Left)
						ok = true;
				}
				if (std::find(mouseButtons.begin(), mouseButtons.end(), MouseButton::RIGHT) != mouseButtons.end())
				{
					if (ev->mouseButton.button == sf::Mouse::Right)
						ok = true;
				}
				if (std::find(mouseButtons.begin(), mouseButtons.end(), MouseButton::MIDDLE) != mouseButtons.end())
				{
					if (ev->mouseButton.button == sf::Mouse::Middle)
						ok = true;
				}
		}
	}
	if (!ok) return false;
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	class Tmp : public Hitboxed {};
	Tmp tmp;
	tmp.hitboxes.emplace("tmp", std::vector<Hitbox>());
	tmp.hitboxes["tmp"].push_back(Hitbox());
	tmp.setActiveHitbox("tmp");
	Hitbox& tmpHitbox = tmp.hitboxes["tmp"][0];
	tmpHitbox.setPos(sf::Vector2f(mousePos.x - 1, mousePos.y - 1));
	tmpHitbox.setSize(sf::Vector2f(2, 2));
	tmpHitbox.setType("hurtbox");

	return Hitbox::doesHit(&tmp, this);
}

void Clickable::setWindow(sf::RenderWindow* window)
{
	this->window = window;
}

void Clickable::setEvent(sf::Event* ev)
{
	this->ev = ev;
}

std::vector<ClickType>& Clickable::getClickTypes()
{
	return clickTypes;
}

std::vector<MouseButton>& Clickable::getMouseButtons()
{
	return mouseButtons;
}
