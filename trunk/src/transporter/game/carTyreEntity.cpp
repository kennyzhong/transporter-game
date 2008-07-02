#include "transporter.h"

CarTyreEntity::CarTyreEntity( Game* game )
:GameEntity(game)
{

}

//————————————————————————————————————————————————————————————————————————————————————————

CarTyreEntity::~CarTyreEntity()
{

}

//————————————————————————————————————————————————————————————————————————————————————————

bit CarTyreEntity::init(str name)
{
	visualEntity = game->visualSystem.getSceneMgr()->createEntity(name,"Whl01.mesh");
	visualEntity->getMesh()->getSubMesh(0)->setMaterialName("Wheel");
	visualEntity->getMesh()->getSubMesh(1)->setMaterialName("WheelTread");
	visualEntity->getMesh()->getSubMesh(2)->setMaterialName("WheelBackSide");
	visualEntity->setCastShadows(true);
	return true;
}