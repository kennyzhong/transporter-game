#ifndef GAME_H
#define GAME_H
#include "transporter.h"

class Game
{
protected : HINSTANCE appInstance;
			bit isRunning;			
public    : Game();
			~Game();
			void run();
			void stop();
			bit init(HINSTANCE instance);
			HINSTANCE getAppInstance();

			VisualSystem visualSystem;
			InputSystem inputSystem;
			PhysicsSystem physicsSystem;
			GameScene gameScene;
			GameBootScene bootScene;
};

#endif