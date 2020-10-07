#include "Scene.h"

void Scene::setGame(Game* game)
{
	this->game = game;
	this->resources = &(game->getResources());
	this->window = &(game->getWindow());
}

void Scene::setInitialized(bool init)
{
	initialized = init;
}
