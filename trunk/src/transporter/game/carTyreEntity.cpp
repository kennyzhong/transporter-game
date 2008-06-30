#include "transporter.h"

CarTyreEntity::CarTyreEntity( Game* game )
:GameEntity(game)
{

}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

CarTyreEntity::~CarTyreEntity()
{

}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

bit CarTyreEntity::init(str name)
{
	visualEntity = game->visualSystem.getSceneMgr()->createEntity(name,"tyre.mesh");
	visualEntity->setMaterialName("tyreMaterial");
	return true;
}