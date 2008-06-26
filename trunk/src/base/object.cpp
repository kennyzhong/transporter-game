#include "base/object.h"
#include "base/ObjectFactory.h"

u32 Object::getClassId()
{
	return _classId;
}

u32 Object::getId()
{
	return _objectId;
}

Object::Object( u32 classId,u32 objectId )
{
	_classId = classId;
	_objectId = objectId;
}

Object::~Object()
{

}

void Object::destroy()
{
	BaseObjectFactory* factory = ObjectFactoryMgr::getFactory(this->_classId);
	if(factory)
	{
		factory->destroy(this->_objectId);
	}
}