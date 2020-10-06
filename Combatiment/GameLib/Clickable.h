#ifndef INCLUDE_CLICKABLE
#define INCLUDE_CLICKABLE

#include <SFML/Graphics.hpp>
#include "Hitbox.h"

/** 
 * Click types for Clickable::clickTypes
 */
enum class ClickType
{
	ONDOWN = 0,
	ONRELEASE = 1,
	OVER = 2
};

/**
 * MouseButtons for Clickable::mouseButtons
 */
enum class MouseButton
{
	LEFT = sf::Mouse::Left,
	MIDDLE = sf::Mouse::Middle,
	RIGHT = sf::Mouse::Right
};

/** 
 * A pure virtual class of a clickable object.
 */
class Clickable : public Hitboxed
{
protected:

	/** 
	 * \protected
	 * A pointer to the main window.
	 */
	sf::RenderWindow* window;

	/** 
	 * \protected
	 * A pointer to the event of the main window.
	 */
	sf::Event* ev;

	/** 
	 * \protected
	 * A vector containing the click types for which to react to.
	 */
	std::vector<ClickType> clickTypes = std::vector<ClickType>(1, ClickType::ONRELEASE);

	/** 
	 * \protected
	 * A vector containing the mouse buttons for which to react to.
	 */
	std::vector<MouseButton> mouseButtons = std::vector<MouseButton>(1, MouseButton::LEFT);
	

public:

	/**
	 * \public
	 * \return true If the clickable is clicked.
	 * \return false Otherwise.
	 * \note You should not call this method yourself.
	 */
	bool isClicked();

	/** 
	 * \public
	 * Method to call when the clickable is clicked.
	 */
	virtual void onClick() = 0;

	/**
	 * \public
	 * Used in Game::addClickable() to initialize the protected window attribute.
	 * \param window A pointer to the main window.
	 * \note You should not call this method yourself.
	 */
	void setWindow(sf::RenderWindow* window);

	/**
	 * \public
	 * Used in Game::addClickable() to initialize the protected event attribute.
	 * \param ev A pointer to the event of the main window.
	 * \note You should not call this method yourself.
	 */
	void setEvent(sf::Event* ev);

	/**
	 * \public
	 * \return A reference to the vector Clickable::clickTypes.
	 */
	std::vector<ClickType>& getClickTypes();

	/**
	 * \public
	 * \return A reference to the vector Clickable::mouseButtons.
	 */
	std::vector<MouseButton>& getMouseButtons();
};

#endif // !INCLUDE_CLICKABLE