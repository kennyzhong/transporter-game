#ifndef GAME_H
#define GAME_H
#include "transporter.h"

class Game
{
protected : HINSTANCE appInstance;
public    : Game() {};
			~Game();
			void run();
			bit init(HINSTANCE instance);
			HINSTANCE getAppInstance();
			VisualSystem visual;
			InputSystem input;
			PhysicsSystem physics;
			GameScene scene;
};

#endif