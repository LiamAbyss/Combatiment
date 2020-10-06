#pragma once
#include "GameLib/Scene.h"
#include <iostream>
#include <string>

class Options : public Scene
{
private:
	sf::Sprite background;
	sf::Sprite menuFrame;
	sf::Sprite title;
	sf::Sprite selector;
	int selected = 0;
	std::vector<std::pair<std::string, sf::Text>> menuItems;
	GFont font;
	GMusic ambient;
	bool initialized = false;
	int volume = 100;

public:
	// Hérité via Scene
	virtual void initialize() override;
	virtual void update(sf::Time dt, sf::Event& ev) override;
	virtual void render() override;
};

