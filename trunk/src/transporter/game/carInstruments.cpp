#include "transporter.h"

CarInstruments::CarInstruments()
{
	speedometer = 0.0f;
	tachometer = 0.0f;
	instrumentsOverlay = NULL;
	instrumentsPanel = NULL;
	car = NULL;
	isInited = false;
}

void CarInstruments::init( CarEntity* entity )
{
	this->car = entity;
	Ogre::OverlayManager* overlayMgr = Ogre::OverlayManager::getSingletonPtr();
	instrumentsOverlay = overlayMgr->getByName("instrumentsOverlay");
	speedometerOverlay = overlayMgr->getByName("speedometerOverlay");
	tachometerOverlay  = overlayMgr->getByName("tachometerOverlay");
	instrumentsPanel = (Ogre::PanelOverlayElement*)overlayMgr->getOverlayElement("instrumentsOverlayPanel");
	tachometerGauge = (Ogre::PanelOverlayElement*)overlayMgr->getOverlayElement("tachoMeterGaugePanel");
	speedometerGauge = (Ogre::PanelOverlayElement*)overlayMgr->getOverlayElement("speedoMeterGaugePanel");
	instrumentsOverlay->show();
	instrumentsOverlay->setZOrder(2);
	tachometerOverlay->show();
	tachometerOverlay->setZOrder(3);
	speedometerOverlay->show();
	speedometerOverlay->setZOrder(3);

	u32 screenWidth = entity->getGame()->visualSystem.getPrimaryRenderWindow()->getWidth();
	u32 screenHeight = entity->getGame()->visualSystem.getPrimaryRenderWindow()->getHeight();

	//instrumentsPanel->setHorizontalAlignment(Ogre::GuiHorizontalAlignment::GHA_RIGHT);
	//instrumentsPanel->setVerticalAlignment(Ogre::GuiVerticalAlignment::GVA_BOTTOM);
	instrumentsPanel->setPosition(screenWidth-512+32,screenHeight-512+112);
	tachometerGauge->setPosition(screenWidth-512+128+32,screenHeight-512+128+112);
	speedometerGauge->setPosition(screenWidth-512+128+94+32,screenHeight-512+128+43+112);
	isInited = true;
}

void CarInstruments::setSpeedometer( f32 value )
{
	speedometer = value;
}

void CarInstruments::setTachometer( f32 value )
{
	tachometer = value;
}

void CarInstruments::update()
{
	if(isInited)
	{
		f32 speedAngle = 225.0f*speedometer/300.0f;
		f32 rpmAngle = 225.0f*tachometer/10000.0f;

		speedometerGauge->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureRotate(Ogre::Degree(-speedAngle));
		tachometerGauge->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureRotate(Ogre::Degree(-rpmAngle));
	}
}
