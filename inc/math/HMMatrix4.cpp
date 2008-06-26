#include "math/HMath.h"

namespace hmath
{

    const m4 m4::ZERO(
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0 );

    const m4 m4::IDENTITY(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 );

    const m4 m4::CLIPSPACE2DTOIMAGESPACE(
        0.5,    0,  0, 0.5, 
          0, -0.5,  0, 0.5, 
          0,    0,  1,   0,
          0,    0,  0,   1);

    //-----------------------------------------------------------------------
    inline static f64
        MINOR(const m4& m, const size_t r0, const size_t r1, const size_t r2, 
								const size_t c0, const size_t c1, const size_t c2)
    {
        return m[r0][c0] * (m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) -
            m[r0][c1] * (m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) +
            m[r0][c2] * (m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]);
    }
    //-----------------------------------------------------------------------

	m4::m4()
	{
	}

	m4::m4(
		f64 m00, f64 m01, f64 m02, f64 m03,
		f64 m10, f64 m11, f64 m12, f64 m13,
		f64 m20, f64 m21, f64 m22, f64 m23,
		f64 m30, f64 m31, f64 m32, f64 m33 )
	{
		val[0][0] = m00;
		val[0][1] = m01;
		val[0][2] = m02;
		val[0][3] = m03;
		val[1][0] = m10;
		val[1][1] = m11;
		val[1][2] = m12;
		val[1][3] = m13;
		val[2][0] = m20;
		val[2][1] = m21;
		val[2][2] = m22;
		val[2][3] = m23;
		val[3][0] = m30;
		val[3][1] = m31;
		val[3][2] = m32;
		val[3][3] = m33;
	}

	void m4::set( f64 m00, f64 m01, f64 m02, f64 m03,
		f64 m10, f64 m11, f64 m12, f64 m13,
		f64 m20, f64 m21, f64 m22, f64 m23,
		f64 m30, f64 m31, f64 m32, f64 m33 )
	{
		val[0][0] = m00;
		val[0][1] = m01;
		val[0][2] = m02;
		val[0][3] = m03;
		val[1][0] = m10;
		val[1][1] = m11;
		val[1][2] = m12;
		val[1][3] = m13;
		val[2][0] = m20;
		val[2][1] = m21;
		val[2][2] = m22;
		val[2][3] = m23;
		val[3][0] = m30;
		val[3][1] = m31;
		val[3][2] = m32;
		val[3][3] = m33;
	}

	m4::m4(const m3& m3x3)
	{
		operator=(IDENTITY);
		operator=(m3x3);
	}

	m4::m4(const quat& rot)
	{
		m3 m3x3;
		rot.ToRotationMatrix(m3x3);
		operator=(IDENTITY);
		operator=(m3x3);
	}


	f64* m4::operator [] ( size_t iRow )
	{
		assert( iRow < 4 );
		return val[iRow];
	}

	const f64 *const m4::operator [] ( size_t iRow ) const
	{
		assert( iRow < 4 );
		return val[iRow];
	}

	m4 m4::concatenate(const m4 &m2) const
	{
		m4 r;
		r.val[0][0] = val[0][0] * m2.val[0][0] + val[0][1] * m2.val[1][0] + val[0][2] * m2.val[2][0] + val[0][3] * m2.val[3][0];
		r.val[0][1] = val[0][0] * m2.val[0][1] + val[0][1] * m2.val[1][1] + val[0][2] * m2.val[2][1] + val[0][3] * m2.val[3][1];
		r.val[0][2] = val[0][0] * m2.val[0][2] + val[0][1] * m2.val[1][2] + val[0][2] * m2.val[2][2] + val[0][3] * m2.val[3][2];
		r.val[0][3] = val[0][0] * m2.val[0][3] + val[0][1] * m2.val[1][3] + val[0][2] * m2.val[2][3] + val[0][3] * m2.val[3][3];

		r.val[1][0] = val[1][0] * m2.val[0][0] + val[1][1] * m2.val[1][0] + val[1][2] * m2.val[2][0] + val[1][3] * m2.val[3][0];
		r.val[1][1] = val[1][0] * m2.val[0][1] + val[1][1] * m2.val[1][1] + val[1][2] * m2.val[2][1] + val[1][3] * m2.val[3][1];
		r.val[1][2] = val[1][0] * m2.val[0][2] + val[1][1] * m2.val[1][2] + val[1][2] * m2.val[2][2] + val[1][3] * m2.val[3][2];
		r.val[1][3] = val[1][0] * m2.val[0][3] + val[1][1] * m2.val[1][3] + val[1][2] * m2.val[2][3] + val[1][3] * m2.val[3][3];

		r.val[2][0] = val[2][0] * m2.val[0][0] + val[2][1] * m2.val[1][0] + val[2][2] * m2.val[2][0] + val[2][3] * m2.val[3][0];
		r.val[2][1] = val[2][0] * m2.val[0][1] + val[2][1] * m2.val[1][1] + val[2][2] * m2.val[2][1] + val[2][3] * m2.val[3][1];
		r.val[2][2] = val[2][0] * m2.val[0][2] + val[2][1] * m2.val[1][2] + val[2][2] * m2.val[2][2] + val[2][3] * m2.val[3][2];
		r.val[2][3] = val[2][0] * m2.val[0][3] + val[2][1] * m2.val[1][3] + val[2][2] * m2.val[2][3] + val[2][3] * m2.val[3][3];

		r.val[3][0] = val[3][0] * m2.val[0][0] + val[3][1] * m2.val[1][0] + val[3][2] * m2.val[2][0] + val[3][3] * m2.val[3][0];
		r.val[3][1] = val[3][0] * m2.val[0][1] + val[3][1] * m2.val[1][1] + val[3][2] * m2.val[2][1] + val[3][3] * m2.val[3][1];
		r.val[3][2] = val[3][0] * m2.val[0][2] + val[3][1] * m2.val[1][2] + val[3][2] * m2.val[2][2] + val[3][3] * m2.val[3][2];
		r.val[3][3] = val[3][0] * m2.val[0][3] + val[3][1] * m2.val[1][3] + val[3][2] * m2.val[2][3] + val[3][3] * m2.val[3][3];

		return r;
	}

	m4 m4::operator * ( const m4 &m2 ) const
	{
		return concatenate( m2 );
	}

	v3 m4::operator * ( const v3 &v ) const
	{
		v3 r;

		f64 fInvW = 1.0 / ( val[3][0] * v.x + val[3][1] * v.y + val[3][2] * v.z + val[3][3] );

		r.x = ( (f32)val[0][0] * v.x + (f32)val[0][1] * v.y + (f32)val[0][2] * v.z + (f32)val[0][3] ) * (f32)fInvW;
		r.y = ( (f32)val[1][0] * v.x + (f32)val[1][1] * v.y + (f32)val[1][2] * v.z + (f32)val[1][3] ) * (f32)fInvW;
		r.z = ( (f32)val[2][0] * v.x + (f32)val[2][1] * v.y + (f32)val[2][2] * v.z + (f32)val[2][3] ) * (f32)fInvW;

		return r;
	}
	v4 m4::operator * (const v4& v) const
	{
		return v4(
			(f32)val[0][0] * v.x + (f32)val[0][1] * v.y + (f32)val[0][2] * v.z + (f32)val[0][3] * v.w, 
			(f32)val[1][0] * v.x + (f32)val[1][1] * v.y + (f32)val[1][2] * v.z + (f32)val[1][3] * v.w,
			(f32)val[2][0] * v.x + (f32)val[2][1] * v.y + (f32)val[2][2] * v.z + (f32)val[2][3] * v.w,
			(f32)val[3][0] * v.x + (f32)val[3][1] * v.y + (f32)val[3][2] * v.z + (f32)val[3][3] * v.w
			);
	}


	m4 m4::operator + ( const m4 &m2 ) const
	{
		m4 r;

		r.val[0][0] = val[0][0] + m2.val[0][0];
		r.val[0][1] = val[0][1] + m2.val[0][1];
		r.val[0][2] = val[0][2] + m2.val[0][2];
		r.val[0][3] = val[0][3] + m2.val[0][3];

		r.val[1][0] = val[1][0] + m2.val[1][0];
		r.val[1][1] = val[1][1] + m2.val[1][1];
		r.val[1][2] = val[1][2] + m2.val[1][2];
		r.val[1][3] = val[1][3] + m2.val[1][3];

		r.val[2][0] = val[2][0] + m2.val[2][0];
		r.val[2][1] = val[2][1] + m2.val[2][1];
		r.val[2][2] = val[2][2] + m2.val[2][2];
		r.val[2][3] = val[2][3] + m2.val[2][3];

		r.val[3][0] = val[3][0] + m2.val[3][0];
		r.val[3][1] = val[3][1] + m2.val[3][1];
		r.val[3][2] = val[3][2] + m2.val[3][2];
		r.val[3][3] = val[3][3] + m2.val[3][3];

		return r;
	}

	m4 m4::operator - ( const m4 &m2 ) const
	{
		m4 r;
		r.val[0][0] = val[0][0] - m2.val[0][0];
		r.val[0][1] = val[0][1] - m2.val[0][1];
		r.val[0][2] = val[0][2] - m2.val[0][2];
		r.val[0][3] = val[0][3] - m2.val[0][3];

		r.val[1][0] = val[1][0] - m2.val[1][0];
		r.val[1][1] = val[1][1] - m2.val[1][1];
		r.val[1][2] = val[1][2] - m2.val[1][2];
		r.val[1][3] = val[1][3] - m2.val[1][3];

		r.val[2][0] = val[2][0] - m2.val[2][0];
		r.val[2][1] = val[2][1] - m2.val[2][1];
		r.val[2][2] = val[2][2] - m2.val[2][2];
		r.val[2][3] = val[2][3] - m2.val[2][3];

		r.val[3][0] = val[3][0] - m2.val[3][0];
		r.val[3][1] = val[3][1] - m2.val[3][1];
		r.val[3][2] = val[3][2] - m2.val[3][2];
		r.val[3][3] = val[3][3] - m2.val[3][3];

		return r;
	}

	bit m4::operator == ( const m4& m2 ) const
	{
		if( 
			val[0][0] != m2.val[0][0] || val[0][1] != m2.val[0][1] || val[0][2] != m2.val[0][2] || val[0][3] != m2.val[0][3] ||
			val[1][0] != m2.val[1][0] || val[1][1] != m2.val[1][1] || val[1][2] != m2.val[1][2] || val[1][3] != m2.val[1][3] ||
			val[2][0] != m2.val[2][0] || val[2][1] != m2.val[2][1] || val[2][2] != m2.val[2][2] || val[2][3] != m2.val[2][3] ||
			val[3][0] != m2.val[3][0] || val[3][1] != m2.val[3][1] || val[3][2] != m2.val[3][2] || val[3][3] != m2.val[3][3] )
			return false;
		return true;
	}

	bit m4::operator != ( const m4& m2 ) const
	{
		if( 
			val[0][0] != m2.val[0][0] || val[0][1] != m2.val[0][1] || val[0][2] != m2.val[0][2] || val[0][3] != m2.val[0][3] ||
			val[1][0] != m2.val[1][0] || val[1][1] != m2.val[1][1] || val[1][2] != m2.val[1][2] || val[1][3] != m2.val[1][3] ||
			val[2][0] != m2.val[2][0] || val[2][1] != m2.val[2][1] || val[2][2] != m2.val[2][2] || val[2][3] != m2.val[2][3] ||
			val[3][0] != m2.val[3][0] || val[3][1] != m2.val[3][1] || val[3][2] != m2.val[3][2] || val[3][3] != m2.val[3][3] )
			return true;
		return false;
	}

	void m4::operator = ( const m3& mat3 )
	{
		val[0][0] = mat3.val[0][0]; val[0][1] = mat3.val[0][1]; val[0][2] = mat3.val[0][2];
		val[1][0] = mat3.val[1][0]; val[1][1] = mat3.val[1][1]; val[1][2] = mat3.val[1][2];
		val[2][0] = mat3.val[2][0]; val[2][1] = mat3.val[2][1]; val[2][2] = mat3.val[2][2];
	}

	m4 m4::transpose(void) const
	{
		return m4(val[0][0], val[1][0], val[2][0], val[3][0],
			val[0][1], val[1][1], val[2][1], val[3][1],
			val[0][2], val[1][2], val[2][2], val[3][2],
			val[0][3], val[1][3], val[2][3], val[3][3]);
	}

	void m4::setTrans( const v3& v )
	{
		val[0][3] = v.x;
		val[1][3] = v.y;
		val[2][3] = v.z;
	}

	v3 m4::getTrans() const
	{
		return v3((f32)val[0][3], (f32)val[1][3], (f32)val[2][3]);
	}


	void m4::makeTrans( const v3& v )
	{
		val[0][0] = 1.0; val[0][1] = 0.0; val[0][2] = 0.0; val[0][3] = v.x;
		val[1][0] = 0.0; val[1][1] = 1.0; val[1][2] = 0.0; val[1][3] = v.y;
		val[2][0] = 0.0; val[2][1] = 0.0; val[2][2] = 1.0; val[2][3] = v.z;
		val[3][0] = 0.0; val[3][1] = 0.0; val[3][2] = 0.0; val[3][3] = 1.0;
	}

	void m4::makeTrans( f64 tx, f64 ty, f64 tz )
	{
		val[0][0] = 1.0; val[0][1] = 0.0; val[0][2] = 0.0; val[0][3] = tx;
		val[1][0] = 0.0; val[1][1] = 1.0; val[1][2] = 0.0; val[1][3] = ty;
		val[2][0] = 0.0; val[2][1] = 0.0; val[2][2] = 1.0; val[2][3] = tz;
		val[3][0] = 0.0; val[3][1] = 0.0; val[3][2] = 0.0; val[3][3] = 1.0;
	}

	m4 m4::getTrans( const v3& v )
	{
		m4 r;

		r.val[0][0] = 1.0; r.val[0][1] = 0.0; r.val[0][2] = 0.0; r.val[0][3] = v.x;
		r.val[1][0] = 0.0; r.val[1][1] = 1.0; r.val[1][2] = 0.0; r.val[1][3] = v.y;
		r.val[2][0] = 0.0; r.val[2][1] = 0.0; r.val[2][2] = 1.0; r.val[2][3] = v.z;
		r.val[3][0] = 0.0; r.val[3][1] = 0.0; r.val[3][2] = 0.0; r.val[3][3] = 1.0;

		return r;
	}

	m4 m4::getTrans( f64 t_x, f64 t_y, f64 t_z )
	{
		m4 r;

		r.val[0][0] = 1.0; r.val[0][1] = 0.0; r.val[0][2] = 0.0; r.val[0][3] = t_x;
		r.val[1][0] = 0.0; r.val[1][1] = 1.0; r.val[1][2] = 0.0; r.val[1][3] = t_y;
		r.val[2][0] = 0.0; r.val[2][1] = 0.0; r.val[2][2] = 1.0; r.val[2][3] = t_z;
		r.val[3][0] = 0.0; r.val[3][1] = 0.0; r.val[3][2] = 0.0; r.val[3][3] = 1.0;

		return r;
	}

	void m4::setScale( const v3& v )
	{
		val[0][0] = v.x;
		val[1][1] = v.y;
		val[2][2] = v.z;
	}

	m4 m4::getScale( const v3& v )
	{
		m4 r;
		r.val[0][0] = v.x; r.val[0][1] = 0.0; r.val[0][2] = 0.0; r.val[0][3] = 0.0;
		r.val[1][0] = 0.0; r.val[1][1] = v.y; r.val[1][2] = 0.0; r.val[1][3] = 0.0;
		r.val[2][0] = 0.0; r.val[2][1] = 0.0; r.val[2][2] = v.z; r.val[2][3] = 0.0;
		r.val[3][0] = 0.0; r.val[3][1] = 0.0; r.val[3][2] = 0.0; r.val[3][3] = 1.0;

		return r;
	}

	m4 m4::getScale( f64 s_x, f64 s_y, f64 s_z )
	{
		m4 r;
		r.val[0][0] = s_x; r.val[0][1] = 0.0; r.val[0][2] = 0.0; r.val[0][3] = 0.0;
		r.val[1][0] = 0.0; r.val[1][1] = s_y; r.val[1][2] = 0.0; r.val[1][3] = 0.0;
		r.val[2][0] = 0.0; r.val[2][1] = 0.0; r.val[2][2] = s_z; r.val[2][3] = 0.0;
		r.val[3][0] = 0.0; r.val[3][1] = 0.0; r.val[3][2] = 0.0; r.val[3][3] = 1.0;

		return r;
	}

	void m4::extract3x3Matrix(m3& m3x3) const
	{
		m3x3.val[0][0] = (f32)val[0][0];
		m3x3.val[0][1] = (f32)val[0][1];
		m3x3.val[0][2] = (f32)val[0][2];
		m3x3.val[1][0] = (f32)val[1][0];
		m3x3.val[1][1] = (f32)val[1][1];
		m3x3.val[1][2] = (f32)val[1][2];
		m3x3.val[2][0] = (f32)val[2][0];
		m3x3.val[2][1] = (f32)val[2][1];
		m3x3.val[2][2] = (f32)val[2][2];

	}

	quat m4::extractQuaternion() const
	{
		m3 m3x3;
		extract3x3Matrix(m3x3);
		return quat(m3x3);
	}

	m4 m4::operator*(f64 scalar) const
	{
		return m4(
			scalar*val[0][0], scalar*val[0][1], scalar*val[0][2], scalar*val[0][3],
			scalar*val[1][0], scalar*val[1][1], scalar*val[1][2], scalar*val[1][3],
			scalar*val[2][0], scalar*val[2][1], scalar*val[2][2], scalar*val[2][3],
			scalar*val[3][0], scalar*val[3][1], scalar*val[3][2], scalar*val[3][3]);
	}

    m4 m4::adjoint() const
    {
        return m4( MINOR(*this, 1, 2, 3, 1, 2, 3),
            -MINOR(*this, 0, 2, 3, 1, 2, 3),
            MINOR(*this, 0, 1, 3, 1, 2, 3),
            -MINOR(*this, 0, 1, 2, 1, 2, 3),

            -MINOR(*this, 1, 2, 3, 0, 2, 3),
            MINOR(*this, 0, 2, 3, 0, 2, 3),
            -MINOR(*this, 0, 1, 3, 0, 2, 3),
            MINOR(*this, 0, 1, 2, 0, 2, 3),

            MINOR(*this, 1, 2, 3, 0, 1, 3),
            -MINOR(*this, 0, 2, 3, 0, 1, 3),
            MINOR(*this, 0, 1, 3, 0, 1, 3),
            -MINOR(*this, 0, 1, 2, 0, 1, 3),

            -MINOR(*this, 1, 2, 3, 0, 1, 2),
            MINOR(*this, 0, 2, 3, 0, 1, 2),
            -MINOR(*this, 0, 1, 3, 0, 1, 2),
            MINOR(*this, 0, 1, 2, 0, 1, 2));
    }
    //-----------------------------------------------------------------------
    f64 m4::determinant() const
    {
        return val[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
            val[0][1] * MINOR(*this, 1, 2, 3, 0, 2, 3) +
            val[0][2] * MINOR(*this, 1, 2, 3, 0, 1, 3) -
            val[0][3] * MINOR(*this, 1, 2, 3, 0, 1, 2);
    }
    //-----------------------------------------------------------------------
    m4 m4::inverse() const
    {
        f64 m00 = val[0][0], m01 = val[0][1], m02 = val[0][2], m03 = val[0][3];
        f64 m10 = val[1][0], m11 = val[1][1], m12 = val[1][2], m13 = val[1][3];
        f64 m20 = val[2][0], m21 = val[2][1], m22 = val[2][2], m23 = val[2][3];
        f64 m30 = val[3][0], m31 = val[3][1], m32 = val[3][2], m33 = val[3][3];

        f64 v0 = m20 * m31 - m21 * m30;
        f64 v1 = m20 * m32 - m22 * m30;
        f64 v2 = m20 * m33 - m23 * m30;
        f64 v3 = m21 * m32 - m22 * m31;
        f64 v4 = m21 * m33 - m23 * m31;
        f64 v5 = m22 * m33 - m23 * m32;

        f64 t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
        f64 t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
        f64 t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
        f64 t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

        f64 invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

        f64 d00 = t00 * invDet;
        f64 d10 = t10 * invDet;
        f64 d20 = t20 * invDet;
        f64 d30 = t30 * invDet;

        f64 d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        f64 d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        f64 d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        f64 d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m10 * m31 - m11 * m30;
        v1 = m10 * m32 - m12 * m30;
        v2 = m10 * m33 - m13 * m30;
        v3 = m11 * m32 - m12 * m31;
        v4 = m11 * m33 - m13 * m31;
        v5 = m12 * m33 - m13 * m32;

        f64 d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        f64 d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        f64 d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        f64 d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m21 * m10 - m20 * m11;
        v1 = m22 * m10 - m20 * m12;
        v2 = m23 * m10 - m20 * m13;
        v3 = m22 * m11 - m21 * m12;
        v4 = m23 * m11 - m21 * m13;
        v5 = m23 * m12 - m22 * m13;

        f64 d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        f64 d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        f64 d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        f64 d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        return m4(
            d00, d01, d02, d03,
            d10, d11, d12, d13,
            d20, d21, d22, d23,
            d30, d31, d32, d33);
    }
    //-----------------------------------------------------------------------
    m4 m4::inverseAffine(void) const
    {
        assert(isAffine());

        f64 m10 = val[1][0], m11 = val[1][1], m12 = val[1][2];
        f64 m20 = val[2][0], m21 = val[2][1], m22 = val[2][2];

        f64 t00 = m22 * m11 - m21 * m12;
        f64 t10 = m20 * m12 - m22 * m10;
        f64 t20 = m21 * m10 - m20 * m11;

        f64 m00 = val[0][0], m01 = val[0][1], m02 = val[0][2];

        f64 invDet = 1 / (m00 * t00 + m01 * t10 + m02 * t20);

        t00 *= invDet; t10 *= invDet; t20 *= invDet;

        m00 *= invDet; m01 *= invDet; m02 *= invDet;

        f64 r00 = t00;
        f64 r01 = m02 * m21 - m01 * m22;
        f64 r02 = m01 * m12 - m02 * m11;

        f64 r10 = t10;
        f64 r11 = m00 * m22 - m02 * m20;
        f64 r12 = m02 * m10 - m00 * m12;

        f64 r20 = t20;
        f64 r21 = m01 * m20 - m00 * m21;
        f64 r22 = m00 * m11 - m01 * m10;

        f64 m03 = val[0][3], m13 = val[1][3], m23 = val[2][3];

        f64 r03 = - (r00 * m03 + r01 * m13 + r02 * m23);
        f64 r13 = - (r10 * m03 + r11 * m13 + r12 * m23);
        f64 r23 = - (r20 * m03 + r21 * m13 + r22 * m23);

        return m4(
            r00, r01, r02, r03,
            r10, r11, r12, r13,
            r20, r21, r22, r23,
              0,   0,   0,   1);
    }
    //-----------------------------------------------------------------------
    void m4::makeTransform(const v3& position, const v3& scale, const quat& orientation)
    {
        // Ordering:
        //    1. Scale
        //    2. Rotate
        //    3. Translate

        m3 rot3x3, scale3x3;
        orientation.ToRotationMatrix(rot3x3);
		scale3x3 = m3::zero;
        scale3x3[0][0] = scale.x;
        scale3x3[1][1] = scale.y;
        scale3x3[2][2] = scale.z;

        // Set up final matrix with scale, rotation and translation
        *this = rot3x3 * scale3x3;
        this->setTrans(position);

        // No projection term
        val[3][0] = 0; val[3][1] = 0; val[3][2] = 0; val[3][3] = 1;
    }
    //-----------------------------------------------------------------------
    void m4::makeInverseTransform(const v3& position, const v3& scale, const quat& orientation)
    {
        // Invert the parameters
        v3 invTranslate = -position;
        v3 invScale(1 / scale.x, 1 / scale.y, 1 / scale.z);
        quat invRot = orientation.inv();

        // Because we're inverting, order is translation, rotation, scale
        // So make translation relative to scale & rotation
        invTranslate *= invScale; // scale
        invTranslate = invRot * invTranslate; // rotate

        // Next, make a 3x3 rotation matrix and apply inverse scale
        m3 rot3x3, scale3x3;
        invRot.ToRotationMatrix(rot3x3);
		scale3x3 = m3::zero;
        scale3x3[0][0] = invScale.x;
        scale3x3[1][1] = invScale.y;
        scale3x3[2][2] = invScale.z;

        // Set up final matrix with scale, rotation and translation
        *this = scale3x3 * rot3x3;
        this->setTrans(invTranslate);

        // No projection term
        val[3][0] = 0; val[3][1] = 0; val[3][2] = 0; val[3][3] = 1;
    }
	bit m4::isAffine(void) const
	{
		return val[3][0] == 0 && val[3][1] == 0 && val[3][2] == 0 && val[3][3] == 1;
	}
	m4 m4::concatenateAffine(const m4 &m2) const
	{
		assert(isAffine() && m2.isAffine());

		return m4(
			val[0][0] * m2.val[0][0] + val[0][1] * m2.val[1][0] + val[0][2] * m2.val[2][0],
			val[0][0] * m2.val[0][1] + val[0][1] * m2.val[1][1] + val[0][2] * m2.val[2][1],
			val[0][0] * m2.val[0][2] + val[0][1] * m2.val[1][2] + val[0][2] * m2.val[2][2],
			val[0][0] * m2.val[0][3] + val[0][1] * m2.val[1][3] + val[0][2] * m2.val[2][3] + val[0][3],

			val[1][0] * m2.val[0][0] + val[1][1] * m2.val[1][0] + val[1][2] * m2.val[2][0],
			val[1][0] * m2.val[0][1] + val[1][1] * m2.val[1][1] + val[1][2] * m2.val[2][1],
			val[1][0] * m2.val[0][2] + val[1][1] * m2.val[1][2] + val[1][2] * m2.val[2][2],
			val[1][0] * m2.val[0][3] + val[1][1] * m2.val[1][3] + val[1][2] * m2.val[2][3] + val[1][3],

			val[2][0] * m2.val[0][0] + val[2][1] * m2.val[1][0] + val[2][2] * m2.val[2][0],
			val[2][0] * m2.val[0][1] + val[2][1] * m2.val[1][1] + val[2][2] * m2.val[2][1],
			val[2][0] * m2.val[0][2] + val[2][1] * m2.val[1][2] + val[2][2] * m2.val[2][2],
			val[2][0] * m2.val[0][3] + val[2][1] * m2.val[1][3] + val[2][2] * m2.val[2][3] + val[2][3],

			0, 0, 0, 1);
	}
	v3 m4::transformAffine(const v3& v) const
	{
		assert(isAffine());

		return v3(
			(f32)val[0][0] * v.x + (f32)val[0][1] * v.y + (f32)val[0][2] * v.z + (f32)val[0][3], 
			(f32)val[1][0] * v.x + (f32)val[1][1] * v.y + (f32)val[1][2] * v.z + (f32)val[1][3],
			(f32)val[2][0] * v.x + (f32)val[2][1] * v.y + (f32)val[2][2] * v.z + (f32)val[2][3]);
	}
	v4 m4::transformAffine(const v4& v) const
	{
		assert(isAffine());

		return v4(
			(f32)val[0][0] * v.x + (f32)val[0][1] * v.y + (f32)val[0][2] * v.z + (f32)val[0][3] * v.w, 
			(f32)val[1][0] * v.x + (f32)val[1][1] * v.y + (f32)val[1][2] * v.z + (f32)val[1][3] * v.w,
			(f32)val[2][0] * v.x + (f32)val[2][1] * v.y + (f32)val[2][2] * v.z + (f32)val[2][3] * v.w,
			v.w);
	}
	v4 operator * (const v4& v, const m4& mat)
	{
		return v4(
			v.x*(f32)mat[0][0] + v.y*(f32)mat[1][0] + v.z*(f32)mat[2][0] + v.w*(f32)mat[3][0],
			v.x*(f32)mat[0][1] + v.y*(f32)mat[1][1] + v.z*(f32)mat[2][1] + v.w*(f32)mat[3][1],
			v.x*(f32)mat[0][2] + v.y*(f32)mat[1][2] + v.z*(f32)mat[2][2] + v.w*(f32)mat[3][2],
			v.x*(f32)mat[0][3] + v.y*(f32)mat[1][3] + v.z*(f32)mat[2][3] + v.w*(f32)mat[3][3]
		);
	}
}
