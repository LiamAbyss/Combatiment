#ifndef INCLUDE_SCENE
#define INCLUDE_SCENE

class Game;

#include "Game.h"


class Scene
{
protected:
	Game* game;
	ResourceManager* resources;
	sf::RenderWindow* window;
	std::map<std::string, std::shared_ptr<Scene>>* scenes;

public:
	void setGame(Game* game);
	virtual void initialize() = 0;
	virtual void update(sf::Time dt, sf::Event& ev) = 0;
	virtual void render() = 0;
};

#endif // !INCLUDE_SCENE

