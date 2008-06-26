#include "math/HMath.h"

namespace hmath
{
	const v3_64 v3_64::zero( 0, 0, 0 );
	const v3_64 v3_64::unitX( 1, 0, 0 );
	const v3_64 v3_64::unitY( 0, 1, 0 );
	const v3_64 v3_64::unitZ( 0, 0, 1 );
	const v3_64 v3_64::neg_unitX( -1,  0,  0 );
	const v3_64 v3_64::neg_unitY(  0, -1,  0 );
	const v3_64 v3_64::neg_unitZ(  0,  0, -1 );
	const v3_64 v3_64::unit(1, 1, 1);

	quat v3_64::getRotationTo(const v3_64& dest, const v3_64& fallbackAxis) const
	{
		// Based on Stan Melax's article in Game Programming Gems
		quat q;
		// Copy, since cannot modify local
		v3_64 v0 = *this;
		v3_64 v1 = dest;
		v0.norm();
		v1.norm();

		v3_64 c = v0.cross(v1);

		f64 d = v0.dot(v1);
		// If dot == 1, vectors are the same
		if (d >= 1.0f)
		{
			return quat::id;
		}
		f64 s = sqrt( (1+d)*2 );
		if (s < 1e-6f)
		{
			if (fallbackAxis != v3_64::zero)
			{
				// rotate 180 degrees about the fallback axis
				q.FromAngleAxis(rad((f32)PI), v3((f32)fallbackAxis.x,(f32)fallbackAxis.y,(f32)fallbackAxis.z));
			}
			else
			{
				// Generate an axis
				v3_64 axis = v3_64::unitX.cross(*this);
				if (axis.iszerolen()) // pick another if colinear
					axis = v3_64::unitY.cross(*this);
				axis.norm();
				q.FromAngleAxis(rad((f32)PI), v3((f32)axis.x,(f32)axis.y,(f32)axis.z));
			}
		}
		else
		{
			f64 invs = 1 / s;

			q.x = f32(c.x * invs);
			q.y = f32(c.y * invs);
			q.z = f32(c.z * invs);
			q.w = f32(s * 0.5);
		}
		return q;
	}

};