#include "math/HMath.h"

namespace hmath
{
	const m3 m3::zero(0,0,0,0,0,0,0,0,0);
	const m3 m3::id(1,0,0,0,1,0,0,0,1);

	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::FromAxisAngle (const v3& rkAxis, const rad& frads)
	{
		f32 fCos = cos(frads.asRad());
		f32 fSin = sin(frads.asRad());
		f32 fOneMinusCos = f32(1.0)-fCos;
		f32 fX2 = rkAxis.x*rkAxis.x;
		f32 fY2 = rkAxis.y*rkAxis.y;
		f32 fZ2 = rkAxis.z*rkAxis.z;
		f32 fXYM = rkAxis.x*rkAxis.y*fOneMinusCos;
		f32 fXZM = rkAxis.x*rkAxis.z*fOneMinusCos;
		f32 fYZM = rkAxis.y*rkAxis.z*fOneMinusCos;
		f32 fXSin = rkAxis.x*fSin;
		f32 fYSin = rkAxis.y*fSin;
		f32 fZSin = rkAxis.z*fSin;

		val[0][0] = fX2*fOneMinusCos+fCos;
		val[0][1] = fXYM-fZSin;
		val[0][2] = fXZM+fYSin;
		val[1][0] = fXYM+fZSin;
		val[1][1] = fY2*fOneMinusCos+fCos;
		val[1][2] = fYZM-fXSin;
		val[2][0] = fXZM-fYSin;
		val[2][1] = fYZM+fXSin;
		val[2][2] = fZ2*fOneMinusCos+fCos;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit m3::ToEulerAnglesXYZ (rad& rfYAngle, rad& rfPAngle, rad& rfRAngle) const
	{
		rfPAngle = rad(asin(val[0][2]));
		if ( rfPAngle < rad((f32)HALF_PI) )
		{
			if ( rfPAngle > rad((f32)-HALF_PI) )
			{
				rfYAngle = atan2(-val[1][2],val[2][2]);
				rfRAngle = atan2(-val[0][1],val[0][0]);
				return true;
			}
			else
			{
				rad fRmY = rad(atan2(val[1][0],val[1][1]));
				rfRAngle = rad(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			rad fRpY = rad(atan2(val[1][0],val[1][1]));
			rfRAngle = rad(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit m3::ToEulerAnglesXZY (rad& rfYAngle, rad& rfPAngle,rad& rfRAngle) const
	{
		rfPAngle = asin(-val[0][1]);
		if ( rfPAngle < rad((f32)HALF_PI) )
		{
			if ( rfPAngle > rad((f32)-HALF_PI) )
			{
				rfYAngle = atan2(val[2][1],val[1][1]);
				rfRAngle = atan2(val[0][2],val[0][0]);
				return true;
			}
			else
			{
				rad fRmY = rad(atan2(-val[2][0],val[2][2]));
				rfRAngle = rad(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			rad fRpY = rad(atan2(-val[2][0],val[2][2]));
			rfRAngle = rad(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit m3::ToEulerAnglesYXZ (rad& rfYAngle, rad& rfPAngle, rad& rfRAngle) const
	{
		rfPAngle = asin(-val[1][2]);
		if ( rfPAngle < rad((f32)HALF_PI) )
		{
			if ( rfPAngle > rad((f32)-HALF_PI) )
			{
				rfYAngle = atan2(val[0][2],val[2][2]);
				rfRAngle = atan2(val[1][0],val[1][1]);
				return true;
			}
			else
			{
				rad fRmY = rad(atan2(-val[0][1],val[0][0]));
				rfRAngle = rad(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			rad fRpY = rad(atan2(-val[0][1],val[0][0]));
			rfRAngle = rad(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit m3::ToEulerAnglesYZX (rad& rfYAngle, rad& rfPAngle, rad& rfRAngle) const
	{
		rfPAngle = asin(val[1][0]);
		if ( rfPAngle < rad((f32)HALF_PI) )
		{
			if ( rfPAngle > rad((f32)-HALF_PI) )
			{
				rfYAngle = atan2(-val[2][0],val[0][0]);
				rfRAngle = atan2(-val[1][2],val[1][1]);
				return true;
			}
			else
			{
				rad fRmY = rad(atan2(val[2][1],val[2][2]));
				rfRAngle = rad(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			rad fRpY = rad(atan2(val[2][1],val[2][2]));
			rfRAngle = rad(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit m3::ToEulerAnglesZXY (rad& rfYAngle, rad& rfPAngle, rad& rfRAngle) const
	{
		rfPAngle = asin(val[2][1]);
		if ( rfPAngle < rad((f32)HALF_PI) )
		{
			if ( rfPAngle > rad((f32)-HALF_PI) )
			{
				rfYAngle = atan2(-val[0][1],val[1][1]);
				rfRAngle = atan2(-val[2][0],val[2][2]);
				return true;
			}
			else
			{
				rad fRmY = rad(atan2(val[0][2],val[0][0]));
				rfRAngle = rad(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			rad fRpY = rad(atan2(val[0][2],val[0][0]));
			rfRAngle = rad(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit m3::ToEulerAnglesZYX (rad& rfYAngle, rad& rfPAngle,rad& rfRAngle) const
	{
		rfPAngle = asin(-val[2][0]);
		if ( rfPAngle < rad((f32)HALF_PI) )
		{
			if ( rfPAngle > rad((f32)-HALF_PI) )
			{
				rfYAngle = atan2(val[1][0],val[0][0]);
				rfRAngle = atan2(val[2][1],val[2][2]);
				return true;
			}
			else
			{
				rad fRmY = rad(atan2(-val[0][1],val[0][2]));
				rfRAngle = rad(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			rad fRpY = rad(atan2(-val[0][1],val[0][2]));
			rfRAngle = rad(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::FromEulerAnglesXYZ (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle)
	{
		f32 fCos, fSin;

		fCos = cos(fYAngle.asRad());
		fSin = sin(fYAngle.asRad());
		m3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		fCos = cos(fPAngle.asRad());
		fSin = sin(fPAngle.asRad());
		m3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		fCos = cos(fRAngle.asRad());
		fSin = sin(fRAngle.asRad());
		m3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		*this = kXMat*(kYMat*kZMat);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::FromEulerAnglesXZY (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle)
	{
		f32 fCos, fSin;

		fCos = cos(fYAngle.asRad());
		fSin = sin(fYAngle.asRad());
		m3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		fCos = cos(fPAngle.asRad());
		fSin = sin(fPAngle.asRad());
		m3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		fCos = cos(fRAngle.asRad());
		fSin = sin(fRAngle.asRad());
		m3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		*this = kXMat*(kZMat*kYMat);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::FromEulerAnglesYXZ (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle)
	{
		f32 fCos, fSin;

		fCos = cos(fYAngle.asRad());
		fSin = sin(fYAngle.asRad());
		m3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		fCos = cos(fPAngle.asRad());
		fSin = sin(fPAngle.asRad());
		m3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		fCos = cos(fRAngle.asRad());
		fSin = sin(fRAngle.asRad());
		m3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		*this = kYMat*(kXMat*kZMat);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::FromEulerAnglesYZX (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle)
	{
		f32 fCos, fSin;

		fCos = cos(fYAngle.asRad());
		fSin = sin(fYAngle.asRad());
		m3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		fCos = cos(fPAngle.asRad());
		fSin = sin(fPAngle.asRad());
		m3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		fCos = cos(fRAngle.asRad());
		fSin = sin(fRAngle.asRad());
		m3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		*this = kYMat*(kZMat*kXMat);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::FromEulerAnglesZXY (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle)
	{
		f32 fCos, fSin;

		fCos = cos(fYAngle.asRad());
		fSin = sin(fYAngle.asRad());
		m3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		fCos = cos(fPAngle.asRad());
		fSin = sin(fPAngle.asRad());
		m3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		fCos = cos(fRAngle.asRad());
		fSin = sin(fRAngle.asRad());
		m3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		*this = kZMat*(kXMat*kYMat);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::FromEulerAnglesZYX (const rad& fYAngle, const rad& fPAngle, const rad& fRAngle)
	{
		f32 fCos, fSin;

		fCos = cos(fYAngle.asRad());
		fSin = sin(fYAngle.asRad());
		m3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		fCos = cos(fPAngle.asRad());
		fSin = sin(fPAngle.asRad());
		m3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		fCos = cos(fRAngle.asRad());
		fSin = sin(fRAngle.asRad());
		m3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		*this = kZMat*(kYMat*kXMat);
	}

	//————————————————————————————————————————————————————————————————————————————————————————
	
	v3 operator* (const v3& rkVector,const m3& rkMatrix)
	{
		v3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			kProd[iRow] =
				rkVector[0]*rkMatrix.val[0][iRow] +
				rkVector[1]*rkMatrix.val[1][iRow] +
				rkVector[2]*rkMatrix.val[2][iRow];
		}
		return kProd;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3 operator* (f32 fScalar, const m3& rkMatrix)
	{
		m3 kProd;
		for (u32 iRow = 0; iRow < 3; iRow++)
		{
			for (u32 iCol = 0; iCol < 3; iCol++)
			{
				kProd[iRow][iCol] = fScalar * rkMatrix.val[iRow][iCol];
			}
		}
		return kProd;
	}


	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::ToAxisAngle (v3& rkAxis, rad& rfAngle) const
	{
		f32 fTrace = val[0][0] + val[1][1] + val[2][2];
		f32 fCos = f32(0.5)*(fTrace-f32(1.0));
		rfAngle = acos(fCos);  // in [0,PI]

		if ( rfAngle > rad(0.0) )
		{
			if ( rfAngle < rad((f32)PI) )
			{
				rkAxis.x = val[2][1]-val[1][2];
				rkAxis.y = val[0][2]-val[2][0];
				rkAxis.z = val[1][0]-val[0][1];
				rkAxis.norm();
			}
			else
			{
				f32 fHalfInverse;
				if ( val[0][0] >= val[1][1] )
				{
					if ( val[0][0] >= val[2][2] )
					{
						rkAxis.x = f32(0.5)*sqrt(val[0][0] - val[1][1] - val[2][2] + f32(1.0));
						fHalfInverse = f32(0.5)/rkAxis.x;
						rkAxis.y = fHalfInverse*val[0][1];
						rkAxis.z = fHalfInverse*val[0][2];
					}
					else
					{
						rkAxis.z = f32(0.5)*sqrt(val[2][2] - val[0][0] - val[1][1] + f32(1.0));
						fHalfInverse = f32(0.5)/rkAxis.z;
						rkAxis.x = fHalfInverse*val[0][2];
						rkAxis.y = fHalfInverse*val[1][2];
					}
				}
				else
				{
					if ( val[1][1] >= val[2][2] )
					{
						rkAxis.y = f32(0.5)*sqrt(val[1][1] -val[0][0] - val[2][2] + f32(1.0));
						fHalfInverse  = f32(0.5)/rkAxis.y;
						rkAxis.x = fHalfInverse*val[0][1];
						rkAxis.z = fHalfInverse*val[1][2];
					}
					else
					{
						rkAxis.z = f32(0.5)*sqrt(val[2][2] - val[0][0] - val[1][1] + f32(1.0));
						fHalfInverse = f32(0.5)/rkAxis.z;
						rkAxis.x = fHalfInverse*val[0][2];
						rkAxis.y = fHalfInverse*val[1][2];
					}
				}
			}
		}
		else
		{
			rkAxis.x = f32(1.0);
			rkAxis.y = f32(0.0);
			rkAxis.z = f32(0.0);
		}
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit m3::inv (m3& rkInverse, f32 fTolerance) const
	{
		rkInverse[0][0] = val[1][1]*val[2][2] - val[1][2]*val[2][1];
		rkInverse[0][1] = val[0][2]*val[2][1] - val[0][1]*val[2][2];
		rkInverse[0][2] = val[0][1]*val[1][2] - val[0][2]*val[1][1];
		rkInverse[1][0] = val[1][2]*val[2][0] - val[1][0]*val[2][2];
		rkInverse[1][1] = val[0][0]*val[2][2] - val[0][2]*val[2][0];
		rkInverse[1][2] = val[0][2]*val[1][0] - val[0][0]*val[1][2];
		rkInverse[2][0] = val[1][0]*val[2][1] - val[1][1]*val[2][0];
		rkInverse[2][1] = val[0][1]*val[2][0] - val[0][0]*val[2][1];
		rkInverse[2][2] = val[0][0]*val[1][1] - val[0][1]*val[1][0];

		f32 fDet = val[0][0] * rkInverse[0][0] +
			       val[0][1] * rkInverse[1][0] +
			       val[0][2] * rkInverse[2][0];

		if ( fabs(fDet) <= fTolerance )
		{
			return false;
		}

		f32 fInvDet = f32(1.0)/fDet;
		for (u32 iRow = 0; iRow < 3; iRow++)
		{
			for (u32 iCol = 0; iCol < 3; iCol++)
			{
				rkInverse[iRow][iCol] *= fInvDet;
			}
		}

		return true;
	}	

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 m3::GetColumn (u32 iCol) const
	{
		assert( 0 <= iCol && iCol < 3 );
		return v3(val[0][iCol],val[1][iCol],val[2][iCol]);
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void m3::SetColumn(u32 iCol, const v3& vec)
	{
		assert( 0 <= iCol && iCol < 3 );
		val[0][iCol] = vec.x;
		val[1][iCol] = vec.y;
		val[2][iCol] = vec.z;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	bit m3::operator== (const m3& rkMatrix) const
	{
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
			{
				if ( val[iRow][iCol] != rkMatrix.val[iRow][iCol] )
					return false;
			}
		}

		return true;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3 m3::operator+ (const m3& rkMatrix) const
	{
		m3 kSum;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
			{
				kSum.val[iRow][iCol] = val[iRow][iCol] + rkMatrix.val[iRow][iCol];
			}
		}
		return kSum;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3 m3::operator- (const m3& rkMatrix) const
	{
		m3 kDiff;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
			{
				kDiff.val[iRow][iCol] = val[iRow][iCol] -
					rkMatrix.val[iRow][iCol];
			}
		}
		return kDiff;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3 m3::operator* (const m3& rkMatrix) const
	{
		m3 kProd;
		for (u32 iRow = 0; iRow < 3; iRow++)
		{
			for (u32 iCol = 0; iCol < 3; iCol++)
			{
				kProd.val[iRow][iCol] = val[iRow][0]*rkMatrix.val[0][iCol] +
										val[iRow][1]*rkMatrix.val[1][iCol] +
										val[iRow][2]*rkMatrix.val[2][iCol];
			}
		}
		return kProd;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3 m3::operator- () const
	{
		m3 kNeg;
		for (u32 iRow = 0; iRow < 3; iRow++)
		{
			for (u32 iCol = 0; iCol < 3; iCol++)
			{
				kNeg[iRow][iCol] = -val[iRow][iCol];
			}
		}
		return kNeg;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	v3 m3::operator* (const v3& rkVector) const
	{
		v3 kProd;
		for (u32 iRow = 0; iRow < 3; iRow++)
		{
			kProd[iRow] = val[iRow][0] * rkVector[0] +
				          val[iRow][1] * rkVector[1] +
				          val[iRow][2] * rkVector[2];
		}
		return kProd;
	}

	v3_64 m3::operator*  (const v3_64& rkVector) const
	{
		v3_64 kProd;
		for (u32 iRow = 0; iRow < 3; iRow++)
		{
			kProd[iRow] = val[iRow][0] * rkVector[0] +
				val[iRow][1] * rkVector[1] +
				val[iRow][2] * rkVector[2];
		}
		return kProd;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3 m3::operator* (f32 fScalar) const
	{
		m3 kProd;
		for (u32 iRow = 0; iRow < 3; iRow++)
		{
			for (u32 iCol = 0; iCol < 3; iCol++)
			{
				kProd[iRow][iCol] = fScalar*val[iRow][iCol];
			}
		}
		return kProd;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	m3 m3::trans () const
	{
		m3 kTranspose;
		for (u32 iRow = 0; iRow < 3; iRow++)
		{
			for (u32 iCol = 0; iCol < 3; iCol++)
			{
				kTranspose[iRow][iCol] = val[iCol][iRow];
			}
		}
		return kTranspose;
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	f32 m3::det () const
	{
		f32 fCofactor00 = val[1][1]*val[2][2] - val[1][2]*val[2][1];
		f32 fCofactor10 = val[1][2]*val[2][0] - val[1][0]*val[2][2];
		f32 fCofactor20 = val[1][0]*val[2][1] - val[1][1]*val[2][0];

		f32 fDet = val[0][0] * fCofactor00 +
			       val[0][1] * fCofactor10 +
			       val[0][2] * fCofactor20;

		return fDet;
	}

};

