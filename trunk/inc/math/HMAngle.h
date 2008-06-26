#ifndef HYPERMATH_ANGLE
#define HYPERMATH_ANGLE
#include "math/HMath.h"

namespace hmath
{
	class rad;
	class rad64;
	class deg
	{
	public:
		f32 val;
		inline explicit deg ( f32 d=0 );
		inline deg ( const rad& r );
		inline const deg& operator = ( const f32& f );
		inline const deg& operator = ( const deg& d );
		inline const deg& operator = ( const rad& r );

		inline f32 asDeg() const;
		inline f32 asRad() const;

		inline deg operator + ( const deg& d ) const;
		inline deg operator + ( const rad& r ) const;
		inline deg& operator += ( const deg& d );
		inline deg& operator += ( const rad& r );
		inline deg operator - ();
		inline deg operator - ( const deg& d ) const;
		inline deg operator - ( const rad& r ) const;
		inline deg& operator -= ( const deg& d );
		inline deg& operator -= ( const rad& r );
		inline deg operator * ( f32 f ) const;
		inline deg operator * ( const deg& f ) const;
		inline deg& operator *= ( f32 f );
		inline deg operator / ( f32 f ) const;
		inline deg& operator /= ( f32 f );

		inline bit operator <  ( const deg& d ) const;
		inline bit operator <= ( const deg& d ) const;
		inline bit operator == ( const deg& d ) const;
		inline bit operator != ( const deg& d ) const;
		inline bit operator >= ( const deg& d ) const;
		inline bit operator >  ( const deg& d ) const;
	};

	class deg64
	{
	public:
		f64 val;
		inline explicit deg64 ( f64 d=0 );
		inline deg64 ( const rad64& r );
		inline const deg64& operator = ( const f64& f );
		inline const deg64& operator = ( const deg64& d );
		inline const deg64& operator = ( const rad64& r );

		inline f64 asDeg() const;
		inline f64 asRad() const;

		inline deg64 operator + ( const deg64& d ) const;
		inline deg64 operator + ( const rad64& r ) const;
		inline deg64& operator += ( const deg64& d );
		inline deg64& operator += ( const rad64& r );
		inline deg64 operator - ();
		inline deg64 operator - ( const deg64& d ) const;
		inline deg64 operator - ( const rad64& r ) const;
		inline deg64& operator -= ( const deg64& d );
		inline deg64& operator -= ( const rad64& r );
		inline deg64 operator * ( f64 f ) const;
		inline deg64 operator * ( const deg64& f ) const;
		inline deg64& operator *= ( f64 f );
		inline deg64 operator / ( f64 f ) const;
		inline deg64& operator /= ( f64 f );

		inline bit operator <  ( const deg64& d ) const;
		inline bit operator <= ( const deg64& d ) const;
		inline bit operator == ( const deg64& d ) const;
		inline bit operator != ( const deg64& d ) const;
		inline bit operator >= ( const deg64& d ) const;
		inline bit operator >  ( const deg64& d ) const;
	};

	class rad
	{

	public:
		f32 val;
		inline explicit rad ( f32 r=0 );
		inline rad ( const deg& d );
		inline const rad& operator = ( const f32& f );
		inline const rad& operator = ( const rad& r );
		inline const rad& operator = ( const deg& d );

		inline f32 asDeg() const; 
		inline f32 asRad() const;

		inline rad operator + ( const rad& r ) const;
		inline rad operator + ( const deg& d ) const;
		inline rad& operator += ( const rad& r );
		inline rad& operator += ( const deg& d );
		inline rad operator - ();
		inline rad operator - ( const rad& r ) const;
		inline rad operator - ( const deg& d ) const;
		inline rad& operator -= ( const rad& r );
		inline rad& operator -= ( const deg& d );
		inline rad operator * ( f32 f ) const;
		inline rad operator * ( const rad& f ) const;
		inline rad& operator *= ( f32 f );
		inline rad operator / ( f32 f ) const;
		inline rad& operator /= ( f32 f );

		inline bit operator <  ( const rad& r ) const;
		inline bit operator <= ( const rad& r ) const;
		inline bit operator == ( const rad& r ) const;
		inline bit operator != ( const rad& r ) const;
		inline bit operator >= ( const rad& r ) const;
		inline bit operator >  ( const rad& r ) const;
	};

	class rad64
	{

	public:
		f64 val;
		inline explicit rad64 ( f64 r=0 );
		inline rad64 ( const deg64& d );
		inline const rad64& operator = ( const f64& f );
		inline const rad64& operator = ( const rad64& r );
		inline const rad64& operator = ( const deg64& d );

		inline f64 asDeg() const; 
		inline f64 asRad() const;

		inline rad64 operator + ( const rad64& r ) const;
		inline rad64 operator + ( const deg64& d ) const;
		inline rad64& operator += ( const rad64& r );
		inline rad64& operator += ( const deg64& d );
		inline rad64 operator - ();
		inline rad64 operator - ( const rad64& r ) const;
		inline rad64 operator - ( const deg64& d ) const;
		inline rad64& operator -= ( const rad64& r );
		inline rad64& operator -= ( const deg64& d );
		inline rad64 operator * ( f64 f ) const;
		inline rad64 operator * ( const rad64& f ) const;
		inline rad64& operator *= ( f64 f );
		inline rad64 operator / ( f64 f ) const;
		inline rad64& operator /= ( f64 f );

		inline bit operator <  ( const rad64& r ) const;
		inline bit operator <= ( const rad64& r ) const;
		inline bit operator == ( const rad64& r ) const;
		inline bit operator != ( const rad64& r ) const;
		inline bit operator >= ( const rad64& r ) const;
		inline bit operator >  ( const rad64& r ) const;
	};

	deg::deg ( f32 d ) : val(d) 
	{
	}

	deg::deg ( const rad& r ) : val(r.asDeg()) 
	{
	}

	const deg& deg::operator = ( const f32& f ) 
	{ 
		val = f; 
		return *this; 
	}

	const deg& deg::operator = ( const deg& d ) 
	{ 
		val = d.val; 
		return *this; 
	}

	const deg& deg::operator = ( const rad& r ) 
	{
		val = r.asDeg(); 
		return *this; 
	}

	f32 deg::asDeg() const 
	{ 
		return val; 
	}

	f32 deg::asRad() const
	{
		return f32((f64)val * fDeg2Rad);
	}

	deg deg::operator + ( const deg& d ) const 
	{ 
		return deg ( val + d.val ); 
	}

	deg deg::operator + ( const rad& r ) const 
	{ 
		return deg ( val + r.asDeg() ); 
	}

	deg& deg::operator += ( const deg& d ) 
	{ 
		val += d.val; 
		return *this; 
	}

	deg& deg::operator += ( const rad& r ) 
	{ 
		val += r.asDeg(); 
		return *this; 
	}

	deg deg::operator - () 
	{ 
		return deg(-val); 
	}

	deg deg::operator - ( const deg& d ) const 
	{ 
		return deg ( val - d.val ); 
	}

	deg deg::operator - ( const rad& r ) const 
	{ 
		return deg ( val - r.asDeg() ); 
	}

	deg& deg::operator -= ( const deg& d ) 
	{ 
		val -= d.val; 
		return *this; 
	}

	deg& deg::operator -= ( const rad& r ) 
	{ 
		val -= r.asDeg(); 
		return *this; 
	}

	deg deg::operator * ( f32 f ) const 
	{ 
		return deg ( val * f ); 
	}

	deg deg::operator * ( const deg& f ) const 
	{ 
		return deg ( val * f.val ); 
	}

	deg& deg::operator *= ( f32 f ) 
	{ 
		val *= f; 
		return *this; 
	}

	deg deg::operator / ( f32 f ) const 
	{ 
		return deg ( val / f ); 
	}

	deg& deg::operator /= ( f32 f ) 
	{ 
		val /= f; 
		return *this; 
	}

	bit deg::operator <  ( const deg& d ) const 
	{ 
		return val <  d.val; 
	}

	bit deg::operator <= ( const deg& d ) const 
	{ 
		return val <= d.val; 
	}

	bit deg::operator == ( const deg& d ) const 
	{ 
		return val == d.val; 
	}

	bit deg::operator != ( const deg& d ) const 
	{ 
		return val != d.val; 
	}

	bit deg::operator >= ( const deg& d ) const 
	{ 
		return val >= d.val; 
	}

	bit deg::operator >  ( const deg& d ) const 
	{ 
		return val >  d.val; 
	}

	//========================================================================================

	deg64::deg64 ( f64 d ) : val(d) 
	{
	}

	deg64::deg64 ( const rad64& r ) : val(r.asDeg()) 
	{
	}

	const deg64& deg64::operator = ( const f64& f ) 
	{ 
		val = f; 
		return *this; 
	}

	const deg64& deg64::operator = ( const deg64& d ) 
	{ 
		val = d.val; 
		return *this; 
	}

	const deg64& deg64::operator = ( const rad64& r ) 
	{
		val = r.asDeg(); 
		return *this; 
	}

	f64 deg64::asDeg() const 
	{ 
		return val; 
	}

	f64 deg64::asRad() const
	{
		return val * fDeg2Rad;
	}

	deg64 deg64::operator + ( const deg64& d ) const 
	{ 
		return deg64 ( val + d.val ); 
	}

	deg64 deg64::operator + ( const rad64& r ) const 
	{ 
		return deg64 ( val + r.asDeg() ); 
	}

	deg64& deg64::operator += ( const deg64& d ) 
	{ 
		val += d.val; 
		return *this; 
	}

	deg64& deg64::operator += ( const rad64& r ) 
	{ 
		val += r.asDeg(); 
		return *this; 
	}

	deg64 deg64::operator - () 
	{ 
		return deg64(-val); 
	}

	deg64 deg64::operator - ( const deg64& d ) const 
	{ 
		return deg64 ( val - d.val ); 
	}

	deg64 deg64::operator - ( const rad64& r ) const 
	{ 
		return deg64 ( val - r.asDeg() ); 
	}

	deg64& deg64::operator -= ( const deg64& d ) 
	{ 
		val -= d.val; 
		return *this; 
	}

	deg64& deg64::operator -= ( const rad64& r ) 
	{ 
		val -= r.asDeg(); 
		return *this; 
	}

	deg64 deg64::operator * ( f64 f ) const 
	{ 
		return deg64 ( val * f ); 
	}

	deg64 deg64::operator * ( const deg64& f ) const 
	{ 
		return deg64 ( val * f.val ); 
	}

	deg64& deg64::operator *= ( f64 f ) 
	{ 
		val *= f; 
		return *this; 
	}

	deg64 deg64::operator / ( f64 f ) const 
	{ 
		return deg64 ( val / f ); 
	}

	deg64& deg64::operator /= ( f64 f ) 
	{ 
		val /= f; 
		return *this; 
	}

	bit deg64::operator <  ( const deg64& d ) const 
	{ 
		return val <  d.val; 
	}

	bit deg64::operator <= ( const deg64& d ) const 
	{ 
		return val <= d.val; 
	}

	bit deg64::operator == ( const deg64& d ) const 
	{ 
		return val == d.val; 
	}

	bit deg64::operator != ( const deg64& d ) const 
	{ 
		return val != d.val; 
	}

	bit deg64::operator >= ( const deg64& d ) const 
	{ 
		return val >= d.val; 
	}

	bit deg64::operator >  ( const deg64& d ) const 
	{ 
		return val >  d.val; 
	}

	//========================================================================================

	rad::rad ( f32 r ) : val(r) 
	{

	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad::rad ( const deg& d )  : val(d.asRad())
	{

	}

	//————————————————————————————————————————————————————————————————————————————————————————

	const rad& rad::operator = ( const f32& f ) 
	{ 
		val = f; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	const rad& rad::operator = ( const rad& r ) 
	{ 
		val = r.val; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	const rad& rad::operator = ( const deg& d )
	{
		val = d.asRad(); 
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 rad::asDeg() const
	{
		return f32(f64(val) * fRad2Deg);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 rad::asRad() const 
	{ 
		return val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad rad::operator + ( const rad& r ) const 
	{ 
		return rad ( val + r.val ); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad rad::operator + ( const deg& d ) const
	{
		return rad ( val + d.asRad() );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad& rad::operator += ( const rad& r ) 
	{ 
		val += r.val; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad& rad::operator += ( const deg& d )
	{
		val += d.asRad();
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad rad::operator - () 
	{ 
		return rad(-val); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad rad::operator - ( const rad& r ) const 
	{
		return rad ( val - r.val ); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad rad::operator - ( const deg& d ) const
	{
		return rad ( val - d.asRad() );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad& rad::operator -= ( const rad& r ) 
	{ 
		val -= r.val; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad& rad::operator -= ( const deg& d )
	{
		val -= d.asRad();
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad rad::operator * ( f32 f ) const 
	{ 
		return rad ( val * f ); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad rad::operator * ( const rad& f ) const 
	{ 
		return rad ( val * f.val ); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad& rad::operator *= ( f32 f ) 
	{ 
		val *= f; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad rad::operator / ( f32 f ) const 
	{ 
		return rad ( val / f ); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad& rad::operator /= ( f32 f ) 
	{ 
		val /= f; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad::operator <  ( const rad& r ) const 
	{ 
		return val <  r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad::operator <= ( const rad& r ) const 
	{ 
		return val <= r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad::operator == ( const rad& r ) const 
	{ 
		return val == r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad::operator != ( const rad& r ) const 
	{
		return val != r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad::operator >= ( const rad& r ) const 
	{ 
		return val >= r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad::operator >  ( const rad& r ) const 
	{ 
		return val >  r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	inline rad operator * ( f32 a, const rad& b )
	{
		return rad ( a * b.asRad() );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	inline rad operator / ( f32 a, const rad& b )
	{
		return rad ( a / b.asRad() );
	}

	//====================================================================================

	rad64::rad64 ( f64 r ) : val(r) 
	{

	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64::rad64 ( const deg64& d )  : val(d.asRad())
	{

	}

	//————————————————————————————————————————————————————————————————————————————————————————

	const rad64& rad64::operator = ( const f64& f ) 
	{ 
		val = f; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	const rad64& rad64::operator = ( const rad64& r ) 
	{ 
		val = r.val; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	const rad64& rad64::operator = ( const deg64& d )
	{
		val = d.asRad(); 
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 rad64::asDeg() const
	{
		return val * fRad2Deg;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f64 rad64::asRad() const 
	{ 
		return val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64 rad64::operator + ( const rad64& r ) const 
	{ 
		return rad64 ( val + r.val ); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64 rad64::operator + ( const deg64& d ) const
	{
		return rad64 ( val + d.asRad() );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64& rad64::operator += ( const rad64& r ) 
	{ 
		val += r.val; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64& rad64::operator += ( const deg64& d )
	{
		val += d.asRad();
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64 rad64::operator - () 
	{ 
		return rad64(-val); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64 rad64::operator - ( const rad64& r ) const 
	{
		return rad64 ( val - r.val ); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64 rad64::operator - ( const deg64& d ) const
	{
		return rad64 ( val - d.asRad() );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64& rad64::operator -= ( const rad64& r ) 
	{ 
		val -= r.val; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64& rad64::operator -= ( const deg64& d )
	{
		val -= d.asRad();
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64 rad64::operator * ( f64 f ) const 
	{ 
		return rad64 ( val * f ); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64 rad64::operator * ( const rad64& f ) const 
	{ 
		return rad64 ( val * f.val ); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64& rad64::operator *= ( f64 f ) 
	{ 
		val *= f; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64 rad64::operator / ( f64 f ) const 
	{ 
		return rad64 ( val / f ); 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	rad64& rad64::operator /= ( f64 f ) 
	{ 
		val /= f; 
		return *this; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad64::operator <  ( const rad64& r ) const 
	{ 
		return val <  r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad64::operator <= ( const rad64& r ) const 
	{ 
		return val <= r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad64::operator == ( const rad64& r ) const 
	{ 
		return val == r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad64::operator != ( const rad64& r ) const 
	{
		return val != r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad64::operator >= ( const rad64& r ) const 
	{ 
		return val >= r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit rad64::operator >  ( const rad64& r ) const 
	{ 
		return val >  r.val; 
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	inline rad64 operator * ( f64 a, const rad64& b )
	{
		return rad64 ( a * b.asRad() );
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	inline rad64 operator / ( f64 a, const rad64& b )
	{
		return rad64 ( a / b.asRad() );
	}
};
#endif
