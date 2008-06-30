#include "transporter.h"

void Game::run()
{
	isRunning = true;
	inputSystem.run();
	physicsSystem.run(&gameScene.physicsWorld);
	visualSystem.run(&gameScene.visualWorld);	
}

//————————————————————————————————————————————————————————————————————————————————————————

bit Game::init(HINSTANCE instance)
{
	this->appInstance = instance;
	if(visualSystem.init(this))
	{
		bit result = true;
		result &= inputSystem.init(this);
		result &= physicsSystem.init(this);
		result &= gameScene.init(this);
		return result;
	}
	return false;
}

//————————————————————————————————————————————————————————————————————————————————————————

Game::Game()
{
	isRunning = false;
}

Game::~Game()
{	
	stop();
}

//————————————————————————————————————————————————————————————————————————————————————————

HINSTANCE Game::getAppInstance()
{
	return appInstance;
}

//————————————————————————————————————————————————————————————————————————————————————————

void Game::stop()
{
	if(isRunning)
	{
		inputSystem.stop();
		physicsSystem.stop();
		visualSystem.stop();

		gameScene.cleanUp();
		isRunning = false;
	}
}
