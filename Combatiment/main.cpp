#include <iostream>
#include <string>
#include "GameLib/Game.h"

#include "Menu.h"
#include "Options.h"
#include "SplashScreen.h"
#include "LevelSelect.h"

#if defined (SFML_SYSTEM_WINDOWS)
#ifdef NDEBUG
int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
#else
int main()
#endif // _DEBUG
#elif defined (SFML_SYSTEM_LINUX)
int main()
#endif
{
	//Create game basis
	Game combatiment("Combatiment", sf::VideoMode(0, 0), sf::Style::None);
	combatiment.addScene("menu", new Menu());
	combatiment.addScene("options", new Options());
	combatiment.addScene("splash", new SplashScreen());
	combatiment.addScene("levelSelect", new LevelSelect());

	combatiment.setFramerate(120);
	//Set current scene to initialize
	combatiment.setCurrentScene("splash");
	combatiment.launch();
	return 0;
}