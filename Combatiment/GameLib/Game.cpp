#include "Game.h"

Game::Game(std::string title, sf::VideoMode mode, sf::Uint32 style)
{
	window.create(mode, title, style);
	windowMode = mode;
	windowTitle = title;
}

void Game::addScene(std::string label, Scene* scene)
{
	scenes.emplace(label, std::shared_ptr<Scene>(scene));
	scenes[label]->setGame(this);
}

std::map<std::string, std::shared_ptr<Scene>>& Game::getScenes()
{
	return scenes;
}

void Game::setCurrentScene(std::string label)
{
	//TODO : Clear local resources
	currentScene = label;
	clickables.resize(0);
	scenes[label]->initialize();
}

void Game::addClickable(Clickable* clickable)
{
	clickables.push_back(std::shared_ptr<Clickable>(clickable));
	clickables[clickables.size() - 1]->setWindow(&window);
	clickables[clickables.size() - 1]->setEvent(&ev);
}

std::vector<std::shared_ptr<Clickable>>& Game::getClickables()
{
	return clickables;
}

ResourceManager& Game::getResources()
{
	return resources;
}

sf::RenderWindow& Game::getWindow()
{
	return window;
}

sf::VideoMode& Game::getVideoMode()
{
	return windowMode;
}

unsigned short Game::getFramerate()
{
	return framerate;
}

void Game::setFramerate(unsigned short rate)
{
	framerate = rate;
}

void Game::launch()
{
	if (scenes.empty())
	{
		std::cout << "Unable to launch the game : No scene could be found." << std::endl;
		return;
	}
	gameClock.restart();
	framerateClock.restart();
	updateClock.restart();
	while (window.isOpen())
	{
		sf::Time updateTime = updateClock.restart();
		while (window.pollEvent(ev))
		{
			for(auto& c : clickables)
			{
				if (c->isClicked())
					c->onClick();
			}
			scenes[currentScene]->update(updateTime, ev);
			if (ev.type == sf::Event::Closed)
				window.close();
		}

		if (framerateClock.getElapsedTime().asMilliseconds() >= 1000 / framerate)
		{
			window.clear();
			scenes[currentScene]->render();
			window.display();
			framerateClock.restart();
		}
	}
	std::cout << "Game time : " << gameClock.restart().asSeconds() << "s" << std::endl;
}
