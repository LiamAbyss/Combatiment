#pragma once
#include "GameLib/Scene.h"

class SplashScreen : public Scene
{
	// Hérité via Scene
	virtual void initialize() override;
	virtual void update(sf::Time dt, sf::Event& ev) override;
	virtual void render() override;

	// Hérité via Scene
	virtual void update(sf::Time dt) override;
};

