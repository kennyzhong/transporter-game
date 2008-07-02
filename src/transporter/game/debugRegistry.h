#ifndef DEBUGREGISTRY_H
#define DEBUGREGISTRY_H
#include "transporter.h"

class DebugRegistryBaseItem
{
protected : str debugItemName;
public    : DebugRegistryBaseItem(str name);
			virtual ~DebugRegistryBaseItem();
			virtual str print() = 0;
			str getDebugItemName();
};

class DebugRegistry
{
friend class DebugRegistryBaseItem;
private   : static void destroyDebugRegistry();
protected : DebugRegistry();
			~DebugRegistry();
			CRITICAL_SECTION lock;
			std::map<str,DebugRegistryBaseItem*> items;			
public    : static DebugRegistry* getInstance();
			DebugRegistryBaseItem* getItem(str name);
			bit addItem(DebugRegistryBaseItem* item);
			void removeItem(str name);
			str print();
};
#endif