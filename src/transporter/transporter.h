#ifndef TRANSPORTER_H
#define TRANSPORTER_H
#include <windows.h>

#define DIRECTINPUT_VERSION 0x0800

#include "base/datatypes.h"
#include "base/object.h"
#include "base/ObjectFactory.h"
#include "utilities/Event.h"
#include "utilities/genfunction.h"
#include "math/HMath.h"

#include "ogre/Ogre.h"
#include "ogre/openGLRenderSystem/OgreGLRenderSystem.h"
#include "ogre/ogreOctreeSceneMgr/OgreOctreeSceneManager.h"
#include "ogre/openGLRenderSystem/OgreGLPlugin.h"
#include "ogre/ogreOctreeSceneMgr/OgreOctreePlugin.h"
#include "ogre/DXRenderSystem/OgreD3D9Plugin.h"
#include "ogre/cgProgram/OgreCgPlugin.h"
#include "ogre/OgreOverlay.h"
#include "ogre/OgreTextAreaOverlayElement.h"
#include "input/CInputEngine.h"
#include "physics/Common/Base/hkBase.h"
#include "physics/Common/Base/Types/Geometry/hkGeometry.h"
#include "physics/Common/Base/System/Error/hkDefaultError.h"
#include "physics/Common/Base/System/hkBaseSystem.h"
#include "physics/Common/Base/Memory/MemoryClasses/hkMemoryClassDefinitions.h"
#include "physics/Common/Base/Memory/hkThreadMemory.h"
#include "physics/Common/Base/Memory/Memory/Pool/hkPoolMemory.h"
#include "physics/Common/Base/Math/hkMath.h"
#include "physics/Common/Base/Container/Array/hkArray.h"
#include "physics/Common/Base/Container/Array/hkObjectArray.h"
#include "physics/Physics/Dynamics/hkpDynamics.h"
#include "physics/Physics/Dynamics/World/hkpWorld.h"
#include "physics/Physics/Dynamics/World/hkpWorldCinfo.h"
#include "physics/Physics/Collide/hkpCollide.h"
#include "physics/Physics/Collide/Dispatch/hkpAgentRegisterUtil.h"
#include "physics/Physics/Collide/Filter/Group/hkpGroupFilter.h"
#include "physics/Physics/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h"
#include "physics/Physics/Internal/hkpInternal.h"
#include "physics/Physics/Vehicle/hkpVehicle.h"
#include "physics/Physics/Utilities/Actions/Reorient/hkpReorientAction.h"
#include "physics/Physics/Vehicle/hkpVehicleInstance.h"
#include "physics/Internal/PreProcess/ConvexHull/hkpGeometryUtility.h"

class Game;
class VisualScene;
class VisualSystem;

#define EV_UPDATE_PHYSICS_FORCE   1
#define EV_UPDATE_VISUAL_ENTITIES 2

#include "transporter/game/debugRegistry.h"
#include "transporter/utilities/updateListener.h"
#include "transporter/utilities/updateListenerMgr.h"
#include "transporter/visual/visualSystem.h"
#include "transporter/visual/visualScene.h"
#include "transporter/physics/physicsFlatLand.h"
#include "transporter/physics/physicsScene.h"
#include "transporter/physics/physicsSystem.h"
#include "transporter/physics/physicsVehicleSetup.h"
#include "transporter/input/inputSystem.h"
#include "transporter/game/gameEntity.h"
#include "transporter/game/surface.h"
#include "transporter/game/carSteering.h"
#include "transporter/game/carTyreEntity.h"
#include "transporter/game/carEntity.h"
#include "transporter/game/gameScene.h"
#include "transporter/game/game.h"


#endif