#ifndef CARENTITY_H
#define CARENTITY_H
#include "transporter.h"

class CarEntity : public GameEntity
{
protected : Surface* surface;
			hkpReorientAction* physicsActionReorient;
			hkpVehicleInstance* physicsVehicleInstance;
			hkpConvexVerticesShape* createChassisShape();
			CarTyreEntity* tyre[4];
public    : CarEntity(Surface* surface);
			~CarEntity();
			virtual bit init(str name);
};
#endif