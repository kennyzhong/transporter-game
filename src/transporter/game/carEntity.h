#ifndef CARENTITY_H
#define CARENTITY_H
#include "transporter.h"

class CarEntity;

class CarDebugInfo : public DebugRegistryBaseItem
{
protected : virtual str print();
			CarEntity* entity;
public    : CarDebugInfo();
			~CarDebugInfo();
			void setEntity(CarEntity* entity);
};

class CarEntity : public GameEntity
{
friend class CarDebugInfo;
protected : Surface* surface;
			//hkpReorientAction* physicsActionReorient;
			hkpVehicleInstance* physicsVehicleInstance;
			hkpConvexVerticesShape* createChassisShape();
			CarTyreEntity* tyre[4];
			CarSteering steeringInput;
			CarInstruments instruments;
			CarDebugInfo debugInfo;
			Ogre::Entity* physicsShape;
			hkpVehicleTransmission::TransmissionOutput transmissionOutput;
			virtual void updatePhysics(u32 timeElapse);
			virtual void updateVisual();
public    : CarEntity(Surface* surface);
			~CarEntity();
			virtual bit init(str name);
};
#endif