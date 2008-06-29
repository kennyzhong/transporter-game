#include "transporter.h"

CarTyreEntity::CarTyreEntity( VisualSystem* visual )
:GameEntity(visual)
{

}

//————————————————————————————————————————————————————————————————————————————————————————

CarTyreEntity::~CarTyreEntity()
{

}

//————————————————————————————————————————————————————————————————————————————————————————

bit CarTyreEntity::init(str name)
{
	visualEntity = visualSystem->getSceneMgr()->createEntity(name,"tyre.mesh");
	visualEntity->setMaterialName("tyreMaterial");
	return true;
}