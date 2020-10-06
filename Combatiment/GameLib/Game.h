#ifndef INCLUDE_GAME
#define INCLUDE_GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include "Clickable.h"
#include "ResourceManager.h"

class Scene;
#include "Scene.h"

class Game
{
private:
	//SCENES
	std::map<std::string, std::shared_ptr<Scene>> scenes;

	std::vector<std::shared_ptr<Clickable>> clickables;

	ResourceManager resources;

	sf::Clock gameClock;
	sf::Clock framerateClock;
	sf::Clock updateClock;

	std::string windowTitle;
	sf::RenderWindow window;
	sf::VideoMode windowMode;
	unsigned short framerate = 60;
	std::string currentScene;

	sf::Event ev;

public:
	Game(std::string title, sf::VideoMode mode, sf::Uint32 style = 7U);
	void addScene(std::string label, Scene* scene);
	std::map<std::string, std::shared_ptr<Scene>>& getScenes();
	void setCurrentScene(std::string label);

	void addClickable(Clickable* clickable);
	std::vector<std::shared_ptr<Clickable>>& getClickables();

	ResourceManager& getResources();
	sf::RenderWindow& getWindow();
	sf::VideoMode& getVideoMode();
	unsigned short getFramerate();
	void setFramerate(unsigned short rate);
	void launch();
};

#endif // !INCLUDE_GAME

