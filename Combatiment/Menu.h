#pragma once
#include "GameLib/Scene.h"
#include <iostream>
#include <string>

class Menu : public Scene
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

public:
	// H�rit� via Scene
	virtual void initialize() override;
	virtual void update(sf::Time dt, sf::Event& ev) override;
	virtual void render() override;
};

