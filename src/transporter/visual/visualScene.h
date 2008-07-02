#ifndef VISUALSCENE_H
#define VISUALSCENE_H
#include "transporter.h"

class VisualScene
{
protected : Game* game;
			Ogre::TextAreaOverlayElement* debugTextOverlay;
			void updateCamera();
			void updateOverlays();
public    : VisualScene();
			~VisualScene();

			bit init(Game* game);
			void update();
			void cleanUp();
};
#endif