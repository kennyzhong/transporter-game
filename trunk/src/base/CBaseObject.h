#ifndef CBASEOBJECT_H
#define CBASEOBJECT_H
#include "base/datatypes.h"

class CBaseObject
{
	protected : str _name;
				CBaseObject* _owner;
	public    : CBaseObject(str name,CBaseObject* owner = NULL);
				CBaseObject(CBaseObject* owner = NULL);
				virtual ~CBaseObject(void){}
				CBaseObject* get_owner(void);
			  
				str get_name(void);
};

#endif