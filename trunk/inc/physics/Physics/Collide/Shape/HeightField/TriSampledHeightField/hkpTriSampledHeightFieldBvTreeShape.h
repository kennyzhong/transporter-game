/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2008 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_TRI_SAMPLED_HEIGHTFIELD_BVTREE_SHAPE
#define HK_TRI_SAMPLED_HEIGHTFIELD_BVTREE_SHAPE

#include <Physics/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>

extern const hkClass hkpTriSampledHeightFieldBvTreeShapeClass;

class hkpTriSampledHeightFieldCollection;

/// This shape must be used in conjunction with the hkpTriSampledHeightFieldCollection. Please see the documentation for
/// the hkpTriSampledHeightFieldCollection for details on what the classes do.
class hkpTriSampledHeightFieldBvTreeShape : public hkpBvTreeShape
{
	public:

		HK_DECLARE_REFLECTION();

			/// The constructor takes a pointer to hkpTriSampledHeightFieldCollection.
			/// This class is designed to work together with the hkpTriSampledHeightFieldCollection.
			/// The value "doAabbRejection" can be used to turn off the aabb rejection test.
			/// The queryAabb() method (which will be used by agents/user queries using 
			/// the hkpBvTreeShape interface) uses its projection onto the heightfield grid
			/// space to determine what triangles to return.
			/// To ensure that the resulting triangles are at least close to the
			/// AABB in the direction of projection (that the AABB is not hovering completely
			/// above or below all points in that area of heightfield), this test checks that it
			/// at least overlaps the single AABB bounding all those triangles.
			/// By default it is true. Setting it to false disables the test,
			/// which may give a small speedup for flat heightfields.
		hkpTriSampledHeightFieldBvTreeShape( const hkpTriSampledHeightFieldCollection* c, hkBool doAabbRejection = true );

#ifndef HK_PLATFORM_SPU
		hkpTriSampledHeightFieldBvTreeShape( hkFinishLoadedObjectFlag flag ) : hkpBvTreeShape(flag), m_childContainer(flag) { m_type = HK_SHAPE_BV_TREE; }
#endif

			/// Returns a struct of function pointers needed by the SPU
		static void HK_CALL registerSimulationFunctions( ShapeFuncs& sf );

		//
		// hkpBvTreeShape interface
		//

			/// Returns the hkpShapeKey for all shapes in the hkpShapeCollection that intersect with the obb (defined by obbTransform and obbExtent).
			/// This implementation simply bounds the OBB by an AABB and uses the queryAabb() method. Thus it is not as
			/// accurate as it could be if using a more sophisticated algorithm, and can return triangles completely outside the OBB.
		virtual void queryObb( const hkTransform& obbTransform, const hkVector4& obbExtent, hkReal tolerance, hkArray< hkpShapeKey >& hits ) const;

			/// Returns the hkpShapeKey for all shapes in the hkpShapeCollection that intersect with the AABB.
		virtual void queryAabb( const hkAabb& aabb, hkArray<hkpShapeKey>& hits ) const;

			// hkpBvTreeShape interface implementation.
		virtual hkUint32 queryAabb( const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys ) const;
			
			// hkpBvTreeShape interface implementation.
		const hkpShapeContainer* getContainer() const;

		//
		// hkpShape interface
		//

			// hkpShape interface implementation.
		HKP_SHAPE_VIRTUAL void getAabbImpl( HKP_SHAPE_VIRTUAL_THIS const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) HKP_SHAPE_VIRTUAL_CONST;

			// hkpShape interface implementation.
		virtual hkBool castRayImpl( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output ) const;

			// hkpShape interface implementation.
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

			// hkpShape interface implementation.
		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;

			// Retrieves the shape collection, DMAing from PPU if necessary
		const hkpTriSampledHeightFieldCollection* getShapeCollection() const;

	protected:
		
		class hkpSingleShapeContainer m_childContainer;
		mutable int	m_childSize;	//+nosave
		
		hkBool m_wantAabbRejectionTest;
};


#endif // HK_TRI_SAMPLED_HEIGHTFIELD_BVTREE_SHAPE

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
