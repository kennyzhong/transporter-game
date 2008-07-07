#include "transporter.h"

void Game::run()
{
	isRunning = true;
			
	visualSystem.addScene(&gameScene.visualWorld);		
	physicsSystem.run(&gameScene.physicsWorld);	

	inputSystem.start();
	bootScene.showLog(false);
	bootScene.showLoadingScreen(false);
	visualSystem.waitUntilEnd();
}

//————————————————————————————————————————————————————————————————————————————————————————

bit Game::init(HINSTANCE instance)
{
	this->appInstance = instance;
	bit result = visualSystem.init(this);	
	if(result)
	{
		bootScene.init(this);
		visualSystem.addScene(&bootScene);
		visualSystem.run();	
		
		result &= inputSystem.init(this);
		result &= physicsSystem.init(this);		
		result &= gameScene.init(this);	
		result &= gameScene.physicsWorld.init(this);
		result &= gameScene.visualWorld.init(this);
		gameScene.createEntities();
	}
	return result;
}

//————————————————————————————————————————————————————————————————————————————————————————

Game::Game()
{
	isRunning = false;
}

//————————————————————————————————————————————————————————————————————————————————————————

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
