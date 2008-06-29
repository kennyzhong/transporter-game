#ifndef CARTYREENTITY_H
#define CARTYREENTITY_H
#include "transporter.h"

class CarTyreEntity : public GameEntity
{
protected :
public    : CarTyreEntity(VisualSystem* visual);
			virtual ~CarTyreEntity();
			virtual bit init(str name);
};
#endif