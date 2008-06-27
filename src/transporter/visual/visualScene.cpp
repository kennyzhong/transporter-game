#include "transporter.h"

VisualScene::VisualScene()
{
	this->game = NULL;
}

VisualScene::~VisualScene()
{

}

void VisualScene::init(Game* game)
{	
	this->game = game;

	game->visual.getSceneMgr()->setAmbientLight(Ogre::ColourValue(1.0,1.0,1.0));
	game->visual.getSceneMgr()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	game->visual.getSceneMgr()->setShadowColour( Ogre::ColourValue(0.5, 0.5, 0.5) );
	game->visual.getSceneMgr()->setSkyBox(true,"skybox",10000);

	Ogre::Plane surfacePlane;
	surfacePlane.normal = Ogre::Vector3::UNIT_Y;
	surfacePlane.d = 0;
	Ogre::MeshManager::getSingleton().createPlane("surface",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		surfacePlane,
		4096, 4096, 128, 128, true, 1, 128, 128, Ogre::Vector3::UNIT_Z);

	Ogre::SceneNode* surfaceNode = game->visual.getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* surfaceEntity  = game->visual.getSceneMgr()->createEntity( "surface", "surface" );
	surfaceEntity->setMaterialName("asphalt");
	surfaceNode->attachObject(surfaceEntity);
	surfaceNode->setPosition(0,0,0);
	
	game->visual.getCamera()->setPosition(0,20,-300);
	game->visual.getCamera()->lookAt(0,0,1);
}

void VisualScene::update()
{
	updateCamera();
}

void VisualScene::updateCamera()
{
	static f32 rotz;
	static f32 rotx;
	static f32 roty;

	rotz += f32(game->input.getMouseMovement(2))/10.0f; 
	rotz  = clampValue(rotz,50.0f,400.0f);

	if(game->input.getMouseBtnState(1)) 
	{
		rotx += (f32)game->input.getMouseMovement(0);
		roty += (f32)game->input.getMouseMovement(1);
		
		rotx = circularValue(rotx,0.0f,360.0f);
		roty = clampValue(roty,1.0f,89.0f); 
	}	

	Ogre::Vector3 pos = Ogre::Vector3::ZERO;
	pos.z = rotz*cos(hmath::deg(rotx).asRad())*sin(hmath::deg(roty).asRad());
	pos.x = rotz*sin(hmath::deg(rotx).asRad())*sin(hmath::deg(roty).asRad());
	pos.y = rotz*cos(hmath::deg(roty).asRad());

	game->visual.getCamera()->setPosition(pos);
	game->visual.getCamera()->lookAt(0,0,0);
	game->input.resetMouseMovement();
}