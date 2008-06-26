#ifndef HYPERMATH_VECTOR4
#define HYPERMATH_VECTOR4
#include "math/HMath.h"

namespace hmath
{
	class v4
	{
	public : 
		union 
		{
			struct 
			{
				f32 x; 
				f32 y; 
				f32 z;
				f32 w;
			};
			f32 val[4];
		};
		inline v4(){};
		inline v4( const f32 fX, const f32 fY, const f32 fZ, const f32 fW );
		inline explicit v4( const i32 fX, const i32 fY, const i32 fZ, const i32 fW );
		inline explicit v4( const f32 vec[4] );
		inline explicit v4( const i32 vec[4] );
		inline explicit v4( f32* const r );
		inline explicit v4( const f32 scaler );
		inline v4( const v4& vec );

		inline f32 operator [] ( const size_t i ) const;
		inline f32& operator [] ( const size_t i );
		inline v4& operator = ( const v4& vec );
		inline v4& operator = ( const f32 scaler );
		inline bit operator == ( const v4& vec ) const;
		inline bit operator != ( const v4& vec ) const;
		inline v4 operator + ( const v4& vec ) const;
		inline v4 operator - ( const v4& vec ) const;
		inline v4 operator * ( const f32 scalar ) const;
		inline v4 operator * ( const v4& rhs) const;
		inline v4 operator / ( const f32 scalar ) const;
		inline v4 operator / ( const v4& rhs) const;
		inline v4 operator - () const;
		inline v4 operator + () const;
		inline v4& operator += ( const v4& vec );
		inline v4& operator += ( const f32 scalar );
		inline v4& operator -= ( const v4& vec );
		inline v4& operator -= ( const f32 scalar );
		inline v4& operator *= ( const f32 scalar );
		inline v4& operator *= ( const v4& vec );
		inline v4& operator /= ( const f32 scalar );
		inline v4& operator /= ( const v4& vec );
		inline bit operator < ( const v4& rhs ) const;
		inline bit operator > ( const v4& rhs ) const;
		inline f32 len () const;
		inline f32 sqlen () const;
		inline f32 dot(const v4& vec) const;
		inline f32 norm();
		inline v4 cross( const v4& vec ) const;
		inline v4 reflect(const v4& normal) const;
		inline bit iszerolen(void) const;
		inline v4 up(void) const;
		inline v4 mid( const v4& vec ) const;
		inline void floor( const v4& cmp );
		inline void ceil( const v4& cmp );

		static const v4 zero;
		static const v4 unitX;
		static const v4 unitY;
		static const v4 unitZ;
		static const v4 unitW;
		static const v4 neg_unitX;
		static const v4 neg_unitY;
		static const v4 neg_unitZ;
		static const v4 neg_unitW;
		static const v4 unit;

		quat getRotationTo(const v4& dest, const v4& fallbackAxis = v4::zero) const;
	};

	//————————————————————————————————————————————————————————————————————————————————————————

	v4::v4( const f32 fX, const f32 fY, const f32 fZ, const f32 fW )
		: x( fX ), y( fY ), z( fZ ), w( fW )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4::v4( const i32 fX, const i32 fY, const i32 fZ, const i32 fW )
	{
		x = f32(fX);
		y = f32(fY);
		z = f32(fZ);
		w = f32(fW);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4::v4( const f32 vec[4] )
		: x( vec[0] ), y( vec[1] ), z( vec[2] ), w( vec[3] )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4::v4( const i32 vec[4] )
	{
		x = (f32)vec[0];
		y = (f32)vec[1];
		z = (f32)vec[2];
		w = (f32)vec[3];
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4::v4( f32* const r )
		: x( r[0] ), y( r[1] ), z( r[2] ), w( r[3] )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4::v4( const f32 scaler )
		: x( scaler ), y( scaler ), z( scaler ), w( scaler )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4::v4( const v4& vec )
		: x( vec.x ), y( vec.y ), z( vec.z ), w( vec.w )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v4::operator [] ( const size_t i ) const
	{
		//	assert( i < 4 );
		return *(&x+i);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32& v4::operator [] ( const size_t i )
	{
		//	assert( i < 4 );
		return *(&x+i);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4& v4::operator = ( const v4& vec )
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4& v4::operator = ( const f32 scaler )
	{
		x = scaler;
		y = scaler;
		z = scaler;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v4::operator == ( const v4& vec ) const
	{
		return ( x == vec.x && y == vec.y && z == vec.z && w == vec.w );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v4::operator != ( const v4& vec ) const
	{
		return ( x != vec.x || y != vec.y || z != vec.z || w != vec.w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::operator + ( const v4& vec ) const
	{
		return v4(x + vec.x,y + vec.y,z + vec.z,w + vec.w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::operator - ( const v4& vec ) const
	{
		return v4(x - vec.x,y - vec.y,z - vec.z,w - vec.w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::operator * ( const f32 scalar ) const
	{
		return v4(x * scalar,y * scalar,z * scalar,w * scalar);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::operator * ( const v4& rhs) const
	{
		return v4(x * rhs.x,y * rhs.y, z * rhs.z,w * rhs.w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::operator / ( const f32 scalar ) const
	{
		assert( scalar != 0.0 );

		f32 fInv = f32(1.0) / scalar;

		return v4( x * fInv,y * fInv,z * fInv,w * fInv);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::operator / ( const v4& rhs) const
	{
		return v4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::operator + () const
	{
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::operator - () const
	{
		return v4(-x, -y, -z, -w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v4 operator * ( const f32 scalar, const v4& vec ) 
	{
		return v4( scalar * vec.x, scalar * vec.y, scalar * vec.z, scalar * vec.w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v4 operator + (const v4& lhs, const f32 rhs) 
	{
		return v4( lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v4 operator + (const f32 lhs, const v4& rhs) 
	{
		return v4( lhs + rhs.x, lhs + rhs.y,lhs + rhs.z, lhs + rhs.w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v4 operator - (const v4& lhs, const f32 rhs) 
	{
		return v4( lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v4 operator - (const f32 lhs, const v4& rhs) 
	{
		return v4(lhs - rhs.x,lhs - rhs.y,lhs - rhs.z, lhs - rhs.w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————


	v4& v4::operator += ( const v4& vec )
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4& v4::operator += ( const f32 scalar )
	{
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4& v4::operator -= ( const v4& vec )
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4& v4::operator -= ( const f32 scalar )
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4& v4::operator *= ( const f32 scalar )
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4& v4::operator *= ( const v4& vec )
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		w *= vec.w;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4& v4::operator /= ( const f32 scalar )
	{
		assert( scalar != 0.0 );

		f32 fInv = f32(1.0) / scalar;

		x *= fInv;
		y *= fInv;
		z *= fInv;
		w *= fInv;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4& v4::operator /= ( const v4& vec )
	{
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		w /= vec.w;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v4::operator < ( const v4& rhs ) const
	{
		if( x < rhs.x && y < rhs.y && z < rhs.z && w < rhs.w)
			return true;
		return false;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v4::operator > ( const v4& rhs ) const
	{
		if( x > rhs.x && y > rhs.y && z > rhs.z && w>rhs.w)
			return true;
		return false;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v4::len () const
	{
		return sqrt( x * x + y * y + z * z + w * w);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v4::sqlen () const
	{
		return x * x + y * y + z * z + w * w;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v4::dot(const v4& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v4::norm()
	{
		f32 fLength = len();

		if ( fLength > 1e-08 )
		{
			f32 fInvLength = f32(1.0) / fLength;
			x *= fInvLength;
			y *= fInvLength;
			z *= fInvLength;
			w *= fInvLength;
		}

		return fLength;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::cross( const v4& vec ) const
	{
		return v4( w * vec.x - x * vec.w,
			       y * vec.z - z * vec.y,
			       z * vec.w - w * vec.z,
			       x * vec.y - y * vec.x );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::reflect(const v4& normal) const
	{
		return v4( *this - ( 2 * this->dot(normal) * normal ) );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v4::iszerolen(void) const
	{
		f32 sqlen = (x * x) + (y * y) + (z * z) + (w * w);
		return (sqlen < (1e-06 * 1e-06));

	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::up(void) const
	{
		static const f32 fSquareZero = f32(1e-06 * 1e-06);

		v4 perp = this->cross( v4::unitX );

		if( perp.sqlen() < fSquareZero )
		{
			perp = this->cross( v4::unitY );
		}

		return perp;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v4 v4::mid( const v4& vec ) const
	{
		return v4( ( x + vec.x ) * f32(0.5),
			       ( y + vec.y ) * f32(0.5),
			       ( z + vec.z ) * f32(0.5),
				   ( w + vec.w ) * f32(0.5) );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void v4::floor( const v4& cmp )
	{
		if( cmp.x < x ) x = cmp.x;
		if( cmp.y < y ) y = cmp.y;
		if( cmp.z < z ) z = cmp.z;
		if( cmp.w < w ) w = cmp.w;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void v4::ceil( const v4& cmp )
	{
		if( cmp.x > x ) x = cmp.x;
		if( cmp.y > y ) y = cmp.y;
		if( cmp.z > z ) z = cmp.z;
		if( cmp.w > w ) w = cmp.w;
	}
}

#endif
