#include "Menu.h"

void Menu::initialize()
{
	//Set a framerate limit for the progress bar and menu animation
	window->setFramerateLimit(60);

	//LOADING BAR
	sf::RectangleShape loadingShape;
	loadingShape.setOutlineThickness(5);
	loadingShape.setOutlineColor(sf::Color::White);
	loadingShape.setFillColor(sf::Color::Transparent);
	loadingShape.setSize(sf::Vector2f(window->getSize().x * 0.6, window->getSize().y * 0.05));
	loadingShape.setPosition(sf::Vector2f((window->getSize().x - loadingShape.getSize().x) / 2 , (window->getSize().y - loadingShape.getSize().y) / 2));
	sf::RectangleShape loadProgress;
	loadProgress.setFillColor(sf::Color::White);
	loadProgress.setSize(sf::Vector2f(loadingShape.getSize().x - 2*loadingShape.getOutlineThickness(), loadingShape.getSize().y - 2 * loadingShape.getOutlineThickness()));
	loadProgress.setPosition(sf::Vector2f(loadingShape.getPosition().x + loadingShape.getOutlineThickness(), loadingShape.getPosition().y + loadingShape.getOutlineThickness()));
	loadProgress.setScale(0, 1);
	sf::Text loadingText;
	loadingText.setFillColor(sf::Color::White);
	loadingText.setCharacterSize(window->getSize().y * 0.025);
	loadingText.setPosition(loadingShape.getPosition().x, loadingShape.getPosition().y - loadingText.getCharacterSize() / 0.4);

	float progress = 0;
	float progressStep = 1. / 5.;
	auto renderProgress = [&loadingShape, &loadProgress, &loadingText, &progress, &progressStep](std::string filename, sf::RenderWindow* window)
	{
		progress += progressStep;
		loadProgress.setScale(progress, 1);
		loadingText.setString(std::to_string((int)(progress * 100)) + "% - Loading : " + filename);
		window->clear();
		window->draw(loadingShape);
		window->draw(loadProgress);
		window->draw(loadingText);
		window->display();
	};

	//LOAD RESOURCES
	resources->load("font", "../assets/fonts/backto1982.ttf");
	font = boost::get<GFont>(resources->get("font"));
	loadingText.setFont(*font);
	renderProgress("../assets/fonts/backto1982.ttf", window);
	resources->load("menu/background", "../assets/background/menu.png");
	renderProgress("../assets/background/menu.png", window);
	resources->load("menu/ambient", "../assets/music/mus_mettaton_ex.ogg");
	renderProgress("../assets/music/mus_mettaton_ex.ogg", window);
	resources->load("menu/frame", "../assets/misc/menuframe.png");
	renderProgress("../assets/misc/menuframe.png", window);
	resources->load("menu/title", "../assets/misc/title.png");
	renderProgress("../assets/misc/title.png", window);

	//MUSICS and SOUNDS
	ambient = boost::get<GMusic>(resources->get("menu/ambient"));
	ambient->setLoop(true);
	ambient->play();

	//TEXTURES
	//Background
	sf::Texture& backgroundText = *boost::get<GTexture>(resources->get("menu/background"));
	background.setTexture(backgroundText);
	sf::Vector2f initialScaler(
		(float)game->getVideoMode().width / (float)backgroundText.getSize().x,
		(float)game->getVideoMode().height / (float)backgroundText.getSize().y
	);
	background.setScale(initialScaler);
	background.setColor(sf::Color(255, 255, 255, 0));

	//MenuFrame
	sf::Texture& frameText = *boost::get<GTexture>(resources->get("menu/frame"));
	menuFrame.setTexture(frameText);
	menuFrame.setScale(sf::Vector2f(1, 1));
	menuFrame.setPosition(sf::Vector2f(
		game->getVideoMode().width / 2 - menuFrame.getScale().x * frameText.getSize().x / 2,
		game->getVideoMode().height / 2 - menuFrame.getScale().y * frameText.getSize().y / 2
	));
	menuFrame.setColor(sf::Color(255, 255, 255, 0));

	//Title
	sf::Texture& titleText = *boost::get<GTexture>(resources->get("menu/title"));

	title.setTexture(titleText);

	//MENU ITEMS
	menuItems.emplace("start", sf::Text());
	menuItems["start"].setFont(*font);
	menuItems["start"].setString("Start");
	menuItems["start"].setCharacterSize(window->getSize().y * 0.035);
	menuItems["start"].setFillColor(sf::Color::White);
	menuItems["start"].setPosition(sf::Vector2f(
		menuFrame.getPosition().x + (menuFrame.getScale().x * frameText.getSize().x - menuItems["start"].getGlobalBounds().width) / 2,
		menuFrame.getPosition().y + (menuFrame.getScale().y * frameText.getSize().y - menuItems["start"].getGlobalBounds().height - 25) / 2
	));

	//Prepare menu animation
	sf::Vector2f finalScale(0.14, 0.14);
	sf::Vector2f initScale(0.25, 0.25);
	sf::Vector2f initPos(
		game->getVideoMode().width / 2 - initScale.x * titleText.getSize().x / 2,
		game->getVideoMode().height / 2 - initScale.y * titleText.getSize().y / 2
	);
	sf::Vector2f finalPos(
		game->getVideoMode().width / 2 - finalScale.x * titleText.getSize().x / 2,
		0.05 * game->getVideoMode().height
	);

	//Show menu animation
	for(float i = 0; i < 1; i += 0.015)
	{
		title.setScale(initScale * i);
		title.setPosition(
			game->getVideoMode().width / 2 - title.getScale().x * titleText.getSize().x / 2,
			game->getVideoMode().height / 2 - title.getScale().y * titleText.getSize().y / 2
		);
		title.setColor(sf::Color(255, 255, 255, 255 * i));
		window->clear();
		window->draw(title);
		window->display();
	}
	//sf::sleep(sf::milliseconds(500));
	for(float i = 0; i < 1; i+= 0.02)
	{
		title.setScale(initScale - (initScale - finalScale) * i);
		title.setPosition(initPos.x + (finalPos.x - initPos.x) * i, initPos.y - (initPos.y - finalPos.y) * i);
		background.setColor(sf::Color(255, 255, 255, 255*i));
		menuFrame.setColor(sf::Color(255, 255, 255, 255*i));
		window->clear();
		window->draw(background);
		window->draw(menuFrame);
		for (auto& f : menuItems)
			window->draw(f.second);
		window->draw(title);
		window->display();
	}

	//Remove framerate limit (Game::update() is taking care of it)
	window->setFramerateLimit(0);
}

void Menu::update(sf::Time dt, sf::Event& ev)
{
	if(ev.type == sf::Event::KeyPressed)
	{
		//On alt+F4
		if(ev.key.code == sf::Keyboard::F4 && ev.key.alt)
		{
			window->close();
		}
	}
}

void Menu::render()
{
	window->draw(background);
	window->draw(menuFrame);
	for (auto& f : menuItems)
		window->draw(f.second);
	window->draw(title);
}
