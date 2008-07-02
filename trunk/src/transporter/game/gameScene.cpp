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

	visualWorld.init(game);
	physicsWorld.init(game);

	createEntities();
	return true;
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
	physicsWorld.cleanUp();
	visualWorld.cleanUp();
}

//————————————————————————————————————————————————————————————————————————————————————————

void GameScene::createEntities()
{
	surface = new Surface(game);
	surface->init("surface");

	car     = new CarEntity(surface);
	car->init("car");
}