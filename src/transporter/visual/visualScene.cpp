#include "transporter.h"

VisualScene::VisualScene()
{
	this->game = NULL;
}

//————————————————————————————————————————————————————————————————————————————————————————

VisualScene::~VisualScene()
{

}

//————————————————————————————————————————————————————————————————————————————————————————

bit VisualScene::init(Game* game)
{	
	this->game = game;

	game->visualSystem.getSceneMgr()->setAmbientLight(Ogre::ColourValue(1.0,1.0,1.0));
	game->visualSystem.getSceneMgr()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	game->visualSystem.getSceneMgr()->setShadowColour( Ogre::ColourValue(0.5, 0.5, 0.5) );
	game->visualSystem.getSceneMgr()->setSkyBox(true,"skybox",10000);

	Ogre::Light* light = game->visualSystem.getSceneMgr()->createLight("MainLight");
	light->setType(Ogre::Light::LT_SPOTLIGHT);
	light->setPosition(500,500,200);
	light->setDirection(-light->getPosition());
	light->setSpecularColour(1.0,9.0,8.0);
	light->setDiffuseColour(1.0,9.0,8.0);
	light->setPowerScale(1.0);
	light->setCastShadows(true);	
	
	game->visualSystem.getCamera()->setPosition(0,20,-100);
	game->visualSystem.getCamera()->lookAt(0,0,1);

	return true;
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualScene::update()
{
	updateCamera();
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualScene::updateCamera()
{
	static f32 rotz;
	static f32 rotx;
	static f32 roty;

	rotz += f32(game->inputSystem.getMouseMovement(2))/10.0f; 
	rotz  = clampValue(rotz,10.0f,100.0f);

	if(game->inputSystem.getMouseBtnState(1)) 
	{
		rotx += (f32)game->inputSystem.getMouseMovement(0);
		roty += (f32)game->inputSystem.getMouseMovement(1);
		
		rotx = circularValue(rotx,0.0f,360.0f);
		roty = clampValue(roty,5.0f,85.0f); 
	}	

	Ogre::Vector3 pos = Ogre::Vector3::ZERO;
	pos.z = rotz*cos(hmath::deg(rotx).asRad())*sin(hmath::deg(roty).asRad());
	pos.x = rotz*sin(hmath::deg(rotx).asRad())*sin(hmath::deg(roty).asRad());
	pos.y = rotz*cos(hmath::deg(roty).asRad());

	game->visualSystem.getCamera()->setPosition(pos);
	game->visualSystem.getCamera()->lookAt(0,0,0);
	game->inputSystem.resetMouseMovement();
}

//————————————————————————————————————————————————————————————————————————————————————————

void VisualScene::cleanUp()
{
	//game->visual.getSceneMgr()->clearScene();
}