#include "Options.h"

void Options::initialize()
{
	if (initialized) return;
	initialized = true;

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
	sf::Texture& frameText = *boost::get<GTexture>(resources->get("menu/frame"));
	menuFrame.setTexture(frameText);
	menuFrame.setScale(sf::Vector2f(1.5, 2.5));
	menuFrame.setPosition(sf::Vector2f(
		game->getVideoMode().width / 2 - menuFrame.getScale().x * frameText.getSize().x / 2,
		game->getVideoMode().height / 2 - menuFrame.getScale().y * frameText.getSize().y / 2 + 0.4 * frameText.getSize().y
	));

	//Title
	sf::Texture& titleText = *boost::get<GTexture>(resources->get("menu/title"));
	title.setTexture(titleText);
	title.setScale(sf::Vector2f(0.14, 0.14));
	title.setPosition(sf::Vector2f(
		game->getVideoMode().width / 2 - title.getScale().x * titleText.getSize().x / 2,
		0.05 * game->getVideoMode().height
	));

	//MENU ITEMS
	menuItems.push_back(std::make_pair("Volume : 100%", sf::Text()));
	menuItems.push_back(std::make_pair("Option2", sf::Text()));
	menuItems.push_back(std::make_pair("Option3", sf::Text()));
	menuItems.push_back(std::make_pair("Back", sf::Text()));

	font = boost::get<GFont>(resources->get("font"));
	int iItem = 0;
	for (auto& f : menuItems)
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
	selector.setScale(menuFrame.getScale().x * frameText.getSize().x / selectText->getSize().x * 0.9, selectText->getSize().y / menuItems[0].second.getGlobalBounds().height);
	selector.setPosition(sf::Vector2f(
		menuFrame.getPosition().x + (menuFrame.getScale().x * frameText.getSize().x - selector.getScale().x * selectText->getSize().x) / 2,
		menuFrame.getPosition().y + menuItems.begin()->second.getGlobalBounds().height * 2.5 * (selected + 1)
	));
}

void Options::update(sf::Time dt, sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed)
	{
		//On alt+F4
		if (ev.key.code == sf::Keyboard::F4 && ev.key.alt)
		{
			window->close();
		}
		else if (ev.key.code == sf::Keyboard::Down)
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
		else if (ev.key.code == sf::Keyboard::Left)
		{
			switch (selected)
			{
			case 0:
				volume--;
				if (volume < 0)
					volume = 100;
				menuItems[selected].second.setString("Volume : " + std::to_string(volume) + "%");
				ambient->setVolume(volume);
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
				menuItems[selected].second.setString("Volume : " + std::to_string(volume) + "%");
				ambient->setVolume(volume);
				break;
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
