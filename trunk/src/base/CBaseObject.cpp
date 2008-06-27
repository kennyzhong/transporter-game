#include "base/CBaseObject.H"
#include "utilities/genFunction.h"

CBaseObject::CBaseObject(str name,CBaseObject* owner)
{
	_owner = owner;
	_name = name;
}

CBaseObject::CBaseObject(CBaseObject* owner)
{	
	static int cnt;
	_name = "object"+IntToStr(cnt++);
	_owner = owner;
}

str CBaseObject::get_name(void)
{
	return _name;
}


CBaseObject* CBaseObject::get_owner(void)
{
	return _owner;
}