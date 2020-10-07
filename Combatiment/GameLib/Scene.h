#ifndef INCLUDE_SCENE
#define INCLUDE_SCENE

class Game;

#include "Game.h"

/** 
 * A pure virtual class of a game scene.
 */
class Scene
{
protected:

	/** 
	 * \protected
	 * A pointer to the game.
	 * \see Game
	 */
	Game* game;

	/** 
	 * \protected
	 * A pointer to the resource manager.
	 * \see ResourceManager
	 */
	ResourceManager* resources;

	/** 
	 * \protected
	 * A pointer to the main window.
	 */
	sf::RenderWindow* window;

	bool initialized = false;

public:

	/**
	 * \public
	 * Used in Game::addScene() to initialize the protected attributes.
	 * \param game A pointer to the game.
	 * \see Game
	 * \note You should not call this method yourself.
	 */
	void setGame(Game* game);

	void setInitialized(bool init);

	/** 
	 * \public
	 * Initializer to load resources, show loading animations etc...
	 */
	virtual void initialize() = 0;

	/**
	 * \public
	 * Game loop in which all the processing is done.
	 * \param dt The time passed since last update.
	 * \param ev The SFML event for the main window.
	 */
	virtual void update(sf::Time dt, sf::Event& ev) = 0;

	/** 
	 * \public
	 * Game loop in which all the rendering is done.
	 */
	virtual void render() = 0;
};

#endif // !INCLUDE_SCENE

