#ifndef CARINSTRUMENTS_H
#define CARINSTRUMENTS_H
#include "transporter.h"

class CarEntity;

class CarInstruments
{
protected : f32 speedometer;
			f32 tachometer;
			CarEntity* car;
			Ogre::Overlay* instrumentsOverlay;
			Ogre::Overlay* speedometerOverlay;
			Ogre::Overlay* tachometerOverlay;
			Ogre::PanelOverlayElement* instrumentsPanel;
			Ogre::PanelOverlayElement* speedometerGauge;
			Ogre::PanelOverlayElement* tachometerGauge;
			bit isInited;
public    : CarInstruments();
			void init(CarEntity* entity);
			void update();
			void setSpeedometer(f32 value);
			void setTachometer(f32 value);
};
#endif