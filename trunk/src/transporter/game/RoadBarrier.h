#ifndef ROADBARRIER_H
#define ROADBARRIER_H
#include "transporter.h"

class RoadBarrier : public GameEntity
{
protected : virtual void updatePhysics(u32 timeElapse);
			virtual void updateVisual();
public    : RoadBarrier(Game* game);
			virtual ~RoadBarrier();
			virtual bit init(str name);
};
#endif