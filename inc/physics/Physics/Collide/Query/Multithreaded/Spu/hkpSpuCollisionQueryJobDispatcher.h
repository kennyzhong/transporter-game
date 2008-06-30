/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2008 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_SPU_COLLIDE_QUERY_DISPATCH_JOBS_H
#define HK_SPU_COLLIDE_QUERY_DISPATCH_JOBS_H


#include <Common/Base/Thread/JobQueue/hkJobQueue.h>


class hkpWorld;
struct hkpCollisionQueryJobData;


hkJobQueue::JobStatus HK_CALL hkSpuProcessNextCollisionQueryJob(	  hkJobQueue&				queue, 
																const hkpCollisionQueryJobData*	jobData, 
																	  hkJobQueue::WaitStatus	waitStatusIn);


#endif // HK_SPU_COLLIDE_QUERY_DISPATCH_JOBS_H

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