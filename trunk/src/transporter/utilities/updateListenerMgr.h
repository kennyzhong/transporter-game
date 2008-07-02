#ifndef UPDATELISTENERMGR_H
#define UPDATELISTENERMGR_H
#include "transporter.h"

class UpdateListenerMgr
{
friend class UpdateListener;
private   : static void destroyUpdateListenerMgr();
protected : UpdateListenerMgr();
			~UpdateListenerMgr();
			CRITICAL_SECTION lock;
			std::vector<UpdateListener*> listeners;					
public    : static UpdateListenerMgr* getInstance();
			void update(u32 evId,u32 param);
			void addListener(UpdateListener* listener);
			void removeListener(UpdateListener* listener);
};
#endif