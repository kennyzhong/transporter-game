#include "math/HMath.h"

namespace hmath
{
const v3 v3::zero( 0, 0, 0 );
const v3 v3::unitX( 1, 0, 0 );
const v3 v3::unitY( 0, 1, 0 );
const v3 v3::unitZ( 0, 0, 1 );
const v3 v3::neg_unitX( -1,  0,  0 );
const v3 v3::neg_unitY(  0, -1,  0 );
const v3 v3::neg_unitZ(  0,  0, -1 );
const v3 v3::unit(1, 1, 1);

quat v3::getRotationTo(const v3& dest, const v3& fallbackAxis) const
{
	// Based on Stan Melax's article in Game Programming Gems
	quat q;
	// Copy, since cannot modify local
	v3 v0 = *this;
	v3 v1 = dest;
	v0.norm();
	v1.norm();

	v3 c = v0.cross(v1);

	f32 d = v0.dot(v1);
	// If dot == 1, vectors are the same
	if (d >= 1.0f)
	{
		return quat::id;
	}
	f32 s = sqrt( (1+d)*2 );
	if (s < 1e-6f)
	{
		if (fallbackAxis != v3::zero)
		{
			// rotate 180 degrees about the fallback axis
			q.FromAngleAxis(rad((f32)PI), fallbackAxis);
		}
		else
		{
			// Generate an axis
			v3 axis = v3::unitX.cross(*this);
			if (axis.iszerolen()) // pick another if colinear
				axis = v3::unitY.cross(*this);
			axis.norm();
			q.FromAngleAxis(rad((f32)PI), axis);
		}
	}
	else
	{
		f32 invs = 1 / s;

		q.x = c.x * invs;
		q.y = c.y * invs;
		q.z = c.z * invs;
		q.w = s * (f32)0.5;
	}
	return q;
}

};