#ifndef HYPERMATH_M4
#define HYPERMATH_M4

#include "math/HMath.h"
using namespace hmath;

namespace hmath
{
    class m4
    {
    public:
        union {
            f64 val[4][4];
            f64 _val[16];
        };
    
        m4();
        m4( f64 m00, f64 m01, f64 m02, f64 m03,
            f64 m10, f64 m11, f64 m12, f64 m13,
            f64 m20, f64 m21, f64 m22, f64 m23,
            f64 m30, f64 m31, f64 m32, f64 m33 );

        m4(const m3& m3x3);
        m4(const quat& rot);       
		void set( f64 m00, f64 m01, f64 m02, f64 m03,
			      f64 m10, f64 m11, f64 m12, f64 m13,
			      f64 m20, f64 m21, f64 m22, f64 m23,
			      f64 m30, f64 m31, f64 m32, f64 m33 );
        f64* operator [] ( size_t iRow );
        const f64 *const operator [] ( size_t iRow ) const;
        m4 concatenate(const m4 &m2) const;
        m4 operator * ( const m4 &m2 ) const;
        v3 operator * ( const v3 &v ) const;
        v4 operator * (const v4& v) const;
        m4 operator + ( const m4 &m2 ) const;
        m4 operator - ( const m4 &m2 ) const;
        bit operator == ( const m4& m2 ) const;
        bit operator != ( const m4& m2 ) const;
        void operator = ( const m3& mat3 );
        m4 transpose(void) const;
        void setTrans( const v3& v );
        v3 getTrans() const;       
        void makeTrans( const v3& v );
        void makeTrans( f64 tx, f64 ty, f64 tz );
        static m4 getTrans( const v3& v );
        static m4 getTrans( f64 t_x, f64 t_y, f64 t_z );
        void setScale( const v3& v );
        static m4 getScale( const v3& v );
        static m4 getScale( f64 s_x, f64 s_y, f64 s_z );
        void extract3x3Matrix(m3& m3x3) const;
        quat extractQuaternion() const;
        static const m4 ZERO;
        static const m4 IDENTITY;
        static const m4 CLIPSPACE2DTOIMAGESPACE;
        m4 operator*(f64 scalar) const;
		m4 adjoint() const;
		f64 determinant() const;
		m4 inverse() const;
        void makeTransform(const v3& position, const v3& scale, const quat& orientation);
        void makeInverseTransform(const v3& position, const v3& scale, const quat& orientation);
        bit isAffine(void) const;
        m4 inverseAffine(void) const;
        m4 concatenateAffine(const m4 &m2) const;
        v3 transformAffine(const v3& v) const;
        v4 transformAffine(const v4& v) const;
    };
    extern v4 operator * (const v4& v, const m4& mat);

}
#endif
