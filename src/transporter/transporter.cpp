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
	char* stackBuffer;
	int stackSize = 2*1024*1024; // 2MB stack
	stackBuffer = hkAllocate<char>( stackSize, HK_MEMORY_CLASS_BASE);
	threadMemory.setStackArea( stackBuffer, stackSize);

	Game transporter;
	if(transporter.init(hInst))
	{
		transporter.run();
	}

	threadMemory.setStackArea(0, 0);
	hkDeallocate(stackBuffer);
	//threadMemory.removeReference();
	hkBaseSystem::quit();
}

//————————————————————————————————————————————————————————————————————————————————————————
