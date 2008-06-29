#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "transporter.h"

class GameScene
{
protected : Game* game;
			Surface* surface;
			CarEntity* car;
public    : GameScene();
			~GameScene();
			virtual bit init(Game* game);
			virtual void update();
			void cleanUp();

			VisualScene visual;
};
#endif