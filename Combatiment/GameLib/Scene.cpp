#include "Scene.h"

void Scene::setGame(Game* game)
{
	this->game = game;
	this->resources = &(game->getResources());
	this->window = &(game->getWindow());
	this->scenes = &(game->getScenes());
}
