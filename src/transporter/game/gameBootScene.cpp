#include "transporter.h"

bit GameBootScene::init( Game* game )
{
	game->visualSystem.lockThread();

	game->visualSystem.loadResources("BootStrap");

	Ogre::OverlayManager* overlayManager = Ogre::OverlayManager::getSingletonPtr();
	logOverlay = overlayManager->getByName("logText");	
	logOverlay->setZOrder(1);
	loadingScreenOverlay = overlayManager->getByName("loadingScreen");
	loadingScreenOverlay->show();
	loadingScreenOverlay->setZOrder(0);

	overlayPanel = (Ogre::PanelOverlayElement*)overlayManager->getOverlayElement("logTextPanel");	
	logTextOverlay  = (Ogre::TextAreaOverlayElement*)overlayManager->getOverlayElement("logTextArea");
	logTextOverlay->show();

	game->visualSystem.unlockThread();

	return true;
}

void GameBootScene::update()
{
	static bit isClosing;
	if(!isShowLog && logOverlay->isVisible())
	{
		isClosing = true;
	}
	else if(isShowLog && !logOverlay->isVisible())
	{
		overlayPanel->setPosition(0.0f,0.5f);
		logOverlay->show();
	}
	if(isClosing)
	{
		static f32 pos = 0.5f;
		overlayPanel->setPosition(0.0,pos);
		pos += 0.05;
		if(pos > 1.0f)
		{
			logOverlay->hide();
			isClosing = false;
			pos = 0.5f;
		}
	}
	str logText = "";
	u32 k = 25;
	for(u32 i=0 ; i<k ; i++)
	{
		str textItem = RTLog::getLog(i)+ "\n";
		if(textItem.length()-1 > 125)
		{
			while(textItem.length()-1 > 125)
			{
				str subText = textItem.substr(0,125) + "\n  ";
				textItem = textItem.substr(125,textItem.length() - 125);
				logText+= subText;
				k--;
				if(textItem.length() <= 125)
				{
					logText += textItem;
				}
			}	
		}
		else
		{
			logText += textItem;
		}
	}
	logTextOverlay->setCaption(logText);
}

void GameBootScene::showLog( bit isShow )
{
	isShowLog = isShow;
}

GameBootScene::GameBootScene()
{
	logTextOverlay = NULL;
	overlayPanel = NULL;
	logOverlay = NULL;
	isShowLog = true;
}

void GameBootScene::showLoadingScreen( bit isShow )
{
	if(isShow)
	{
		loadingScreenOverlay->show();
	}
	else
	{
		loadingScreenOverlay->hide();
	}
}