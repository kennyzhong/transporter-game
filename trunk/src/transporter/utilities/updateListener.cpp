#include "transporter.h"

UpdateListener::UpdateListener()
{
	UpdateListenerMgr::getInstance()->addListener(this);
}

UpdateListener::~UpdateListener()
{
	UpdateListenerMgr::getInstance()->removeListener(this);
}

void UpdateListener::update( u32 evId,u32 param )
{

}