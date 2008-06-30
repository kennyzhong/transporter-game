#include "transporter.h"

void Game::run()
{
	input.run();
	visual.run(&scene.visual);
}

//————————————————————————————————————————————————————————————————————————————————————————

bit Game::init(HINSTANCE instance)
{
	this->appInstance = instance;
	if(visual.init(this))
	{
		input.init(this);
		physics.init(this);
		scene.init(this);
		return true;
	}
	return false;
}

//————————————————————————————————————————————————————————————————————————————————————————

Game::~Game()
{
	scene.cleanUp();
	input.stop();
	visual.stop();
}

//————————————————————————————————————————————————————————————————————————————————————————

HINSTANCE Game::getAppInstance()
{
	return appInstance;
}