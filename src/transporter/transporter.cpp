#include "transporter.h"

void errorReportFunction(const char* str, void* params)
{
	printf("\n %s",str);
}

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, int )
{	
	hkMemory* memoryManager = new hkPoolMemory();
	hkThreadMemory threadMemory(memoryManager, 16);
	hkBaseSystem::init( memoryManager, &threadMemory, errorReportFunction );
	memoryManager->removeReference();

	Game transporter;
	if(transporter.init(hInst))
	{
		transporter.run();
		transporter.stop();
	}

	hkBaseSystem::quit();
}

//————————————————————————————————————————————————————————————————————————————————————————
