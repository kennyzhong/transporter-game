#ifndef HMVECTOR3_64_H
#define HMVECTOR3_64_H
#include "math/HMath.h"

namespace hmath
{
	class v3_64
	{
	public : 
		union 
		{
			struct 
			{
				f64 x; 
				f64 y; 
				f64 z;
			};
			f64 val[3];
		};
		inline v3_64(){};
		inline v3_64( const f64 fX, const f64 fY, const f64 fZ );
		inline explicit v3_64( const i32 fX, const i32 fY, const i32 fZ );
		inline explicit v3_64( const f64 vec[3] );
		inline explicit v3_64( const i32 vec[3] );
		inline explicit v3_64( f64* const r );
		inline explicit v3_64( const f64 scaler );
		inline v3_64( const v3_64& vec );

		inline f64 operator [] ( const size_t i ) const;
		inline f64& operator [] ( const size_t i );
		inline v3_64& operator = ( const v3_64& vec );
		inline v3_64& operator = ( const f64 scaler );
		inline bit operator == ( const v3_64& vec ) const;
		inline bit operator != ( const v3_64& vec ) const;
		inline v3_64 operator + ( const v3_64& vec ) const;
		inline v3_64 operator - ( const v3_64& vec ) const;
		inline v3_64 operator * ( const f64 scalar ) const;
		inline v3_64 operator * ( const v3_64& rhs) const;
		inline v3_64 operator / ( const f64 scalar ) const;
		inline v3_64 operator / ( const v3_64& rhs) const;
		inline v3_64 operator - () const;
		inline v3_64 operator + () const;
		inline v3_64& operator += ( const v3_64& vec );
		inline v3_64& operator += ( const f64 scalar );
		inline v3_64& operator -= ( const v3_64& vec );
		inline v3_64& operator -= ( const f64 scalar );
		inline v3_64& operator *= ( const f64 scalar );
		inline v3_64& operator *= ( const v3_64& vec );
		inline v3_64& operator /= ( const f64 scalar );
		inline v3_64& operator /= ( const v3_64& vec );
		inline bit operator < ( const v3_64& rhs ) const;
		inline bit operator > ( const v3_64& rhs ) const;
		inline f64 len () const;
		inline f64 sqlen () const;
		inline f64 dot(const v3_64& vec) const;
		inline f64 norm();
		inline v3_64 cross( const v3_64& vec ) const;
		inline v3_64 reflect(const v3_64& normal) const;
		inline bit iszerolen(void) const;
		inline v3_64 up(void) const;
		inline v3_64 mid( const v3_64& vec ) const;
		inline void floor( const v3_64& cmp );
		inline void ceil( const v3_64& cmp );

		static const v3_64 zero;
		static const v3_64 unitX;
		static const v3_64 unitY;
		static const v3_64 unitZ;
		static const v3_64 neg_unitX;
		static const v3_64 neg_unitY;
		static const v3_64 neg_unitZ;
		static const v3_64 unit;

		quat getRotationTo(const v3_64& dest, const v3_64& fallbackAxis = v3_64::zero) const;
	};

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64::v3_64( const f64 fX, const f64 fY, const f64 fZ )
		: x( fX ), y( fY ), z( fZ )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64::v3_64( const i32 fX, const i32 fY, const i32 fZ )
	{
		x = f64(fX);
		y = f64(fY);
		z = f64(fZ);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64::v3_64( const f64 vec[3] )
		: x( vec[0] ), y( vec[1] ), z( vec[2] )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64::v3_64( const i32 vec[3] )
	{
		x = (f64)vec[0];
		y = (f64)vec[1];
		z = (f64)vec[2];
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64::v3_64( f64* const r )
		: x( r[0] ), y( r[1] ), z( r[2] )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64::v3_64( const f64 scaler )
		: x( scaler ), y( scaler ), z( scaler )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64::v3_64( const v3_64& vec )
		: x( vec.x ), y( vec.y ), z( vec.z )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v3_64::operator [] ( const size_t i ) const
	{
		//	assert( i < 3 );
		return *(&x+i);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64& v3_64::operator [] ( const size_t i )
	{
		//	assert( i < 3 );
		return *(&x+i);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64& v3_64::operator = ( const v3_64& vec )
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64& v3_64::operator = ( const f64 scaler )
	{
		x = scaler;
		y = scaler;
		z = scaler;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v3_64::operator == ( const v3_64& vec ) const
	{
		return ( x == vec.x && y == vec.y && z == vec.z );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v3_64::operator != ( const v3_64& vec ) const
	{
		return ( x != vec.x || y != vec.y || z != vec.z );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::operator + ( const v3_64& vec ) const
	{
		return v3_64(x + vec.x,y + vec.y,z + vec.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::operator - ( const v3_64& vec ) const
	{
		return v3_64(x - vec.x,y - vec.y,z - vec.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::operator * ( const f64 scalar ) const
	{
		return v3_64(x * scalar,y * scalar,z * scalar);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::operator * ( const v3_64& rhs) const
	{
		return v3_64(x * rhs.x,y * rhs.y, z * rhs.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::operator / ( const f64 scalar ) const
	{
		assert( scalar != 0.0 );

		f64 fInv = f64(1.0) / scalar;

		return v3_64( x * fInv,y * fInv,z * fInv);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::operator / ( const v3_64& rhs) const
	{
		return v3_64(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::operator + () const
	{
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::operator - () const
	{
		return v3_64(-x, -y, -z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v3_64 operator * ( const f64 scalar, const v3_64& vec ) 
	{
		return v3_64( scalar * vec.x, scalar * vec.y, scalar * vec.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v3_64 operator + (const v3_64& lhs, const f64 rhs) 
	{
		return v3_64( lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v3_64 operator + (const f64 lhs, const v3_64& rhs) 
	{
		return v3_64( lhs + rhs.x, lhs + rhs.y,lhs + rhs.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v3_64 operator - (const v3_64& lhs, const f64 rhs) 
	{
		return v3_64( lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	static v3_64 operator - (const f64 lhs, const v3_64& rhs) 
	{
		return v3_64(lhs - rhs.x,lhs - rhs.y,lhs - rhs.z);
	}

	//————————————————————————————————————————————————————————————————————————————————————————


	v3_64& v3_64::operator += ( const v3_64& vec )
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64& v3_64::operator += ( const f64 scalar )
	{
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64& v3_64::operator -= ( const v3_64& vec )
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64& v3_64::operator -= ( const f64 scalar )
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64& v3_64::operator *= ( const f64 scalar )
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64& v3_64::operator *= ( const v3_64& vec )
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64& v3_64::operator /= ( const f64 scalar )
	{
		assert( scalar != 0.0 );

		f64 fInv = f64(1.0) / scalar;

		x *= fInv;
		y *= fInv;
		z *= fInv;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64& v3_64::operator /= ( const v3_64& vec )
	{
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v3_64::operator < ( const v3_64& rhs ) const
	{
		if( x < rhs.x && y < rhs.y && z < rhs.z )
			return true;
		return false;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v3_64::operator > ( const v3_64& rhs ) const
	{
		if( x > rhs.x && y > rhs.y && z > rhs.z )
			return true;
		return false;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v3_64::len () const
	{
		return sqrt( x * x + y * y + z * z );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v3_64::sqlen () const
	{
		return x * x + y * y + z * z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v3_64::dot(const v3_64& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v3_64::norm()
	{
		f64 fLength = len();

		if ( fLength > 1e-08 )
		{
			f64 fInvLength = f64(1.0) / fLength;
			x *= fInvLength;
			y *= fInvLength;
			z *= fInvLength;
		}

		return fLength;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::cross( const v3_64& vec ) const
	{
		return v3_64(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::reflect(const v3_64& normal) const
	{
		return v3_64( *this - ( 2 * this->dot(normal) * normal ) );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v3_64::iszerolen(void) const
	{
		f64 sqlen = (x * x) + (y * y) + (z * z);
		return (sqlen < (1e-06 * 1e-06));

	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::up(void) const
	{
		static const f64 fSquareZero = f64(1e-06 * 1e-06);

		v3_64 perp = this->cross( v3_64::unitX );

		if( perp.sqlen() < fSquareZero )
		{
			perp = this->cross( v3_64::unitY );
		}

		return perp;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3_64 v3_64::mid( const v3_64& vec ) const
	{
		return v3_64( ( x + vec.x ) * f64(0.5),
			( y + vec.y ) * f64(0.5),
			( z + vec.z ) * f64(0.5) );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void v3_64::floor( const v3_64& cmp )
	{
		if( cmp.x < x ) x = cmp.x;
		if( cmp.y < y ) y = cmp.y;
		if( cmp.z < z ) z = cmp.z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void v3_64::ceil( const v3_64& cmp )
	{
		if( cmp.x > x ) x = cmp.x;
		if( cmp.y > y ) y = cmp.y;
		if( cmp.z > z ) z = cmp.z;
	}
}
#endif
