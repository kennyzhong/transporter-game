#ifndef GAMEVISUALSCENE_H
#define GAMEVISUALSCENE_H
#include "transporter.h"

class GameVisualScene : public VisualScene
{
protected : Ogre::TextAreaOverlayElement* debugTextOverlay;
			void updateCamera();
			void updateOverlays();
public    : GameVisualScene();
			virtual ~GameVisualScene();

			virtual bit init(Game* game);
			virtual void update();
			virtual void cleanUp();
};
#endif