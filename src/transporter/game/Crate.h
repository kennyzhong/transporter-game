#ifndef CRATE_H
#define CRATE_H
#include "transporter.h"

class Crate : public GameEntity
{
protected : virtual void updatePhysics(u32 timeElapse);
			virtual void updateVisual();
public    : Crate(Game* game);
			virtual ~Crate();
			virtual bit init(str name);
};
#endif