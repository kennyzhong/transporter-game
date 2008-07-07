#include "transporter.h"

VisualScene::VisualScene()
{
	this->game = NULL;
}

//————————————————————————————————————————————————————————————————————————————————————————

VisualScene::~VisualScene()
{

}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualScene::init(Game* game)
{	
	this->game = game;
	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualScene::update()
{

}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualScene::cleanUp()
{
	//game->visual.getSceneMgr()->clearScene();
}

