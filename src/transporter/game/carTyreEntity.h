#ifndef CARTYREENTITY_H
#define CARTYREENTITY_H
#include "transporter.h"

class CarTyreEntity : public GameEntity
{
protected :
public    : CarTyreEntity(Game* game);
			virtual ~CarTyreEntity();
			virtual bit init(str name);
};
#endif