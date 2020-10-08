#include "SplashScreen.h"

void SplashScreen::initialize()
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	//Load splash image
	sf::Image image;
	image.loadFromFile("../assets/misc/splash.png");
	sf::Texture imgtext;
	imgtext.loadFromImage(image);
	sf::Sprite img;
	img.setTexture(imgtext);

	window->create(sf::VideoMode(image.getSize().x, image.getSize().y), "Combatiment", sf::Style::None);

	//Set the shape and position of the splashscreen
	game->setWShape(image);
	game->getWindow().setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - image.getSize().x) / 2,
		(sf::VideoMode::getDesktopMode().height - image.getSize().y) / 2));

	//Draw splashscreen and wait a bit
	game->getWindow().clear();// sf::Color(0, 0, 0, 255));
	game->getWindow().draw(img);
	game->getWindow().display();
	sf::sleep(sf::seconds(3));

	//Reset to good values
	game->setVideoMode(modes[/*modes.size() - */(int)(modes.size() / 4)/*(modes.size() > 1? 1 : 0)*/]);
	//game->getWindow().setPosition(sf::Vector2i(0, 0));

	game->setCurrentScene("menu");
}

void SplashScreen::update(sf::Time dt, sf::Event& ev)
{
	return;
}

void SplashScreen::render()
{
	return;
}
