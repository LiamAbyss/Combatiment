#include "LevelSelect.h"

void LevelSelect::initialize()
{
	//Background
	sf::Texture& backgroundText = *boost::get<GTexture>(resources->get("menu/background"));
	backgroundText.setRepeated(true);
	background.setTexture(&backgroundText);
	background.setTextureRect(sf::IntRect(0, 0, backgroundText.getSize().x * 2, backgroundText.getSize().y));
	background.setSize(sf::Vector2f(backgroundText.getSize().x * 2, backgroundText.getSize().y));
	background.setScale(
		(float)game->getVideoMode().width / (float)backgroundText.getSize().x,
		(float)game->getVideoMode().height / (float)backgroundText.getSize().y
	);

	//Ground platform
	groundText = boost::get<GTexture>(resources->get("game/ground"));
	groundText->setRepeated(true);
	groundHitboxes = boost::get<GJson>(resources->get("game/groundHitboxes"));

	ground.setTexture(&*groundText);
	ground.hitboxes = Hitbox::getHitboxes(*groundHitboxes, "ground");
	ground.setActiveHitbox("main");

	sf::Vector2f groundPosOrigin = sf::Vector2f(0, game->getVideoMode().height - 0.7 * groundText->getSize().y);
	ground.move(groundPosOrigin);
	ground.moveHitboxes(groundPosOrigin);
	ground.setTextureRect(sf::IntRect(0, 0, groundText->getSize().x * 2, groundText->getSize().y));
	ground.setSize(sf::Vector2f(groundText->getSize().x * 2, groundText->getSize().y)); 
	ground.setScale((float)game->getVideoMode().width / (float)groundText->getSize().x,	1);
	ground.setScaleHitboxes(sf::Vector2f((float)game->getVideoMode().width / (float)groundText->getSize().x * 2, 1));

	//Player
	playerText = boost::get<GTexture>(resources->get("building/walk"));
	playerHitboxes = boost::get<GJson>(resources->get("building/hitboxes"));

	player.setTexture(*playerText);
	player.setTextureRect(sf::IntRect(0, 0, playerText->getSize().x / 6, playerText->getSize().y));
	player.hitboxes = Hitbox::getHitboxes(*playerHitboxes, "player");
	player.setActiveHitbox("still");
	player.setPosHitboxes(sf::Vector2f(
		0,
		ground.hitboxes[ground.activeHitbox][0].getTop() - player.getScale().y * playerText->getSize().y
	));
	player.setPosition(sf::Vector2f(
		0,
		ground.hitboxes[ground.activeHitbox][0].getTop() - player.getScale().y * playerText->getSize().y
	));
}

void LevelSelect::update(sf::Time dt, sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed)
	{
		//On alt+F4
		if (ev.key.code == sf::Keyboard::F4 && ev.key.alt)
		{
			window->close();
		}
	}
}

void LevelSelect::update(sf::Time dt)
{
	//Camera
	window->setView(sf::View(sf::Vector2f(player.getPosition().x, window->getSize().y / 2), (sf::Vector2f)window->getSize()));

	//Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && Hitbox::doesHit(&ground, &player))
	{
		player.velocity.y = -6;
	}
	
	//Right-Left Moves
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Hitbox::doesHit(&ground, &player))
	{
		player.velocity.x = 300 * dt.asSeconds();

		//Unflip
		player.flipHitboxes(&player, false);
		player.setTextureRect(sf::IntRect(0, 0, playerText->getSize().x / 6, playerText->getSize().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && Hitbox::doesHit(&ground, &player))
	{
		player.velocity.x = -300 * dt.asSeconds();

		//Flip
		player.flipHitboxes(&player, true);
		player.setTextureRect(sf::IntRect(playerText->getSize().x / 6, 0, -(playerText->getSize().x / 6.), playerText->getSize().y));
	}
	else if(Hitbox::doesHit(&ground, &player))
		player.velocity.x = 0;

	//Gravity (=10px/s²) + Collisions
	player.velocity.y += 10 * dt.asSeconds();
	player.moveHitboxes(player.velocity);
	player.move(player.velocity);
	if (Hitbox::doesHit(&ground, &player))
	{
		player.moveHitboxes(-player.velocity);
		player.velocity.y = -player.velocity.y * 0;
		player.setPosHitboxes(sf::Vector2f(
			player.getPosition().x,
			ground.hitboxes[ground.activeHitbox][0].getTop() - player.getScale().y * playerText->getSize().y
		));
		player.setPosition(sf::Vector2f(
			player.getPosition().x,
			ground.hitboxes[ground.activeHitbox][0].getTop() - player.getScale().y * playerText->getSize().y
		));
	}
}

void LevelSelect::render()
{
	window->draw(background);
	window->draw(ground);
	window->draw(player);
	ground.renderHitboxes(*window);
	player.renderHitboxes(*window);
}
