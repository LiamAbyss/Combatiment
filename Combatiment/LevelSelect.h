#pragma once
#include "GameLib/Scene.h"

class Platform : public Hitboxed, public sf::RectangleShape
{

};

class Character : public Hitboxed, public sf::Sprite
{
public:
	sf::Vector2f velocity;
};

class LevelSelect : public Scene
{
private:
	GTexture groundText;
	GTexture playerText;
	GJson groundHitboxes;
	GJson playerHitboxes;
	Platform ground;
	sf::RectangleShape background;
	Character player;

public:
	// Hérité via Scene
	virtual void initialize() override;
	virtual void update(sf::Time dt, sf::Event& ev) override;
	virtual void update(sf::Time dt) override;
	virtual void render() override;
};

