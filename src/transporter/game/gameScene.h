#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "transporter.h"

class GameScene
{
protected : Game* game;
			Surface* surface;
			CarEntity* car;
			void createEntities();
public    : GameScene();
			~GameScene();
			virtual bit init(Game* game);
			void cleanUp();

			VisualScene visualWorld;
			PhysicsScene physicsWorld;
};
#endif