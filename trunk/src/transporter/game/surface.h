#ifndef SURFACE_H
#define SURFACE_H
#include "transporter.h"

class Surface : public GameEntity
{
protected : 
public    : Surface(VisualSystem* visual);
			~Surface();
			virtual bit init(str name);
};

#endif