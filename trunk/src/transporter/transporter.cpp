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
