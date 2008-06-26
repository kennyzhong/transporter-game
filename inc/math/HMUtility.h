#ifndef HYPERMATH_UTILITY
#define HYPERMATH_UTILITY
#include "math/HMath.h"

namespace hmath
{
	extern f32 InvSqrt(f32 fValue);
	extern bit f32_equal( f32 a, f32 b, f32 tolerance );
	extern f64 Deg2Rad(f64 degrees) ;
	extern f64 Rad2Deg(f64 radians) ;
	extern f32 UnitRandom ();
	extern f64 safeASIN(f64 x);
	extern f64 ClampUnity( f64 x );
	extern void HprToMatrix( m4& rotation, const v3_64& hpr );
	extern void MatrixToHpr( v3_64& hpr, const m4& rotation );
	extern bit IsFinite(const f64 value);
	extern void Clamp(f64& x, const f64 low, const f64 high);
	extern void Clamp(u32& x, const u32 low, const u32 high);
	extern void Clamp(i32& x, const i32 low, const i32 high);
	extern void EulersToMatrix(m4& dst, rad64 psi, rad64 theta, rad64 phi);
	extern void MatrixToEulers(const m4& src, f64& psi, f64& theta, f64& phi);
/*
	bit v3_directionEquals(v3& v,const v3& rhs,const rad& tolerance);

	bit v3_positionEquals(v3& v,const v3& rhs, f32 tolerance);

	v3 v3_randomDeviant(v3& v,const rad& angle,const v3& up );

	quat v3_getRotationTo(v3& v,const v3& dest,const v3& fallbackAxis);
	*/
}
#endif
