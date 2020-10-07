#include <iostream>
#include <string>
#include "GameLib/Game.h"

#include "Menu.h"
#include "Options.h"

int main()
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	Game combatiment("Combatiment", modes[/*modes.size() - */1/*(modes.size() > 1? 1 : 0)*/]);
	combatiment.addScene("menu", new Menu());
	combatiment.addScene("options", new Options());
	combatiment.setCurrentScene("menu");

	combatiment.launch();
	return 0;
}