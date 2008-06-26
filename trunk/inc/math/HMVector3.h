#ifndef HYPERMATH_VECTOR3
#define HYPERMATH_VECTOR3
#include "math/HMath.h"

namespace hmath
{
	class v3
	{
	public : 
		union 
		{
			struct 
			{
				f32 x; 
				f32 y; 
				f32 z;
			};
			f32 val[3];
		};
		inline v3(){};
		inline v3( const f32 fX, const f32 fY, const f32 fZ );
		inline explicit v3( const i32 fX, const i32 fY, const i32 fZ );
		inline explicit v3( const f32 vec[3] );
		inline explicit v3( const i32 vec[3] );
		inline explicit v3( f32* const r );
		inline explicit v3( const f32 scaler );
		inline v3( const v3& vec );

		inline f32 operator [] ( const size_t i ) const;
		inline f32& operator [] ( const size_t i );
		inline v3& operator = ( const v3& vec );
		inline v3& operator = ( const f32 scaler );
		inline bit operator == ( const v3& vec ) const;
		inline bit operator != ( const v3& vec ) const;
		inline v3 operator + ( const v3& vec ) const;
		inline v3 operator - ( const v3& vec ) const;
		inline v3 operator * ( const f32 scalar ) const;
		inline v3 operator * ( const v3& rhs) const;
		inline v3 operator / ( const f32 scalar ) const;
		inline v3 operator / ( const v3& rhs) const;
		inline v3 operator - () const;
		inline v3 operator + () const;
		inline v3& operator += ( const v3& vec );
		inline v3& operator += ( const f32 scalar );
		inline v3& operator -= ( const v3& vec );
		inline v3& operator -= ( const f32 scalar );
		inline v3& operator *= ( const f32 scalar );
		inline v3& operator *= ( const v3& vec );
		inline v3& operator /= ( const f32 scalar );
		inline v3& operator /= ( const v3& vec );
		inline bit operator < ( const v3& rhs ) const;
		inline bit operator > ( const v3& rhs ) const;
		inline f32 len () const;
		inline f32 sqlen () const;
		inline f32 dot(const v3& vec) const;
		inline f32 norm();
		inline v3 cross( const v3& vec ) const;
		inline v3 reflect(const v3& normal) const;
		inline bit iszerolen(void) const;
		inline v3 up(void) const;
		inline v3 mid( const v3& vec ) const;
		inline void floor( const v3& cmp );
		inline void ceil( const v3& cmp );

		static const v3 zero;
		static const v3 unitX;
		static const v3 unitY;
		static const v3 unitZ;
		static const v3 neg_unitX;
		static const v3 neg_unitY;
		static const v3 neg_unitZ;
		static const v3 unit;

		quat getRotationTo(const v3& dest, const v3& fallbackAxis = v3::zero) const;
	};

	//————————————————————————————————————————————————————————————————————————————————————————

	v3::v3( const f32 fX, const f32 fY, const f32 fZ )
		: x( fX ), y( fY ), z( fZ )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3::v3( const i32 fX, const i32 fY, const i32 fZ )
	{
		x = f32(fX);
		y = f32(fY);
		z = f32(fZ);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3::v3( const f32 vec[3] )
		: x( vec[0] ), y( vec[1] ), z( vec[2] )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3::v3( const i32 vec[3] )
	{
		x = (f32)vec[0];
		y = (f32)vec[1];
		z = (f32)vec[2];
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3::v3( f32* const r )
		: x( r[0] ), y( r[1] ), z( r[2] )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3::v3( const f32 scaler )
		: x( scaler ), y( scaler ), z( scaler )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3::v3( const v3& vec )
		: x( vec.x ), y( vec.y ), z( vec.z )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v3::operator [] ( const size_t i ) const
	{
		//	assert( i < 3 );
		return *(&x+i);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32& v3::operator [] ( const size_t i )
	{
		//	assert( i < 3 );
		return *(&x+i);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3& v3::operator = ( const v3& vec )
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3& v3::operator = ( const f32 scaler )
	{
		x = scaler;
		y = scaler;
		z = scaler;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v3::operator == ( const v3& vec ) const
	{
		return ( x == vec.x && y == vec.y && z == vec.z );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v3::operator != ( const v3& vec ) const
	{
		return ( x != vec.x || y != vec.y || z != vec.z );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::operator + ( const v3& vec ) const
	{
		return v3(x + vec.x,y + vec.y,z + vec.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::operator - ( const v3& vec ) const
	{
		return v3(x - vec.x,y - vec.y,z - vec.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::operator * ( const f32 scalar ) const
	{
		return v3(x * scalar,y * scalar,z * scalar);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::operator * ( const v3& rhs) const
	{
		return v3(x * rhs.x,y * rhs.y, z * rhs.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::operator / ( const f32 scalar ) const
	{
		assert( scalar != 0.0 );

		f32 fInv = f32(1.0) / scalar;

		return v3( x * fInv,y * fInv,z * fInv);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::operator / ( const v3& rhs) const
	{
		return v3(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::operator + () const
	{
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::operator - () const
	{
		return v3(-x, -y, -z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v3 operator * ( const f32 scalar, const v3& vec ) 
	{
		return v3( scalar * vec.x, scalar * vec.y, scalar * vec.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v3 operator + (const v3& lhs, const f32 rhs) 
	{
		return v3( lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v3 operator + (const f32 lhs, const v3& rhs) 
	{
		return v3( lhs + rhs.x, lhs + rhs.y,lhs + rhs.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v3 operator - (const v3& lhs, const f32 rhs) 
	{
		return v3( lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v3 operator - (const f32 lhs, const v3& rhs) 
	{
		return v3(lhs - rhs.x,lhs - rhs.y,lhs - rhs.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————


	v3& v3::operator += ( const v3& vec )
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3& v3::operator += ( const f32 scalar )
	{
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3& v3::operator -= ( const v3& vec )
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3& v3::operator -= ( const f32 scalar )
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3& v3::operator *= ( const f32 scalar )
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3& v3::operator *= ( const v3& vec )
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3& v3::operator /= ( const f32 scalar )
	{
		assert( scalar != 0.0 );

		f32 fInv = f32(1.0) / scalar;

		x *= fInv;
		y *= fInv;
		z *= fInv;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3& v3::operator /= ( const v3& vec )
	{
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v3::operator < ( const v3& rhs ) const
	{
		if( x < rhs.x && y < rhs.y && z < rhs.z )
			return true;
		return false;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v3::operator > ( const v3& rhs ) const
	{
		if( x > rhs.x && y > rhs.y && z > rhs.z )
			return true;
		return false;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v3::len () const
	{
		return sqrt( x * x + y * y + z * z );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v3::sqlen () const
	{
		return x * x + y * y + z * z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v3::dot(const v3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v3::norm()
	{
		f32 fLength = len();

		if ( fLength > 1e-08 )
		{
			f32 fInvLength = f32(1.0) / fLength;
			x *= fInvLength;
			y *= fInvLength;
			z *= fInvLength;
		}

		return fLength;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::cross( const v3& vec ) const
	{
		return v3(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::reflect(const v3& normal) const
	{
		return v3( *this - ( 2 * this->dot(normal) * normal ) );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v3::iszerolen(void) const
	{
		f32 sqlen = (x * x) + (y * y) + (z * z);
		return (sqlen < (1e-06 * 1e-06));

	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::up(void) const
	{
		static const f32 fSquareZero = f32(1e-06 * 1e-06);

		v3 perp = this->cross( v3::unitX );

		if( perp.sqlen() < fSquareZero )
		{
			perp = this->cross( v3::unitY );
		}

		return perp;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 v3::mid( const v3& vec ) const
	{
		return v3( ( x + vec.x ) * f32(0.5),
				   ( y + vec.y ) * f32(0.5),
				   ( z + vec.z ) * f32(0.5) );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void v3::floor( const v3& cmp )
	{
		if( cmp.x < x ) x = cmp.x;
		if( cmp.y < y ) y = cmp.y;
		if( cmp.z < z ) z = cmp.z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void v3::ceil( const v3& cmp )
	{
		if( cmp.x > x ) x = cmp.x;
		if( cmp.y > y ) y = cmp.y;
		if( cmp.z > z ) z = cmp.z;
	}
}
#endif
