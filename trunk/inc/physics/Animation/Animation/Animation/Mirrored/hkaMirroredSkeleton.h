/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2008 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HKANIMATION_ANIMATION_HKMIRROREDSKELETON_H
#define HKANIMATION_ANIMATION_HKMIRROREDSKELETON_H

#include <Animation/Animation/Animation/hkaSkeletalAnimation.h>
#include <Common/Base/Math/Util/hkConvertCoordinateSpace.h>

class hkaSkeleton;

	/// This is a helper class for the hkaMirroredSkeletalAnimation which encapsulates the 'mirroring' functionality
	/// and works at a per-bone level (rather than the per-track level of a hkaSkeletalAnimation).
class hkaMirroredSkeleton : public hkReferencedObject
{

	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RIG );

		/// Constructor for hkaMirroredSkeletalAnimation
		/// \param skeleton Rig hierarchy
		hkaMirroredSkeleton( const hkaSkeleton *skeleton );

		~hkaMirroredSkeleton();

		// MIRRORING SETTINGS

		/// Set the mirror axis
		/// \param v Axis to mirror about
		void setMirrorAxis( const hkVector4 &v );
	 
		/// Sets the mode to mix coordinate systems between left and right sides
		/// \param negate Enables/disables mixed mode
		void setMixedMode( hkBool mixed = true );

		/// Set the default orientation of the root node
		/// \param T Transformation to account for an offset of the root
		void setRootOrientation( const hkQsTransform &T );

		/// Set the default orientation of direct children of the root
		/// \param T Transformation to account for an offset of children of the root
		void setChildOrientation( const hkQsTransform &T );

		/// Set an orientation for the nubs
		/// \param T Transformation to account for nub non-conformance
		void setNubOrientation( const hkQsTransform &T );

		
		// PAIRING

		/// Allows the user to set bone pairing information
		/// \param bi Bone to pair with bj
		/// \param bj Bone to pair with bi
		void setBonePair( hkInt16 bi, hkInt16 bj );

		/// Allows the user to set all of the bone pairing information at once
		/// \param bonePairMap The mapping of bones to their mirrored partners
		/// \param numBonePairMap The number of elements in bonePairMap
		void setBonePairMap( hkInt16* bonePairMap, int numBonePairMap );

		/// Allows the user to query bone pairing information
		/// \return The paired bone for bi
		/// \param bi Bone to query pair information for
		hkInt16 getBonePair( hkInt16 bi ) const;

#if !defined(HK_PLATFORM_SPU)
		/// Computes bone pairing information from unique substrings of bone names
		/// \param ltag Array of strings uniquely identifying left bones
		/// \param ltag Array of strings uniquely identifying right bones
		void computeBonePairingFromNames( const hkObjectArray< hkString > &ltag, const hkObjectArray< hkString > &rtag );

		/// Computes bone pairing information from unique substrings of bone names
		/// \param ltag Array of strings uniquely identifying left bones
		/// \param ltag Array of strings uniquely identifying right bones
		/// \param skeleton The skeleton that is being mirrored
		/// \param bonePairMap The buffer for the resultant bone map
		static void HK_CALL computeBonePairingFromNames( 
			const hkObjectArray< hkString > &ltag, 
			const hkObjectArray< hkString > &rtag,
			const hkaSkeleton* skeleton,
			hkInt16 *bonePairMap );
#endif
		// MIRRORING
		
		/// Compute the new mirrored tranform for the paired bone of bone bi.  This function is
		/// typically called by the hkaMirroredSkeletalAnimation class
		/// \param QInOut Contains the transform for bone bi, overwritten with new paired bj transform
		void mirrorPairedBone( hkQsTransform &QInOut, hkInt16 bi, hkBool additive ) const;

		/// Compute a new mirrored transform for extracted motion of the root
		/// typically called by the hkaMirroredSkeletalAnimation class
		/// \param QInOut Contains the original delta transform, overwritten by the mirrored transform
		/// \param additive True if this animation is additive
		void mirrorExtractedMotion( hkQsTransform &QInOut, hkBool additive ) const;

		// NOT FOR USER USE Accessors for static method hkaMirroredSkeletalAnimation::samplePartialWithDataChunks
		inline hkInt16* getBonePairMap() const { return m_bonePairMap; }
		inline hkBool* getBoneIsNubArray() const { return m_boneIsNub; }
		inline const hkaSkeleton* getSkeleton() const { return m_skeleton; }
		inline void reconstructFromDMAdData(hkInt16* bonePairMap, hkBool* boneIsNubArray, const hkaSkeleton* skeleton) 
		{
			m_bonePairMap = bonePairMap;
			m_boneIsNub = boneIsNubArray;
			m_skeleton = skeleton;
		}

	private:

		/// Creates a mirroring transform
		/// \param v Axis to mirror about
		/// \return A mirroring transform about axis v
		hkConvertCS createMirroringCS( const hkVector4 &v ) const;

		/// Mirrors a bone transform about the chosen axis
		/// \param QInOut Tranform to mirror
		/// \param T Mirroring transform
		/// \return Mirrored version of Q
		static void HK_CALL mirrorTransform( hkQsTransform& QInOut, const hkConvertCS& T );

		/// Mirrors a bone transform about the chosen axis with an offset transform
		/// \param QInOut TransformToMirror
		/// \param T Mirroring transform
		/// \param R Offset rotation
		static void HK_CALL mirrorTransform( hkQsTransform& QInOut, const hkConvertCS& T, const hkQsTransform& R );

		/// Creates the proper mirroring transform for bone bi
		/// \param Q Input transform (current transform of paired bone)
		/// \param bi The bone to produce a mirroring transform for
		hkQsTransform mirrorTransform( hkQsTransform& QInOut, hkInt16 bi ) const;

		/// Updates all mirroring transforms
		void computeMirroringTransforms();

		/// Computes which bones are nubs
		void computeBoneChildInfo();

		/// Bone pairing information
		hkInt16 *m_bonePairMap;

		/// Keep track of which bones are nubs (those without a child)
		hkBool *m_boneIsNub;

		/// Skeleton, used to get the parent bone information
		const hkaSkeleton *m_skeleton;

		// Required Options
		/// Local axis of reflection
		hkVector4 m_axis;

		// Optional Options
		hkQsTransform m_rootOrientation;
		hkQsTransform m_childOrientation;
		hkQsTransform m_nubOrientation;
		hkBool m_mixed;

		// Values cached for efficiency
		hkConvertCS m_mirrorCS;
		hkConvertCS m_rootCS;
		hkConvertCS m_childCS;
		hkConvertCS m_nubCS;
		hkQuaternion m_rotateSide;
};

#endif // HKANIMATION_ANIMATION_HKMIRROREDSKELETON_H

/*
* Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20080529)
*
* Confidential Information of Havok.  (C) Copyright 1999-2008 
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
*
* Use of this software for evaluation purposes is subject to and indicates 
* acceptance of the End User licence Agreement for this product. A copy of 
* the license is included with this software and is also available at
* www.havok.com/tryhavok
*
*/
