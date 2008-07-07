#ifndef CARSTEERING_H
#define CARSTEERING_H
#include "transporter.h"

class CarSteering : public DebugRegistryBaseItem
{
protected : f32 steering;
			f32 throttle;
			f32 braking;
			bit handBrake;
			i32 gearShift;
			f32 steeringSaturation;
			f32 throttleSaturation;
			f32 brakingSaturation;

			u32 throttleKey;
			u32 brakingKey;
			u32 leftSteeringKey;
			u32 rightSteeringKey;
			u32 handBrakeKey;
			u32 gearUpshiftKey;
			u32 gearDownshiftKey;

			bit isThrottleKeyPressed;
			bit isBrakingKeyPressed;
			i32 isSteeringKey;

			InputSystem* inputSystem;

			void updateThrottleKey(u32 timeElapse);
			void updateBrakingKey(u32 timeElapse);
			void updateSteeringKey(u32 timeElapse);

			static void onKeyDown(void* userptr,u32 btn);
			static void onKeyUp(void* userptr,u32 btn);
			static void onKeyPressed(void* userptr,u32 btn);

			virtual str print();

public    : CarSteering(InputSystem* inputSystem);
			~CarSteering();

			f32 getSteering();
			f32 getThrottle();
			f32 getBraking();
			bit getHandBrake();
			i32 getGearShift();

			f32 getSteeringSaturation();
			f32 getThrottleSaturation();
			f32 getBrakingSaturation();

			void setSteeringSaturation(f32 value);
			void setThrottleSaturation(f32 value);
			void setBrakingSaturation(f32 value);

			void update(u32 timeElapse);
};
#endif