#include "transporter.h"

void errorReportFunction(const char* str, void* params)
{
	RTLog::write(str);	
}

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, int )
{	
	hkMemory* memoryManager = new hkPoolMemory();
	hkThreadMemory threadMemory(memoryManager, 16);
	hkBaseSystem::init( memoryManager, &threadMemory, errorReportFunction );

	char* stackBuffer;
	int stackSize = 8*1024*1024; 
	stackBuffer = hkAllocate<char>( stackSize, HK_MEMORY_CLASS_BASE);
	threadMemory.setStackArea( stackBuffer, stackSize);

	Game transporter;
	if(transporter.init(hInst))
	{
		transporter.run();
		transporter.stop();
	}
	
	//threadMemory.setStackArea(0, 0);
	//hkDeallocate(stackBuffer);
	//hkBaseSystem::clearThreadResources();
	//memoryManager->removeReference();
	hkBaseSystem::quit();
}

//————————————————————————————————————————————————————————————————————————————————————————
