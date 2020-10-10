#include "Menu.h"

void Menu::initialize()
{
	if (initialized) return;

	if (!loaded)
	{
		//Set a framerate limit for the progress bar and menu animation
		//window->setFramerateLimit(60);

		//LOADING BAR
		sf::RectangleShape loadingShape;
		loadingShape.setOutlineThickness(5);
		loadingShape.setOutlineColor(sf::Color::White);
		loadingShape.setFillColor(sf::Color::Transparent);
		loadingShape.setSize(sf::Vector2f(window->getSize().x * 0.6, window->getSize().y * 0.05));
		loadingShape.setPosition(sf::Vector2f((window->getSize().x - loadingShape.getSize().x) / 2, (window->getSize().y - loadingShape.getSize().y) / 2));
		sf::RectangleShape loadProgress;
		loadProgress.setFillColor(sf::Color::White);
		loadProgress.setSize(sf::Vector2f(loadingShape.getSize().x - 2 * loadingShape.getOutlineThickness(), loadingShape.getSize().y - 2 * loadingShape.getOutlineThickness()));
		loadProgress.setPosition(sf::Vector2f(loadingShape.getPosition().x + loadingShape.getOutlineThickness(), loadingShape.getPosition().y + loadingShape.getOutlineThickness()));
		loadProgress.setScale(0, 1);
		sf::Text loadingText;
		loadingText.setFillColor(sf::Color::White);
		loadingText.setCharacterSize(window->getSize().y * 0.025);
		loadingText.setPosition(loadingShape.getPosition().x, loadingShape.getPosition().y - loadingText.getCharacterSize() / 0.4);

		float progress = 0;
		float progressStep = 1. / 8.;
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
		resources->load("menu/selector", "../assets/menu/selector.png");
		renderProgress("../assets/menu/selector.png", window);
		resources->load("game/ground", "../assets/levels/ground.png");
		renderProgress("../assets/levels/ground.png", window);
		resources->load("game/groundHitboxes", "../assets/levels/groundHitboxes.json");
		renderProgress("../assets/levels/groundHitboxes.json", window);
		resources->load("building/walk", "../assets/building/walk.png");
		renderProgress("../assets/building/walk.png", window);
		resources->load("building/hitboxes", "../assets/building/hitboxes.json");
		renderProgress("../assets/building/hitboxes.json", window);

		//MUSICS and SOUNDS
		ambient = boost::get<GMusic>(resources->get("menu/ambient"));
		ambient->setLoop(true);
		ambient->play();
	}

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
	menuFrame.setScale(
		(float)game->getVideoMode().width / (float)frameText.getSize().x * 0.39,
		(float)game->getVideoMode().height / (float)frameText.getSize().y * 0.47
	);
	menuFrame.setPosition(sf::Vector2f(
		game->getVideoMode().width / 2 - menuFrame.getScale().x * frameText.getSize().x / 2,
		game->getVideoMode().height / 2 - menuFrame.getScale().y * frameText.getSize().y / 2 + 23.15 * (float)window->getSize().y / (float)frameText.getSize().y
	));
	menuFrame.setColor(sf::Color(255, 255, 255, 0));

	//Title
	sf::Texture& titleText = *boost::get<GTexture>(resources->get("menu/title"));
	title.setTexture(titleText);

	//MENU ITEMS
	if (menuItems.empty())
	{
		menuItems.push_back(std::make_pair("Start", sf::Text()));
		menuItems.push_back(std::make_pair("Options", sf::Text()));
		menuItems.push_back(std::make_pair("Exit", sf::Text()));
	}

	int iItem = 0;
	for(auto& f : menuItems)
	{
		iItem++;
		f.second.setFont(*font);
		f.second.setString(f.first);
		f.second.setCharacterSize(window->getSize().y * 0.035);
		f.second.setFillColor(sf::Color::White); 
		sf::Vector2f itemPos(
			menuFrame.getPosition().x + (menuFrame.getScale().x * frameText.getSize().x - f.second.getGlobalBounds().width) / 2,
			menuFrame.getPosition().y + f.second.getGlobalBounds().height * 2.5 * iItem//+ (menuFrame.getScale().y * frameText.getSize().y - menuItems.begin()->second.getGlobalBounds().height) / menuItems.size()
		);
		f.second.setPosition(itemPos);
	}

	//MENU SELECTOR
	GTexture selectText = boost::get<GTexture>(resources->get("menu/selector"));
	selector.setTexture(*selectText);
	selector.setScale(
		menuFrame.getScale().x * frameText.getSize().x / selectText->getSize().x * 0.8, 
		(float)selectText->getSize().y * (float)window->getSize().y * 0.00002258);
	selector.setPosition(sf::Vector2f(
		menuFrame.getPosition().x + (menuFrame.getScale().x * frameText.getSize().x - selector.getScale().x * selectText->getSize().x) / 2, 
		menuFrame.getPosition().y + menuItems.begin()->second.getGlobalBounds().height * 2.5 * (selected + 1)
	));

	//Prepare menu animation
	sf::Vector2f finalScale(
		(float)game->getVideoMode().width / (float)titleText.getSize().x * 0.52,
		(float)game->getVideoMode().height / (float)titleText.getSize().y * 0.18
	);

	//std::cout << (float)game->getVideoMode().width / (float)titleText.getSize().x * 0.93 << std::endl;
	//std::cout << (float)game->getVideoMode().height / (float)titleText.getSize().y * 0.3218 << std::endl;
	
	sf::Vector2f initScale(
		(float)game->getVideoMode().width / (float)titleText.getSize().x * 0.93,
		(float)game->getVideoMode().height / (float)titleText.getSize().y * 0.3218
	);
	sf::Vector2f initPos(
		game->getVideoMode().width / 2 - initScale.x * titleText.getSize().x / 2,
		game->getVideoMode().height / 2 - initScale.y * titleText.getSize().y / 2
	);
	sf::Vector2f finalPos(
		game->getVideoMode().width / 2 - finalScale.x * titleText.getSize().x / 2,
		0.05 * game->getVideoMode().height
	);

	if (!loaded)
	{
		//Show menu animation
		for (float i = 0; i < 1; i += 0.9 / game->getFramerate())
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
		for (float i = 0; i < 1; i += 1.2 / game->getFramerate())
		{
			title.setScale(initScale - (initScale - finalScale) * i);
			title.setPosition(initPos.x + (finalPos.x - initPos.x) * i, initPos.y - (initPos.y - finalPos.y) * i);
			background.setColor(sf::Color(255, 255, 255, 255 * i));
			menuFrame.setColor(sf::Color(255, 255, 255, 255 * i));
			window->clear();
			window->draw(background);
			window->draw(menuFrame);
			for (auto& f : menuItems)
				window->draw(f.second);
			window->draw(selector);
			window->draw(title);
			window->display();
		}

		//Remove framerate limit (Game::update() is taking care of it)
		//window->setFramerateLimit(0);
		loaded = true;
	}
	else
	{
		title.setScale(initScale - (initScale - finalScale));
		title.setPosition(initPos.x + (finalPos.x - initPos.x), initPos.y - (initPos.y - finalPos.y));
		background.setColor(sf::Color(255, 255, 255, 255));
		menuFrame.setColor(sf::Color(255, 255, 255, 255));
	}
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
		else if(ev.key.code == sf::Keyboard::Down)
		{
			sf::Texture& frameText = *boost::get<GTexture>(resources->get("menu/frame"));
			GTexture selectText = boost::get<GTexture>(resources->get("menu/selector"));
			if (++selected >= menuItems.size())
				selected = 0;
			selector.setPosition(sf::Vector2f(
				menuFrame.getPosition().x + (menuFrame.getScale().x * frameText.getSize().x - selector.getScale().x * selectText->getSize().x) / 2,
				menuFrame.getPosition().y + menuItems.begin()->second.getGlobalBounds().height * 2.5 * (selected + 1)
			));
		}
		else if (ev.key.code == sf::Keyboard::Up)
		{
			sf::Texture& frameText = *boost::get<GTexture>(resources->get("menu/frame"));
			GTexture selectText = boost::get<GTexture>(resources->get("menu/selector"));
			if (--selected < 0)
				selected = menuItems.size() - 1;
			selector.setPosition(sf::Vector2f(
				menuFrame.getPosition().x + (menuFrame.getScale().x * frameText.getSize().x - selector.getScale().x * selectText->getSize().x) / 2,
				menuFrame.getPosition().y + menuItems.begin()->second.getGlobalBounds().height * 2.5 * (selected + 1)
			));
		}
		else if(ev.key.code == sf::Keyboard::Return)
		{
			switch (selected)
			{
			case 0:
				game->setCurrentScene("levelSelect");
				break;
			case 1:
				game->setCurrentScene("options");
				break;
			case 2:
				window->close();
				break;
			default:
				break;
			}
		}
	}
}

void Menu::render()
{
	window->draw(background);
	window->draw(menuFrame);
	for (auto& f : menuItems)
		window->draw(f.second);
	window->draw(selector);
	window->draw(title);
}

void Menu::setInitialized(bool init)
{
	initialized = init;
}

void Menu::update(sf::Time dt)
{
}
