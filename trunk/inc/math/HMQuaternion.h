#ifndef HYPERMATH_QUATERNION
#define HYPERMATH_QUATERNION
#include "math/HMath.h"

namespace hmath
{
	class quat
	{
	public : union
			 {
				 struct {
					 f32 w, x, y, z;
				 };
				 f32 val[4];
			 };

			inline quat( f32 fW = 1.0, f32 fX = 0.0, f32 fY = 0.0, f32 fZ = 0.0);
			inline quat(const quat& rkQ);
			inline quat(const m3& rot);
			inline quat(const rad& rfAngle, const v3& rkAxis);
			inline quat(const v3& xaxis, const v3& yaxis, const v3& zaxis);
			inline quat(const v3* akAxis);
			inline quat(f32* valptr);
			void FromRotationMatrix (const m3& kRot);
			void ToRotationMatrix (m3& kRot) const;
			void FromAngleAxis (const rad& rfAngle, const v3& rkAxis);
			void ToAngleAxis (rad& rfAngle, v3& rkAxis) const;
			void ToAngleAxis (deg& dAngle, v3& rkAxis) const;
			void FromAxes (const v3* akAxis);
			void FromAxes (const v3& xAxis, const v3& yAxis, const v3& zAxis);
			void ToAxes (v3* akAxis) const;
			void ToAxes (v3& xAxis, v3& yAxis, v3& zAxis) const;
			void FromEuler(rad psi,rad theta,rad phi);
			v3 xAxis(void) const;
			v3 yAxis(void) const;
			v3 zAxis(void) const;

			v3 operator*  (const v3& rkVector) const;
			inline quat& operator=  (const quat& rkQ);
			inline quat  operator+  (const quat& rkQ) const;
			inline quat  operator-  (const quat& rkQ) const;
			inline quat  operator*  (const quat& rkQ) const;
			inline quat  operator*  (f32 fScalar) const;			
			inline quat  operator-  () const;
			inline bit   operator== (const quat& rhs) const;
			inline bit   operator!= (const quat& rhs) const;

			inline f32 dot (const quat& rkQ) const;
			inline f32 sqlen () const;
			inline f32 len () const; 
			inline f32 norm(void); 
			inline quat inv () const; 
			inline quat uinv () const;
			quat exp () const;
			quat log () const;

			inline rad getRoll(void) const;
			inline rad getPitch(void) const;
			inline rad getYaw(void) const;		
			inline bit equals(const quat& rhs, const rad& tolerance) const;

			static const quat zero;
			static const quat id;
	};

	//====================================================================================	

	quat::quat ( f32 fW,f32 fX, f32 fY, f32 fZ)
	{
		w = fW;
		x = fX;
		y = fY;
		z = fZ;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat::quat (const quat& rkQ)
	{
		w = rkQ.w;
		x = rkQ.x;
		y = rkQ.y;
		z = rkQ.z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat::quat(const m3& rot)
	{
		this->FromRotationMatrix(rot);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat::quat(const rad& rfAngle, const v3& rkAxis)
	{
		this->FromAngleAxis(rfAngle, rkAxis);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat::quat(const v3& xaxis, const v3& yaxis, const v3& zaxis)
	{
		this->FromAxes(xaxis, yaxis, zaxis);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat::quat(const v3* akAxis)
	{
		this->FromAxes(akAxis);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat::quat(f32* valptr)
	{
		memcpy(val, valptr, sizeof(f32)*4);
	}		

	//————————————————————————————————————————————————————————————————————————————————————————

	quat& quat::operator= (const quat& rkQ)
	{
		w = rkQ.w;
		x = rkQ.x;
		y = rkQ.y;
		z = rkQ.z;
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat quat::operator+ (const quat& rkQ) const
	{
		return quat(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat quat::operator- (const quat& rkQ) const
	{
		return quat(w-rkQ.w,x-rkQ.x,y-rkQ.y,z-rkQ.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat quat::operator* (const quat& rkQ) const
	{
		return quat ( w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
					  w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
					  w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
					  w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat quat::operator* (f32 fScalar) const
	{
		return quat(fScalar*w,fScalar*x,fScalar*y,fScalar*z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat quat::operator- () const
	{
		return quat(-w,-x,-y,-z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit quat::operator== (const quat& rhs) const
	{
		return (rhs.x == x) && (rhs.y == y) && (rhs.z == z) && (rhs.w == w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit quat::operator!= (const quat& rhs) const
	{
		return !operator==(rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad quat::getRoll(void) const
	{
		return rad(atan2(2*(x*y + w*z), w*w + x*x - y*y - z*z));
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad quat::getPitch(void) const
	{
		return rad(atan2(2*(y*z + w*x), w*w - x*x - y*y + z*z));
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad quat::getYaw(void) const
	{
		return rad(asin(-2*(x*z - w*y)));
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 quat::dot (const quat& rkQ) const
	{
		return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 quat::sqlen () const
	{
		return w*w+x*x+y*y+z*z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 quat::len () const
	{
		//return w*w+x*x+y*y+z*z;
		return sqrt(w*w+x*x+y*y+z*z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 quat::norm(void)
	{
		f32 l = len();
		f32 factor = 1.0f / l;
		*this = *this * factor;
		return l;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat quat::inv () const
	{
		f32 fNorm = sqlen();
		if ( fNorm > 0.0 )
		{
			f32 fInvNorm = f32(1.0)/fNorm;
			return quat( w*fInvNorm, -x*fInvNorm, -y*fInvNorm, -z*fInvNorm );
		}
		else
		{
			return zero;
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat quat::uinv () const
	{
		return quat(w,-x,-y,-z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit quat::equals(const quat& rhs, const rad& tolerance) const
	{
		rad angle = rad(acos(dot(rhs)));

		return (fabs(angle.asRad()) <= tolerance.asRad()) ||
			   f32_equal(angle.asRad(), f32(PI), tolerance.asRad());
	}

};

#endif
