/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2008 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HKANIMATION_ANIMATION_HKSKELETALANIMATION_XML_H
#define HKANIMATION_ANIMATION_HKSKELETALANIMATION_XML_H

#include <Animation/Animation/Animation/hkaAnnotationTrack.h>
#include <Animation/Animation/Motion/hkaAnimatedReferenceFrame.h>

class hkaChunkCache;

/// hkaSkeletalAnimation meta information
extern const class hkClass hkaSkeletalAnimationClass;

/// The base class for animation storage.
/// All skeletal animation have a finite period specified in seconds.
/// The interface implies that each implementation can be sampled continuously over the period.
class hkaSkeletalAnimation : public hkReferencedObject
{
	public:
	
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_UNCOMPRESSED );
		HK_DECLARE_REFLECTION();

			/// Default constructor
		inline hkaSkeletalAnimation();

			/// Type information 
		enum AnimationType {

				///
			HK_UNKNOWN_ANIMATION = 0,

				/// Interleaved
			HK_INTERLEAVED_ANIMATION,
				/// Delta compressed
			HK_DELTA_COMPRESSED_ANIMATION,
				/// Wavelet compressed
			HK_WAVELET_COMPRESSED_ANIMATION,
				/// Mirrored
			HK_MIRRORED_ANIMATION,
				/// Spline
			HK_SPLINE_COMPRESSED_ANIMATION
		};

		
			/// Get AnimationType.
		HK_FORCE_INLINE hkaSkeletalAnimation::AnimationType getType() const;

			/// Get the pose at a given time
		virtual void sampleTracks(hkReal time, hkQsTransform* transformTracksOut, hkReal* floatTracksOut, hkaChunkCache* cache) const = 0;
		
			/// Get a subset of the the first 'maxNumTracks' transform tracks (all tracks from 0 to maxNumTracks-1 inclusive), and the first 'maxNumFloatTracks' float tracks of a pose at a given time.
		virtual void samplePartialTracks(hkReal time,
										 hkUint32 maxNumTransformTracks, hkQsTransform* transformTracksOut,
										 hkUint32 maxNumFloatTracks, hkReal* floatTracksOut,
										 hkaChunkCache* cache) const;

			/// Sample a single animation track.
		inline void sampleSingleTransformTrack( hkReal time, hkInt16 track, hkQsTransform* transformOut ) const;

			/// Sample a single floating track.
		inline void sampleSingleFloatTrack( hkReal time, hkInt16 track, hkReal* out ) const;

			/// Sample individual animation tracks.
		virtual void sampleIndividualTransformTracks( hkReal time, const hkInt16* tracks, hkUint32 numTracks, hkQsTransform* transformOut ) const = 0;

			/// Sample a individual floating tracks.
		virtual void sampleIndividualFloatTracks( hkReal time, const hkInt16* tracks, hkUint32 numTracks, hkReal* out ) const = 0;



			/// Returns the number of original samples / frames of animation.
		virtual int getNumOriginalFrames() const = 0;

			/*
			* Block decompression
			*/

			// INTERNAL
		struct DataChunk
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_RUNTIME, DataChunk);

			const void* m_data;
			hkUint32	m_size;
			hkUint8     m_offset; // the amount we need to add to the data to bring it to the "real" data
#if !defined(HK_PLATFORM_SPU)
			DataChunk() : m_data(HK_NULL), m_size(0), m_offset(0) {}	// Only exisits on PPU for error checking
#endif
			inline void setDataChunkWith16ByteAlignmentCorrection(const void* dataPtrIn, int numBytes)
			{
				hkUlong actualStart = (hkUlong) dataPtrIn;
				m_offset = hkUint8(actualStart & 0xF);
				actualStart &= 0xFFFFFFF0;
				m_data = (const void*) actualStart;

				m_size = numBytes;
				m_size += m_offset;
				m_size = HK_NEXT_MULTIPLE_OF(16, m_size);
			}

			inline void init()
			{
				m_data = HK_NULL;
				m_size = 0;
				m_offset = 0;
			}
		};

			/// Return the number of chunks of data required to sample a pose at time t
		virtual int getNumDataChunks(hkReal time) const;

			/// Return the chunks of data required to sample a pose at time t
		virtual void getDataChunks(hkReal time, DataChunk* dataChunks, int m_numDataChunks) const;

			/// Return the maximum total size of all combined chunk data which could be returned by getDataChunks for this animation.
		virtual int getMaxSizeOfCombinedDataChunks() const;

			/// Returns the motion stored (previously extracted from the animation) at time t.
			/// This motion represents the absolute offset from the start of the animation.
		virtual void getExtractedMotionReferenceFrame(hkReal time, hkQsTransform& motionOut) const;
	
			/// Returns the change in reference frame between two times for extracted motion.
		virtual void getExtractedMotionDeltaReferenceFrame( hkReal time, hkReal nextTime, int loops, hkQsTransform& deltaMotionOut ) const;

			/// Test for presence of extracted motion
		hkBool hasExtractedMotion() const;

			/// Set the extracted motion of this animation
		void setExtractedMotion( const hkaAnimatedReferenceFrame* extractedMotion );
				
			/// Get the frame/sample index and delta between frames. So 0 <= frameOut < getNumOriginalFrames() and 0 <= delta < 1.0
		inline void getFrameAndDelta(hkReal time, hkUint32& frameOut, hkReal& deltaOut) const;


	protected:
		
			/// AnimationType.
		hkEnum<hkaSkeletalAnimation::AnimationType, hkInt32> m_type;
	
	public:

			/// The length of the animation cycle in seconds
		hkReal m_duration;
		
			/// The number of bone tracks to be animated.
		int m_numberOfTransformTracks;

			/// The number of float tracks to be animated
		int m_numberOfFloatTracks;

	protected:
			/// An hkaAnimatedReferenceFrame instance containing extracted motion.
		const hkaAnimatedReferenceFrame* m_extractedMotion;
		
	public:
			/// The animation tracks associated with this skeletal animation.
		hkaAnnotationTrack** m_annotationTracks;
			/// Size of m_annotationTracks array.
		hkInt32 m_numAnnotationTracks;
	
			// Constructor for initialisation of vtable fixup
		HK_FORCE_INLINE hkaSkeletalAnimation( hkFinishLoadedObjectFlag flag ) : hkReferencedObject(flag) {}
};

#include <Animation/Animation/Animation/hkaSkeletalAnimation.inl>

#endif // HKANIMATION_ANIMATION_HKSKELETALANIMATION_XML_H

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
