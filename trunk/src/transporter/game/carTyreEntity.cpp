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
	visualEntity = game->visualSystem.getSceneMgr()->createEntity(name,"tyre.mesh");
	visualEntity->setMaterialName("tyreMaterial");
	return true;
}