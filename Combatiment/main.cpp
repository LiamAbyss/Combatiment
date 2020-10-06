#include <iostream>
#include <string>
#include "GameLib/Game.h"

#include "Menu.h"

int main()
{
	Game combatiment("Combatiment", sf::VideoMode::getFullscreenModes()[1], sf::Style::Fullscreen);
	combatiment.addScene("menu", new Menu());
	combatiment.setCurrentScene("menu");

	combatiment.launch();
	return 0;
}