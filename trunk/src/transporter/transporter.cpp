#include "transporter.h"

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, int )
{	
	Game transporter;
	transporter.run();
}

//————————————————————————————————————————————————————————————————————————————————————————

void Game::run()
{
	visual.run();
}