#include "Options.h"

void Options::initialize()
{
	if (initialized) return;

	for (int i = 0; i < videoModes.size(); i++)
		if (videoModes[i] == game->getVideoMode())
			selectedVideoMode = i;

	ambient = boost::get<GMusic>(resources->get("menu/ambient"));

	//TEXTURES
	//Background
	sf::Texture& backgroundText = *boost::get<GTexture>(resources->get("menu/background"));
	background.setTexture(backgroundText);
	sf::Vector2f initialScaler(
		(float)game->getVideoMode().width / (float)backgroundText.getSize().x,
		(float)game->getVideoMode().height / (float)backgroundText.getSize().y
	);
	background.setScale(initialScaler);
	
	//MenuFrame
	frameText = boost::get<GTexture>(resources->get("menu/frame"));
	menuFrame.setTexture(*frameText);
	menuFrame.setScale(
		(float)game->getVideoMode().width / (float)frameText->getSize().x * 0.39,
		(float)game->getVideoMode().height / (float)frameText->getSize().y * 0.579
	);
	menuFrame.setPosition(sf::Vector2f(
		game->getVideoMode().width / 2 - menuFrame.getScale().x * frameText->getSize().x / 2,
		game->getVideoMode().height / 2 - menuFrame.getScale().y * frameText->getSize().y / 2 + 23.15 * (float)window->getSize().y / (float)frameText->getSize().y
	));

	//Title
	sf::Texture& titleText = *boost::get<GTexture>(resources->get("menu/title"));
	title.setTexture(titleText);
	title.setScale(
		(float)game->getVideoMode().width / (float)titleText.getSize().x * 0.52,
		(float)game->getVideoMode().height / (float)titleText.getSize().y * 0.18
	);
	title.setPosition(sf::Vector2f(
		game->getVideoMode().width / 2 - title.getScale().x * titleText.getSize().x / 2,
		0.05 * game->getVideoMode().height
	));

	//MENU ITEMS
	if (menuItems.empty())
	{
		menuItems.push_back(std::make_pair("Volume", sf::Text()));
		menuItems.push_back(std::make_pair("Resolution", sf::Text()));
		menuItems.push_back(std::make_pair("Fullscreen", sf::Text()));
		menuItems.push_back(std::make_pair("Back", sf::Text()));
	}

	font = boost::get<GFont>(resources->get("font"));
	for (auto& f : menuItems)
	{
		f.second.setFont(*font);
		f.second.setString(f.first);
		f.second.setCharacterSize(window->getSize().y * 0.035);
		f.second.setFillColor(sf::Color::White);
	}
	repositionMenuItems();

	//MENU SELECTOR
	GTexture selectText = boost::get<GTexture>(resources->get("menu/selector"));
	selector.setTexture(*selectText);
	selector.setScale(
		menuFrame.getScale().x * frameText->getSize().x / selectText->getSize().x * 0.9,
		(float)selectText->getSize().y * (float)window->getSize().y * 0.00002258);
	selector.setPosition(sf::Vector2f(
		menuFrame.getPosition().x + (menuFrame.getScale().x * frameText->getSize().x - selector.getScale().x * selectText->getSize().x) / 2,
		menuFrame.getPosition().y + menuItems.begin()->second.getGlobalBounds().height * 2.5 * (selected + 1)
	));
}

void Options::update(sf::Time dt, sf::Event& ev)
{
	for(auto& f : menuItems)
	{
		f.second.setString(f.first);
	}
	if (selected == 0)
		menuItems[selected].second.setString(std::to_string(volume) + "%");
	if (selected == 1)
		menuItems[selected].second.setString(std::to_string(game->getVideoMode().width) + "x" + std::to_string(game->getVideoMode().height));
	if (selected == 2)
		menuItems[selected].second.setString(fullscreen ? "Yes" : "No");

	if (ev.type == sf::Event::KeyPressed)
	{
		//On alt+F4
		if (ev.key.code == sf::Keyboard::F4 && ev.key.alt)
		{
			window->close();
		}
		else if (ev.key.code == sf::Keyboard::Down)
		{
			GTexture selectText = boost::get<GTexture>(resources->get("menu/selector"));
			if (++selected >= menuItems.size())
				selected = 0;
			selector.setPosition(sf::Vector2f(
				menuFrame.getPosition().x + (menuFrame.getScale().x * frameText->getSize().x - selector.getScale().x * selectText->getSize().x) / 2,
				menuFrame.getPosition().y + menuItems.begin()->second.getGlobalBounds().height * 2.5 * (selected + 1)
			));
		}
		else if (ev.key.code == sf::Keyboard::Up)
		{
			GTexture selectText = boost::get<GTexture>(resources->get("menu/selector"));
			if (--selected < 0)
				selected = menuItems.size() - 1;
			selector.setPosition(sf::Vector2f(
				menuFrame.getPosition().x + (menuFrame.getScale().x * frameText->getSize().x - selector.getScale().x * selectText->getSize().x) / 2,
				menuFrame.getPosition().y + menuItems.begin()->second.getGlobalBounds().height * 2.5 * (selected + 1)
			));
		}
		else if (ev.key.code == sf::Keyboard::Left)
		{
			switch (selected)
			{
			case 0:
				volume--;
				if (volume < 0)
					volume = 100;
				menuItems[selected].second.setString(std::to_string(volume) + "%");
				ambient->setVolume(volume);
				break;
			case 1:
				selectedVideoMode--;
				if (selectedVideoMode < 0)
					selectedVideoMode = videoModes.size() - 1;
				checkVideoMode();
				break;
			case 2:
				fullscreen = !fullscreen;
				checkVideoMode();
				break;
			default:
				break;
			}
		}
		else if (ev.key.code == sf::Keyboard::Right)
		{
			switch (selected)
			{
			case 0:
				volume++;
				if (volume > 100)
					volume = 0;
				menuItems[selected].second.setString(std::to_string(volume) + "%");
				ambient->setVolume(volume);
				break;
			case 1:
				selectedVideoMode++;
				if (selectedVideoMode >= videoModes.size())
					selectedVideoMode = 0;
				checkVideoMode();
				break;
			case 2:
				fullscreen = !fullscreen;
				checkVideoMode();
			default:
				break;
			}
		}
		else if (ev.key.code == sf::Keyboard::Return)
		{
			switch (selected)
			{
			case 3:
				game->setCurrentScene("menu");
				break;
			default:
				break;
			}
		}
	}
	repositionMenuItems();
}

void Options::render()
{
	window->draw(background);
	window->draw(menuFrame);
	for (auto& f : menuItems)
		window->draw(f.second);
	window->draw(selector);
	window->draw(title);
}

void Options::repositionMenuItems()
{
	int iItem = 0;
	for (auto& f : menuItems)
	{
		iItem++;
		sf::Vector2f itemPos(
			menuFrame.getPosition().x + (menuFrame.getScale().x * frameText->getSize().x - f.second.getGlobalBounds().width) / 2,
			menuFrame.getPosition().y + f.second.getGlobalBounds().height * 2.5 * iItem
		);
		f.second.setPosition(itemPos);
	}
}

void Options::setInitialized(bool init)
{
	initialized = init;
}

void Options::checkVideoMode()
{
	if (fullscreen)
	{
		if (std::find(videoModes.begin(), videoModes.begin() + 3, videoModes[selectedVideoMode]) == videoModes.begin() + 3)
		{
			selectedVideoMode = 2;
		}
	}
	game->setVideoMode(videoModes[selectedVideoMode], fullscreen ? sf::Style::Fullscreen : 7U);
	for (auto& scene : game->getScenes())
	{
		scene.second->setInitialized(false);
	}
	game->setCurrentScene("options");
}

void Options::update(sf::Time dt)
{
}
