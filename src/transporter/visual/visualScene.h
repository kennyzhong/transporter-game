#ifndef VISUALSCENE_H
#define VISUALSCENE_H
#include "transporter.h"

class VisualScene
{
protected : Game* game;			
public    : VisualScene();
			virtual ~VisualScene();

			virtual bit init(Game* game);
			virtual void update();
			virtual void cleanUp();
};
#endif