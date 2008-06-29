#include "transporter.h"

GameScene::GameScene()
{
	game = NULL;
	surface = NULL;
	car = NULL;
}

//————————————————————————————————————————————————————————————————————————————————————————

GameScene::~GameScene()
{
	cleanUp();
}

//————————————————————————————————————————————————————————————————————————————————————————

bit GameScene::init( Game* game )
{
	this->game = game;
	visual.init(game);
	surface = new Surface(&game->visual);
	surface->init("surface");
	car     = new CarEntity(surface);
	car->init("car");
	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

void GameScene::update()
{
	visual.update();
}

//————————————————————————————————————————————————————————————————————————————————————————

void GameScene::cleanUp()
{
	if(car)
	{
		delete car;
		car = NULL;
	}
	if(surface)
	{
		delete surface;
		surface = NULL;
	}
	visual.cleanUp();
}