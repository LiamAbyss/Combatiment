#include <iostream>
#include <string>
#include "GameLib/Game.h"

#include "Menu.h"
#include "Options.h"

int main()
{
	Game combatiment("Combatiment", sf::VideoMode::getFullscreenModes()[1], sf::Style::Fullscreen);
	combatiment.addScene("menu", new Menu());
	combatiment.addScene("options", new Options());
	combatiment.setCurrentScene("menu");

	combatiment.launch();
	return 0;
}