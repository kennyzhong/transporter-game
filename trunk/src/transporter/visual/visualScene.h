#ifndef VISUALSCENE_H
#define VISUALSCENE_H

class VisualScene
{
protected : Game* game;
			void updateCamera();
public    : VisualScene();
			~VisualScene();

			bit init(Game* game);
			void update();
			void cleanUp();
};
#endif