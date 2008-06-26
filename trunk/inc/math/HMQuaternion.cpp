#include "math/HMath.h"
namespace hmath
{
	const quat quat::zero(0.0,0.0,0.0,0.0);
	const quat quat::id(1.0,0.0,0.0,0.0);

	//————————————————————————————————————————————————————————————————————————————————————————

	void quat::FromAxes (const v3* akAxis)
	{
		m3 kRot;

		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			kRot[0][iCol] = akAxis[iCol].x;
			kRot[1][iCol] = akAxis[iCol].y;
			kRot[2][iCol] = akAxis[iCol].z;
		}

		FromRotationMatrix(kRot);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void quat::FromAxes (const v3& xAxis, const v3& yAxis, const v3& zAxis)
	{
		m3 kRot;

		kRot[0][0] = xAxis.x;
		kRot[1][0] = xAxis.y;
		kRot[2][0] = xAxis.z;

		kRot[0][1] = yAxis.x;
		kRot[1][1] = yAxis.y;
		kRot[2][1] = yAxis.z;

		kRot[0][2] = zAxis.x;
		kRot[1][2] = zAxis.y;
		kRot[2][2] = zAxis.z;

		FromRotationMatrix(kRot);
	}

	void quat::FromEuler(rad psi,rad theta,rad phi)
	{
		m3 mat;
		mat.FromEulerAnglesXYZ(theta,psi,phi);
		FromRotationMatrix(mat);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void quat::FromRotationMatrix (const m3& kRot)
	{
		f32 fTrace = kRot[0][0]+kRot[1][1]+kRot[2][2];
		f32 fRoot;

		if ( fTrace > f32(0.0) )
		{
			fRoot = sqrt(fTrace + f32(1.0));  // 2w
			w = f32(0.5)*fRoot;
			fRoot = f32(0.5)/fRoot;  // 1/(4w)
			x = (kRot[2][1]-kRot[1][2])*fRoot;
			y = (kRot[0][2]-kRot[2][0])*fRoot;
			z = (kRot[1][0]-kRot[0][1])*fRoot;
		}
		else
		{
			// |w| <= 1/2
			static u32 s_iNext[3] = { 1, 2, 0 };
			u32 i = 0;
			if ( kRot[1][1] > kRot[0][0] )
				i = 1;
			if ( kRot[2][2] > kRot[i][i] )
				i = 2;
			u32 j = s_iNext[i];
			u32 k = s_iNext[j];

			fRoot = sqrt(kRot[i][i]-kRot[j][j]-kRot[k][k] + f32(1.0));
			f32* apkQuat[3] = { &x, &y, &z };
			*apkQuat[i] = f32(0.5)*fRoot;
			fRoot = f32(0.5)/fRoot;
			w = (kRot[k][j]-kRot[j][k])*fRoot;
			*apkQuat[j] = (kRot[j][i]+kRot[i][j])*fRoot;
			*apkQuat[k] = (kRot[k][i]+kRot[i][k])*fRoot;
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void quat::ToRotationMatrix (m3& kRot) const
	{
		f32 fTx  = f32(2.0)*x;
		f32 fTy  = f32(2.0)*y;
		f32 fTz  = f32(2.0)*z;
		f32 fTwx = fTx*w;
		f32 fTwy = fTy*w;
		f32 fTwz = fTz*w;
		f32 fTxx = fTx*x;
		f32 fTxy = fTy*x;
		f32 fTxz = fTz*x;
		f32 fTyy = fTy*y;
		f32 fTyz = fTz*y;
		f32 fTzz = fTz*z;

		kRot[0][0] = f32(1.0)-(fTyy+fTzz);
		kRot[0][1] = fTxy-fTwz;
		kRot[0][2] = fTxz+fTwy;
		kRot[1][0] = fTxy+fTwz;
		kRot[1][1] = f32(1.0)-(fTxx+fTzz);
		kRot[1][2] = fTyz-fTwx;
		kRot[2][0] = fTxz-fTwy;
		kRot[2][1] = fTyz+fTwx;
		kRot[2][2] = f32(1.0)-(fTxx+fTyy);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat quat::exp () const
	{
		rad fAngle ( sqrt(x*x+y*y+z*z) );
		f32 fSin = sin(fAngle.asRad());

		quat kResult;
		kResult.w = cos(fAngle.asRad());

		if ( fabs(fSin) >= fEpsilon )
		{
			f32 fCoeff = fSin/(fAngle.asRad());
			kResult.x = fCoeff*x;
			kResult.y = fCoeff*y;
			kResult.z = fCoeff*z;
		}
		else
		{
			kResult.x = x;
			kResult.y = y;
			kResult.z = z;
		}

		return kResult;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	quat quat::log () const
	{
		quat kResult;
		kResult.w = 0.0;

		if ( fabs(w) < 1.0 )
		{
			rad fAngle ( acos(w) );
			f32 fSin = sin(fAngle.asRad());
			if ( abs(fSin) >= fEpsilon )
			{
				f32 fCoeff = fAngle.asRad()/fSin;
				kResult.x = fCoeff*x;
				kResult.y = fCoeff*y;
				kResult.z = fCoeff*z;
				return kResult;
			}
		}

		kResult.x = x;
		kResult.y = y;
		kResult.z = z;

		return kResult;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void quat::ToAngleAxis (rad& rfAngle, v3& rkAxis) const
	{
		f32 fSqrLength = x*x+y*y+z*z;
		if ( fSqrLength > 0.0 )
		{
			rfAngle = f32(2.0)*acos(w);
			f32 fInvLength = InvSqrt(fSqrLength);
			rkAxis.x = x*fInvLength;
			rkAxis.y = y*fInvLength;
			rkAxis.z = z*fInvLength;
		}
		else
		{
			rfAngle = rad(0.0);
			rkAxis.x = 1.0;
			rkAxis.y = 0.0;
			rkAxis.z = 0.0;
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void quat::ToAxes (v3* akAxis) const
	{
		m3 kRot;

		ToRotationMatrix(kRot);

		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			akAxis[iCol].x = kRot[0][iCol];
			akAxis[iCol].y = kRot[1][iCol];
			akAxis[iCol].z = kRot[2][iCol];
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void quat::ToAxes (v3& xAxis, v3& yAxis, v3& zAxis) const
	{
		m3 kRot;

		ToRotationMatrix(kRot);

		xAxis.x = kRot[0][0];
		xAxis.y = kRot[1][0];
		xAxis.z = kRot[2][0];

		yAxis.x = kRot[0][1];
		yAxis.y = kRot[1][1];
		yAxis.z = kRot[2][1];

		zAxis.x = kRot[0][2];
		zAxis.y = kRot[1][2];
		zAxis.z = kRot[2][2];
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void quat::FromAngleAxis (const rad& rfAngle, const v3& rkAxis)
	{
		rad fHalfAngle ( 0.5*rfAngle );
		f32 fSin = sin(fHalfAngle.asRad());
		w = cos(fHalfAngle.asRad());
		x = fSin*rkAxis.x;
		y = fSin*rkAxis.y;
		z = fSin*rkAxis.z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void quat::ToAngleAxis (deg& dAngle, v3& rkAxis) const 
	{
		rad rAngle;
		ToAngleAxis ( rAngle, rkAxis );
		dAngle = rAngle;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 quat::xAxis(void) const
	{
		f32 fTy  = f32(2.0)*y;
		f32 fTz  = f32(2.0)*z;
		f32 fTwy = fTy*w;
		f32 fTwz = fTz*w;
		f32 fTxy = fTy*x;
		f32 fTxz = fTz*x;
		f32 fTyy = fTy*y;
		f32 fTzz = fTz*z;

		return v3(f32(1.0)-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 quat::yAxis(void) const
	{
		f32 fTx  = f32(2.0)*x;
		f32 fTy  = f32(2.0)*y;
		f32 fTz  = f32(2.0)*z;
		f32 fTwx = fTx*w;
		f32 fTwz = fTz*w;
		f32 fTxx = fTx*x;
		f32 fTxy = fTy*x;
		f32 fTyz = fTz*y;
		f32 fTzz = fTz*z;

		return v3(fTxy-fTwz, f32(1.0)-(fTxx+fTzz), fTyz+fTwx);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 quat::zAxis(void) const
	{
		f32 fTx  = f32(2.0)*x;
		f32 fTy  = f32(2.0)*y;
		f32 fTz  = f32(2.0)*z;
		f32 fTwx = fTx*w;
		f32 fTwy = fTy*w;
		f32 fTxx = fTx*x;
		f32 fTxz = fTz*x;
		f32 fTyy = fTy*y;
		f32 fTyz = fTz*y;

		return v3(fTxz+fTwy, fTyz-fTwx, f32(1.0)-(fTxx+fTyy));
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 quat::operator* (const v3& v) const
	{
		v3 uv, uuv;
		v3 qvec(x, y, z);
		uv   = qvec.cross(v);
		uuv  = qvec.cross(uv);
		uv  *= f32(2.0) * w;
		uuv *= f32(2.0);

		return v + uv + uuv;
	}
};