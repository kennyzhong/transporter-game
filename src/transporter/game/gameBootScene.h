#ifndef GAMEBOOTSCENE_H
#define GAMEBOOTSCENE_H
#include "transporter.h"

class GameBootScene : public VisualScene
{
protected : Ogre::TextAreaOverlayElement* logTextOverlay;
			Ogre::PanelOverlayElement* overlayPanel;
			Ogre::Overlay* logOverlay;
			Ogre::Overlay* loadingScreenOverlay;
			bit isShowLog;			
public    : GameBootScene();
			virtual bit init(Game* game);
			virtual void update();
			void showLog(bit isShow);
			void showLoadingScreen(bit isShow);
			bit isLogVisible(){return isShowLog;};
};
#endif