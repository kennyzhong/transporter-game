#include "transporter.h"

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, int )
{	
	Game transporter;
	if(transporter.init(hInst))
	{
		transporter.run();
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

void Game::run()
{
	input.run();
	visual.run(&scene);
}

//————————————————————————————————————————————————————————————————————————————————————————

bit Game::init(HINSTANCE instance)
{
	this->appInstance = instance;
	if(visual.init(this))
	{
		input.init(this);
		return true;
	}
	return false;
}

//————————————————————————————————————————————————————————————————————————————————————————

Game::~Game()
{
	input.stop();
	visual.stop();
}

HINSTANCE Game::getAppInstance()
{
	return appInstance;
}