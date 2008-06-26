#ifndef HYPERMATH_VECTOR2
#define HYPERMATH_VECTOR2
#include "math/HMath.h"
namespace hmath
{
	class v2
	{
		public : union 
				 {
					 struct 
					 {
						 f32 x; 
						 f32 y; 
					 };
					 f32 val[2];
				 };

				 inline v2();
				 inline v2(const f32 fX, const f32 fY );
				 inline explicit v2( const f32 scaler );
				 inline explicit v2( const f32 afCoordinate[2] );
				 inline explicit v2( const int afCoordinate[2] );
				 inline explicit v2( f32* const r );
				 inline v2( const v2& rkVector );
				 inline f32 operator [] ( const size_t i ) const;
				 inline f32& operator [] ( const size_t i );
				 inline v2& operator = ( const v2& rkVector );
				 inline v2& operator = ( const f32 fScalar);
				 inline bit operator == ( const v2& rkVector ) const;
				 inline bit operator != ( const v2& rkVector ) const;
				 inline v2 operator + ( const v2& rkVector ) const;
				 inline v2 operator - ( const v2& rkVector ) const;
				 inline v2 operator * ( const f32 fScalar ) const;
				 inline v2 operator * ( const v2& rhs) const;
				 inline v2 operator / ( const f32 fScalar ) const;
				 inline v2 operator / ( const v2& rhs) const;
				 inline const v2& operator + () const;
				 inline v2 operator - () const;
				 inline friend v2 operator * ( const f32 fScalar, const v2& rkVector );
				 inline friend v2 operator / ( const f32 fScalar, const v2& rkVector );
				 inline friend v2 operator + (const v2& lhs, const f32 rhs);
				 inline friend v2 operator + (const f32 lhs, const v2& rhs);
				 inline friend v2 operator - (const v2& lhs, const f32 rhs);
				 inline friend v2 operator - (const f32 lhs, const v2& rhs);
				 inline v2& operator += ( const v2& rkVector );
				 inline v2& operator += ( const f32 fScaler );
				 inline v2& operator -= ( const v2& rkVector );
				 inline v2& operator -= ( const f32 fScaler );
				 inline v2& operator *= ( const f32 fScalar );
				 inline v2& operator *= ( const v2& rkVector );
				 inline v2& operator /= ( const f32 fScalar );
				 inline v2& operator /= ( const v2& rkVector );
				 inline f32 len () const;
				 inline f32 sqlen () const;
				 inline f32 dot(const v2& vec) const;
				 inline f32 norm();
				 inline v2 mid( const v2& vec ) const;
				 inline bit operator < ( const v2& rhs ) const;
				 inline bit operator > ( const v2& rhs ) const;
				 inline void floor( const v2& cmp );
				 inline void ceil( const v2& cmp );
				 inline v2 up(void) const;
				 inline f32 cross( const v2& rkVector ) const;
				 inline bit iszerolen(void) const;
				 inline v2 reflect(const v2& normal) const;

				 static const v2 zero;
				 static const v2 unitX;
				 static const v2 unitY;
				 static const v2 neg_unitX;
				 static const v2 neg_unitY;
				 static const v2 unit;
	};

	v2::v2()
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2::v2(const f32 fX, const f32 fY )
		: x( fX ), y( fY )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2::v2( const f32 scaler )
		: x( scaler), y( scaler )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2::v2( const f32 afCoordinate[2] )
		: x( afCoordinate[0] ),
		y( afCoordinate[1] )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2::v2( const int afCoordinate[2] )
	{
		x = (f32)afCoordinate[0];
		y = (f32)afCoordinate[1];
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2::v2( f32* const r )
		: x( r[0] ), y( r[1] )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2::v2( const v2& rkVector )
		: x( rkVector.x ), y( rkVector.y )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v2::operator [] ( const size_t i ) const
	{
		assert( i < 2 );

		return *(&x+i);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32& v2::operator [] ( const size_t i )
	{
		assert( i < 2 );

		return *(&x+i);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2& v2::operator = ( const v2& rkVector )
	{
		x = rkVector.x;
		y = rkVector.y;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2& v2::operator = ( const f32 fScalar)
	{
		x = fScalar;
		y = fScalar;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v2::operator == ( const v2& rkVector ) const
	{
		return ( x == rkVector.x && y == rkVector.y );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v2::operator != ( const v2& rkVector ) const
	{
		return ( x != rkVector.x || y != rkVector.y  );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 v2::operator + ( const v2& rkVector ) const
	{
		return v2(
			x + rkVector.x,
			y + rkVector.y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 v2::operator - ( const v2& rkVector ) const
	{
		return v2(
			x - rkVector.x,
			y - rkVector.y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 v2::operator * ( const f32 fScalar ) const
	{
		return v2(
			x * fScalar,
			y * fScalar);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 v2::operator * ( const v2& rhs) const
	{
		return v2(
			x * rhs.x,
			y * rhs.y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 v2::operator / ( const f32 fScalar ) const
	{
		assert( fScalar != 0.0 );

		f32 fInv = f32(1.0) / fScalar;

		return v2(
			x * fInv,
			y * fInv);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 v2::operator / ( const v2& rhs) const
	{
		return v2(
			x / rhs.x,
			y / rhs.y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	const v2& v2::operator + () const
	{
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 v2::operator - () const
	{
		return v2(-x, -y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 operator * ( const f32 fScalar, const v2& rkVector )
	{
		return v2( fScalar * rkVector.x,fScalar * rkVector.y );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 operator / ( const f32 fScalar, const v2& rkVector )
	{
		return v2( fScalar / rkVector.x,fScalar / rkVector.y );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 operator + (const v2& lhs, const f32 rhs)
	{
		return v2(
			lhs.x + rhs,
			lhs.y + rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 operator + (const f32 lhs, const v2& rhs)
	{
		return v2( lhs + rhs.x, lhs + rhs.y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 operator - (const v2& lhs, const f32 rhs)
	{
		return v2( lhs.x - rhs, lhs.y - rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 operator - (const f32 lhs, const v2& rhs)
	{
		return v2( lhs - rhs.x,lhs - rhs.y );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2& v2::operator += ( const v2& rkVector )
	{
		x += rkVector.x;
		y += rkVector.y;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2& v2::operator += ( const f32 fScaler )
	{
		x += fScaler;
		y += fScaler;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2& v2::operator -= ( const v2& rkVector )
	{
		x -= rkVector.x;
		y -= rkVector.y;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2& v2::operator -= ( const f32 fScaler )
	{
		x -= fScaler;
		y -= fScaler;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2& v2::operator *= ( const f32 fScalar )
	{
		x *= fScalar;
		y *= fScalar;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2& v2::operator *= ( const v2& rkVector )
	{
		x *= rkVector.x;
		y *= rkVector.y;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2& v2::operator /= ( const f32 fScalar )
	{
		assert( fScalar != 0.0 );

		f32 fInv = f32(1.0) / fScalar;

		x *= fInv;
		y *= fInv;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2& v2::operator /= ( const v2& rkVector )
	{
		x /= rkVector.x;
		y /= rkVector.y;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v2::len () const
	{
		return sqrt( x * x + y * y );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v2::sqlen () const
	{
		return x * x + y * y;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v2::dot(const v2& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v2::norm()
	{
		f32 fLength = sqrt( x * x + y * y);

		if ( fLength > 1e-08 )
		{
			f32 fInvLength = f32(1.0) / fLength;
			x *= fInvLength;
			y *= fInvLength;
		}

		return fLength;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 v2::mid( const v2& vec ) const
	{
		return v2( ( x + vec.x ) * f32(0.5), ( y + vec.y ) * f32(0.5) );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v2::operator < ( const v2& rhs ) const
	{
		if( x < rhs.x && y < rhs.y )
			return true;
		return false;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v2::operator > ( const v2& rhs ) const
	{
		if( x > rhs.x && y > rhs.y )
			return true;
		return false;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void v2::floor( const v2& cmp )
	{
		if( cmp.x < x ) x = cmp.x;
		if( cmp.y < y ) y = cmp.y;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void v2::ceil( const v2& cmp )
	{
		if( cmp.x > x ) x = cmp.x;
		if( cmp.y > y ) y = cmp.y;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 v2::up(void) const
	{
		return v2 (-y, x);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 v2::cross( const v2& rkVector ) const
	{
		return x * rkVector.y - y * rkVector.x;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v2::iszerolen(void) const
	{
		f32 sqlen = (x * x) + (y * y);
		return (sqlen < (1e-06 * 1e-06));

	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2 v2::reflect(const v2& normal) const
	{
		return v2( *this - ( 2 * this->dot(normal) * normal ) );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

};

#endif
