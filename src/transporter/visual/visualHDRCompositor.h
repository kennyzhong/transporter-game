/**
* This source file is part of HDRlib
* an addon for OGRE (Object-oriented Graphics Rendering Engine)
* For the latest info, see http://www.ogre3d.org/
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU Lesser General Public License as published by the Free Software
* Foundation; either version 2 of the License, or (at your option) any later
* version.

* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

* You should have received a copy of the GNU Lesser General Public License along with
* this program; if not, write to the Free Software Foundation, Inc., 59 Temple
* Place - Suite 330, Boston, MA 02111-1307, USA, or go to
* http://www.gnu.org/copyleft/lesser.txt.
*
* @author	Christian Luksch, modified by uray
* @see		Readme.txt
*/

#ifndef VISUAL_HDR_COMPOSITOR_H
#define VISUAL_HDR_COMPOSITOR_H
#include "transporter/visual/visualSystem.h"

using namespace Ogre;

class HDRCompositor : public Ogre::CompositorInstance::Listener
{
public:

	enum MATID
	{
		MID_KEY = 12345,
		MID_LUMSCALE1,
		MID_LUMSCALE2,
		MID_LUMSCALE4,
		MID_LUMSCALE8,
		MID_BUILDLOCAL,
		MID_DOWN,
		MID_BRIGHT,
		MID_GAUSSBLUR,
		MID_FINAL,
		MID_ADAPT,
		MID_SCALE //must be last		
	};

protected:
	f32		m_GlareStrength;
	i32		m_GlarePasses;
	bit		m_AutoKeying;
	f32		m_Key;
	bit		m_LumAdaption;
	f32		m_VpWidth,m_VpHeight;
	bit		m_Enable;
	f32		m_FrameTime;
	f32		m_AdaptationScale;
	f32		m_BrightPassOffset;
	f32		m_BrightPassThresshold;
	const i32	m_Scales;
	f32		m_E;
	f32		m_Phi;

	RenderWindow*	m_Window;
	Camera*			m_Cam;

	CompositorPtr m_Compositor;
	CompositionTechnique *m_HDRTechnique;

public:

	HDRCompositor(RenderWindow* win, Camera* cam);
	~HDRCompositor(void) { }

	void Release(void);
	void Create(void);

	void Enable(const bool Enable);
	bool IsEnabled(void) const { return m_Enable; }

	float GetGlareStrength(void) const { return m_GlareStrength; }
	void SetGlareStrength(const float Strength) { m_GlareStrength = Strength; }

	int GetGlarePasses(void) const {	return m_GlarePasses; }
	void SetGlarePasses(const float Passes) { m_GlarePasses = Passes; }


	bool GetAutoKeying(void) const { return m_AutoKeying; }
	void SetAutoKeying(const bool AutoKeying) {	m_AutoKeying = AutoKeying; }

	bool GetLumAdaption(void) const { return m_LumAdaption; }
	void SetLumAdapdation(bool LumAdaptation) {	m_LumAdaption = LumAdaptation; }

	float GetKey(void) const { return m_Key; }
	void SetKey(const float Key) { m_Key = Key; }

	float GetAdaptationScale(void) const {return m_AdaptationScale;}
	void SetAdaptationScale(const float Scale) {m_AdaptationScale = Scale;}

	float GetLocalE(void) const {	return m_E; }
	void SetLocalE(const float e) { m_E = e; }

	float GetLocalPhi(void) const {	return m_Phi; }
	void SetLocalPhi(const float phi) { m_Phi = phi; }

	void SetFrameTime(const float FrameTime) { m_FrameTime = FrameTime; }

	//called once on material setup
	virtual void notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);

	//called every frame
	virtual void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
	virtual void notifyViewportSize(int width, int height);

private:	

	void CreateTextureDef(const String name,const unsigned int width,const unsigned int height,const Ogre::PixelFormat format);
	void BrightPass(void);
	void RenderDownSample(void);
	void CalculateLuminance(void);
	void BuildGlare(void);
	void CalculateKey(void);
	void BuildScales(void);
	void FinalRendering(void);
	void BuildGaussGlare(float* out,float rho,float strength, float vpScale);
};

#endif