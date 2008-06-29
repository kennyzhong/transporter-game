#ifndef TRANSPORTER_H
#define TRANSPORTER_H
#include <windows.h>

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
#include "ogre/cgProgram/OgreCgPlugin.h"
#include "input/CInputEngine.h"

class Game;
class VisualScene;
class VisualSystem;

#include "transporter/visual/visualSystem.h"
#include "transporter/visual/visualScene.h"
#include "transporter/input/inputSystem.h"
#include "transporter/game/gameEntity.h"
#include "transporter/game/surface.h"
#include "transporter/game/carTyreEntity.h"
#include "transporter/game/carEntity.h"
#include "transporter/game/gameScene.h"
#include "transporter/game/game.h"


#endif