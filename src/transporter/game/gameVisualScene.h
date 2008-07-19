#ifndef GAMEVISUALSCENE_H
#define GAMEVISUALSCENE_H
#include "transporter.h"

class GameVisualScene : public VisualScene
{
protected : Ogre::TextAreaOverlayElement* debugTextOverlay;
			
public    : GameVisualScene();
			virtual ~GameVisualScene();

			virtual bit init(Game* game);
			virtual void update();
			virtual void cleanUp();
			void updateCamera();
			void updateOverlays();
};
#endif