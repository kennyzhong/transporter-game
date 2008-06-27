#ifndef VISUALSCENE_H
#define VISUALSCENE_H

class VisualScene
{
protected : Game* game;
			void updateCamera();
public    : VisualScene();
			~VisualScene();

			void init(Game* game);
			void update();
};
#endif