#ifndef HYPERMATH_M3
#define HYPERMATH_M3
#include "math/HMath.h"
namespace hmath
{
	class m3
	{
		public:
		f32 val[3][3];
		inline m3 ();
		inline explicit m3 (const f32 arr[3][3]);
		inline m3 (const m3& rkMatrix);
		inline m3 (f32 v00, f32 v01, f32 v02,
			       f32 v10, f32 v11, f32 v12,
			       f32 v20, f32 v21, f32 v22);
		
		v3 GetColumn (u32 iCol) const;
		void SetColumn(u32 iCol, const v3& vec);
		inline void FromAxes(const v3& xAxis, const v3& yAxis, const v3& zAxis);

		inline f32* operator[] (u32 iRow) const;
		inline m3& operator=  (const m3& rkMatrix);		
		inline bit operator!= (const m3& rkMatrix) const;
		bit operator== (const m3& rkMatrix) const;
		m3  operator+  (const m3& rkMatrix) const;
		m3  operator-  (const m3& rkMatrix) const;
		m3  operator*  (const m3& rkMatrix) const;
		m3  operator-  () const;
		v3  operator*  (const v3& rkVector) const;
		v3_64  operator*  (const v3_64& rkVector) const;
		m3  operator*  (f32 fScalar) const;

		m3 trans () const;
		bit inv (m3& rkInverse, f32 fTolerance = 1e-06) const;
		inline m3 inv (f32 fTolerance = 1e-06) const;
		f32 det () const;

		void ToAxisAngle (v3& rkAxis, rad& rfAngle) const;
		inline void ToAxisAngle (v3& rkAxis, deg& rfAngle) const;
		void FromAxisAngle (const v3& rkAxis, const rad& frads);

		bit ToEulerAnglesXYZ (rad& rfYAngle, rad& rfPAngle,rad& rfRAngle) const; //
		bit ToEulerAnglesXZY (rad& rfYAngle, rad& rfPAngle,rad& rfRAngle) const; //
		bit ToEulerAnglesYXZ (rad& rfYAngle, rad& rfPAngle,rad& rfRAngle) const; //
		bit ToEulerAnglesYZX (rad& rfYAngle, rad& rfPAngle,rad& rfRAngle) const; // 
		bit ToEulerAnglesZXY (rad& rfYAngle, rad& rfPAngle,rad& rfRAngle) const; //
		bit ToEulerAnglesZYX (rad& rfYAngle, rad& rfPAngle,rad& rfRAngle) const; //
		void FromEulerAnglesXYZ (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle);
		void FromEulerAnglesXZY (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle);
		void FromEulerAnglesYXZ (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle);
		void FromEulerAnglesYZX (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle);
		void FromEulerAnglesZXY (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle);
		void FromEulerAnglesZYX (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle);

		static const m3 zero;
		static const m3 id;
	};

	//====================================================================================

	m3::m3 ()
	{
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3::m3 (const f32 arr[3][3])
	{
		memcpy(val,arr,9*sizeof(f32));
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3::m3 (const m3& rkMatrix)
	{
		memcpy(val,rkMatrix.val,9*sizeof(f32));
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3::m3 (f32 v00, f32 v01, f32 v02,
		    f32 v10, f32 v11, f32 v12,
		    f32 v20, f32 v21, f32 v22)
	{
		val[0][0] = v00;
		val[0][1] = v01;
		val[0][2] = v02;
		val[1][0] = v10;
		val[1][1] = v11;
		val[1][2] = v12;
		val[2][0] = v20;
		val[2][1] = v21;
		val[2][2] = v22;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3 m3::inv (f32 fTolerance) const
	{
		m3 kInverse = m3::zero;
		inv(kInverse,fTolerance);
		return kInverse;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::FromAxes(const v3& xAxis, const v3& yAxis, const v3& zAxis)
	{
		SetColumn(0,xAxis);
		SetColumn(1,yAxis);
		SetColumn(2,zAxis);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::ToAxisAngle (v3& rkAxis, deg& rfAngle) const 
	{
		rad r;
		ToAxisAngle ( rkAxis, r );
		rfAngle = r;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32* m3::operator[] (u32 iRow) const
	{
		return (f32*)val[iRow];
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3& m3::operator= (const m3& rkMatrix)
	{
		memcpy(val,rkMatrix.val,9*sizeof(f32));
		return *this;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit m3::operator!= (const m3& rkMatrix) const
	{
		return !operator==(rkMatrix);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	extern v3 operator* (const v3& rkVector,const m3& rkMatrix);
	extern m3 operator* (f32 fScalar, const m3& rkMatrix);

};
#endif
