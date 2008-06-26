#ifndef HMVECTOR2_64_H
#define HMVECTOR2_64_H
#include "math/HMath.h"


namespace hmath
{
	class v2_64
	{
	public : union 
			 {
				 struct 
				 {
					 f64 x; 
					 f64 y; 
				 };
				 f64 val[2];
			 };

			 inline v2_64();
			 inline v2_64(const f64 fX, const f64 fY );
			 inline explicit v2_64( const f64 scaler );
			 inline explicit v2_64( const f64 afCoordinate[2] );
			 inline explicit v2_64( const int afCoordinate[2] );
			 inline explicit v2_64( f64* const r );
			 inline v2_64( const v2_64& rkVector );
			 inline f64 operator [] ( const size_t i ) const;
			 inline f64& operator [] ( const size_t i );
			 inline v2_64& operator = ( const v2_64& rkVector );
			 inline v2_64& operator = ( const f64 fScalar);
			 inline bit operator == ( const v2_64& rkVector ) const;
			 inline bit operator != ( const v2_64& rkVector ) const;
			 inline v2_64 operator + ( const v2_64& rkVector ) const;
			 inline v2_64 operator - ( const v2_64& rkVector ) const;
			 inline v2_64 operator * ( const f64 fScalar ) const;
			 inline v2_64 operator * ( const v2_64& rhs) const;
			 inline v2_64 operator / ( const f64 fScalar ) const;
			 inline v2_64 operator / ( const v2_64& rhs) const;
			 inline const v2_64& operator + () const;
			 inline v2_64 operator - () const;
			 inline friend v2_64 operator * ( const f64 fScalar, const v2_64& rkVector );
			 inline friend v2_64 operator / ( const f64 fScalar, const v2_64& rkVector );
			 inline friend v2_64 operator + (const v2_64& lhs, const f64 rhs);
			 inline friend v2_64 operator + (const f64 lhs, const v2_64& rhs);
			 inline friend v2_64 operator - (const v2_64& lhs, const f64 rhs);
			 inline friend v2_64 operator - (const f64 lhs, const v2_64& rhs);
			 inline v2_64& operator += ( const v2_64& rkVector );
			 inline v2_64& operator += ( const f64 fScaler );
			 inline v2_64& operator -= ( const v2_64& rkVector );
			 inline v2_64& operator -= ( const f64 fScaler );
			 inline v2_64& operator *= ( const f64 fScalar );
			 inline v2_64& operator *= ( const v2_64& rkVector );
			 inline v2_64& operator /= ( const f64 fScalar );
			 inline v2_64& operator /= ( const v2_64& rkVector );
			 inline f64 len () const;
			 inline f64 sqlen () const;
			 inline f64 dot(const v2_64& vec) const;
			 inline f64 norm();
			 inline v2_64 mid( const v2_64& vec ) const;
			 inline bit operator < ( const v2_64& rhs ) const;
			 inline bit operator > ( const v2_64& rhs ) const;
			 inline void floor( const v2_64& cmp );
			 inline void ceil( const v2_64& cmp );
			 inline v2_64 up(void) const;
			 inline f64 cross( const v2_64& rkVector ) const;
			 inline bit iszerolen(void) const;
			 inline v2_64 reflect(const v2_64& normal) const;

			 static const v2_64 zero;
			 static const v2_64 unitX;
			 static const v2_64 unitY;
			 static const v2_64 neg_unitX;
			 static const v2_64 neg_unitY;
			 static const v2_64 unit;
	};

	v2_64::v2_64()
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64::v2_64(const f64 fX, const f64 fY )
		: x( fX ), y( fY )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64::v2_64( const f64 scaler )
		: x( scaler), y( scaler )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64::v2_64( const f64 afCoordinate[2] )
		: x( afCoordinate[0] ),
		y( afCoordinate[1] )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64::v2_64( const int afCoordinate[2] )
	{
		x = (f64)afCoordinate[0];
		y = (f64)afCoordinate[1];
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64::v2_64( f64* const r )
		: x( r[0] ), y( r[1] )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64::v2_64( const v2_64& rkVector )
		: x( rkVector.x ), y( rkVector.y )
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v2_64::operator [] ( const size_t i ) const
	{
		assert( i < 2 );

		return *(&x+i);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64& v2_64::operator [] ( const size_t i )
	{
		assert( i < 2 );

		return *(&x+i);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64& v2_64::operator = ( const v2_64& rkVector )
	{
		x = rkVector.x;
		y = rkVector.y;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64& v2_64::operator = ( const f64 fScalar)
	{
		x = fScalar;
		y = fScalar;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v2_64::operator == ( const v2_64& rkVector ) const
	{
		return ( x == rkVector.x && y == rkVector.y );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v2_64::operator != ( const v2_64& rkVector ) const
	{
		return ( x != rkVector.x || y != rkVector.y  );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 v2_64::operator + ( const v2_64& rkVector ) const
	{
		return v2_64(
			x + rkVector.x,
			y + rkVector.y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 v2_64::operator - ( const v2_64& rkVector ) const
	{
		return v2_64(
			x - rkVector.x,
			y - rkVector.y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 v2_64::operator * ( const f64 fScalar ) const
	{
		return v2_64(
			x * fScalar,
			y * fScalar);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 v2_64::operator * ( const v2_64& rhs) const
	{
		return v2_64(
			x * rhs.x,
			y * rhs.y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 v2_64::operator / ( const f64 fScalar ) const
	{
		assert( fScalar != 0.0 );

		f64 fInv = f64(1.0) / fScalar;

		return v2_64(
			x * fInv,
			y * fInv);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 v2_64::operator / ( const v2_64& rhs) const
	{
		return v2_64(
			x / rhs.x,
			y / rhs.y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	const v2_64& v2_64::operator + () const
	{
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 v2_64::operator - () const
	{
		return v2_64(-x, -y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 operator * ( const f64 fScalar, const v2_64& rkVector )
	{
		return v2_64( fScalar * rkVector.x,fScalar * rkVector.y );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 operator / ( const f64 fScalar, const v2_64& rkVector )
	{
		return v2_64( fScalar / rkVector.x,fScalar / rkVector.y );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 operator + (const v2_64& lhs, const f64 rhs)
	{
		return v2_64(
			lhs.x + rhs,
			lhs.y + rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 operator + (const f64 lhs, const v2_64& rhs)
	{
		return v2_64( lhs + rhs.x, lhs + rhs.y);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 operator - (const v2_64& lhs, const f64 rhs)
	{
		return v2_64( lhs.x - rhs, lhs.y - rhs);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 operator - (const f64 lhs, const v2_64& rhs)
	{
		return v2_64( lhs - rhs.x,lhs - rhs.y );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64& v2_64::operator += ( const v2_64& rkVector )
	{
		x += rkVector.x;
		y += rkVector.y;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64& v2_64::operator += ( const f64 fScaler )
	{
		x += fScaler;
		y += fScaler;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64& v2_64::operator -= ( const v2_64& rkVector )
	{
		x -= rkVector.x;
		y -= rkVector.y;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64& v2_64::operator -= ( const f64 fScaler )
	{
		x -= fScaler;
		y -= fScaler;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64& v2_64::operator *= ( const f64 fScalar )
	{
		x *= fScalar;
		y *= fScalar;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64& v2_64::operator *= ( const v2_64& rkVector )
	{
		x *= rkVector.x;
		y *= rkVector.y;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64& v2_64::operator /= ( const f64 fScalar )
	{
		assert( fScalar != 0.0 );

		f64 fInv = f64(1.0) / fScalar;

		x *= fInv;
		y *= fInv;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64& v2_64::operator /= ( const v2_64& rkVector )
	{
		x /= rkVector.x;
		y /= rkVector.y;

		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v2_64::len () const
	{
		return sqrt( x * x + y * y );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v2_64::sqlen () const
	{
		return x * x + y * y;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v2_64::dot(const v2_64& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v2_64::norm()
	{
		f64 fLength = sqrt( x * x + y * y);

		if ( fLength > 1e-08 )
		{
			f64 fInvLength = f64(1.0) / fLength;
			x *= fInvLength;
			y *= fInvLength;
		}

		return fLength;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 v2_64::mid( const v2_64& vec ) const
	{
		return v2_64( ( x + vec.x ) * f64(0.5), ( y + vec.y ) * f64(0.5) );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v2_64::operator < ( const v2_64& rhs ) const
	{
		if( x < rhs.x && y < rhs.y )
			return true;
		return false;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v2_64::operator > ( const v2_64& rhs ) const
	{
		if( x > rhs.x && y > rhs.y )
			return true;
		return false;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void v2_64::floor( const v2_64& cmp )
	{
		if( cmp.x < x ) x = cmp.x;
		if( cmp.y < y ) y = cmp.y;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void v2_64::ceil( const v2_64& cmp )
	{
		if( cmp.x > x ) x = cmp.x;
		if( cmp.y > y ) y = cmp.y;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 v2_64::up(void) const
	{
		return v2_64 (-y, x);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 v2_64::cross( const v2_64& rkVector ) const
	{
		return x * rkVector.y - y * rkVector.x;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit v2_64::iszerolen(void) const
	{
		f64 sqlen = (x * x) + (y * y);
		return (sqlen < (1e-06 * 1e-06));

	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v2_64 v2_64::reflect(const v2_64& normal) const
	{
		return v2_64( *this - ( 2 * this->dot(normal) * normal ) );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

};

#endif
