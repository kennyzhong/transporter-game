#ifndef VISUALSYSTEM_H
#define VISUALSYSTEM_H

#include <windows.h>

#include "base/datatypes.h"
#include "math/HMath.h"
#include "utilities/Event.h"
#include "utilities/genfunction.h"
#include "base/object.h"
#include "base/ObjectFactory.h"

#include "ogre/Ogre.h"
#include "ogre/openGLRenderSystem/OgreGLRenderSystem.h"
#include "ogre/ogreOctreeSceneMgr/OgreOctreeSceneManager.h"
#include "ogre/openGLRenderSystem/OgreGLPlugin.h"
#include "ogre/ogreOctreeSceneMgr/OgreOctreePlugin.h"
#include "ogre/cgProgram/OgreCgPlugin.h"

#include "transporter/visual/window.h"
#include "transporter/visual/win32window.h"
#include "transporter/visual/visualHDRCompositor.h"

class VisualSystem
{
protected : Ogre::RenderWindow* renderWindow;
			Ogre::RenderSystem* renderSystem;
			Ogre::Camera* renderCamera;
			Ogre::Viewport* renderViewport;
			Ogre::SceneManager* sceneMgr;
			Ogre::Root* visualRoot;
			Ogre::GLPlugin* glPlugin;
			Ogre::OctreePlugin* octreePlugin;
			Ogre::CgPlugin* cgPlugin;
			HDRCompositor* hdrCompositor;
			HWND renderWindowHandle;
			bit isVisualRunning;
			bit isVisualInited;
			void createSphere(const str& strName, const f32 r, const i32 nRings = 16, const i32 nSegments = 16);
			void createScene();
			void updateScene();
			void init();
			void cleanUp();
			static void evRenderWindowClosed(void* self,Window* wnd);
			static DWORD WINAPI visualThreadProc(LPVOID param);

public    : VisualSystem();
			~VisualSystem();
						
			void run();
			void stop();
			bit isRunnning();
};
#endif