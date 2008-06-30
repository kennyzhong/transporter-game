#ifndef SURFACE_H
#define SURFACE_H
#include "transporter.h"

class Surface : public GameEntity
{
protected : PhysicsFlatLand* physicsSurfaceShape;
public    : Surface(Game* game);
			~Surface();
			virtual bit init(str name);
};

#endif