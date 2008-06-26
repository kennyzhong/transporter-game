#ifndef OBJECT_H
#define OBJECT_H
#include "base/datatypes.h"

class Object
{
protected : u32 _classId;
			u32 _objectId;
public    : Object(u32 classId,u32 objectId);
			virtual ~Object();
			virtual u32 getClassId();
			virtual u32 getId();
			void destroy();
};
#endif