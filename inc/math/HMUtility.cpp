#include "math/HMath.h"


namespace hmath
{
	inline f32 InvSqrt(f32 fValue)
	{
		return 1.0f/sqrt(fValue);
	}

	inline bit f32_equal( f32 a, f32 b, f32 tolerance )
	{
		return (fabs(b-a) <= tolerance);
	}

	inline f64 Deg2Rad(f64 degrees) 
	{ 
		return degrees * fDeg2Rad; 
	}

	inline f64 Rad2Deg(f64 radians) 
	{ 
		return radians * fRad2Deg; 
	}

	inline f32 UnitRandom ()
	{
		return f32(rand())/f32(RAND_MAX);
	}

	f64 safeASIN(f64 x)
	{
		return ((x) < -1.0 ? (-0.5*PI) : ((x) > 1.0) ? (0.5*PI) : (asin(x)));
	}

	f64 ClampUnity( f64 x )
	{
		if ( x >  1.0f ) return  1.0f;
		if ( x < -1.0f ) return -1.0f;
		return x ;
	}


	void EulersToMatrix(m4& dst, rad64 psi, rad64 theta, rad64 phi)
	{
		f32 cos_psi    = (f32)cos(psi.asRad());                                              
		f32 sin_psi    = (f32)sin(psi.asRad());                                              
		f32 cos_theta  = (f32)cos(theta.asRad());                                            
		f32 sin_theta  = (f32)sin(theta.asRad());                                            
		f32 cos_phi    = (f32)cos(phi.asRad());                                              
		f32 sin_phi    = (f32)sin(phi.asRad());                                              

		dst = m4::IDENTITY;
		dst.val[0][0] = cos_psi * cos_theta;                                         
		dst.val[0][1] = - sin_psi * cos_phi + cos_psi * sin_theta * sin_phi;         
		dst.val[0][2] = sin_psi * sin_phi + cos_psi * sin_theta * cos_phi;           
		dst.val[1][0] = sin_psi * cos_theta;                                        
		dst.val[1][1] = cos_psi * cos_phi + sin_psi * sin_theta * sin_phi;           
		dst.val[1][2] = - cos_psi * sin_phi + sin_psi * sin_theta * cos_phi;         
		dst.val[2][0] = - sin_theta;                                                 
		dst.val[2][1] = cos_theta * sin_phi;                                         
		dst.val[2][2] = cos_theta * cos_phi;                                         
	}

	//————————————————————————————————————————————————————————————————————————————————————————

	void MatrixToEulers(const m4& src, f64& psi, f64& theta, f64& phi)
	{
		v3 coord;
		m4 mat = src;

		f64 cos_theta;
		f64 sq_cos_theta = 1.0 - mat.val[2][0] * mat.val[2][0];
		f64 sin_psi;
		f64 sin_phi;

		cos_theta = ((sq_cos_theta) < 0.0 ? (0.0) : (sqrtf((f32)sq_cos_theta)));
		if (cos_theta == 0.0)
		{
			/* Singularity here */
			cos_theta = 0.000001;
		}

		sin_psi = mat.val[1][0] / cos_theta;
		psi = safeASIN(sin_psi);

		if (mat.val[0][0] < 0.0)
		{
			if (psi < 0.0)
			{
				psi = -PI - (psi);
			}
			else
			{
				psi = PI - (psi);
			}
		}
		theta = -safeASIN(mat.val[2][0]);

		sin_phi = mat.val[2][1] / cos_theta;
		phi = safeASIN(sin_phi);
		/* Correct for quadrant */
		if (mat.val[2][2] < 0.0)
		{
			if (phi < 0.0)
			{
				phi = -PI - (phi);
			}
			else
			{
				phi = PI - (phi);
			}
		}
	}

	void HprToMatrix( m4& rotation, const v3_64& hpr )
	{
		f64 ch, sh, cp, sp, cr, sr, srsp, crsp, srcp ;

		const f64 magic_epsilon = 0.00001;

		//if ( osg::equivalent(hpr[0],(v3::value_type)0.0,magic_epsilon) )
		if( fabs(hpr[0]) < magic_epsilon)
		{
			ch = 1.0 ;
			sh = 0.0 ;
		}
		else
		{
			sh = (f32)sin(hpr[0]);
			ch = (f32)cos(hpr[0]);
		}

		//if ( osg::equivalent(hpr[1],(v3::value_type)0.0,magic_epsilon) )
		if( fabs(hpr[1]) < magic_epsilon)
		{
			cp = 1.0 ;
			sp = 0.0 ;
		}
		else
		{
			sp = (f32)sin(hpr[1]);
			cp = (f32)cos(hpr[1]);
		}

		//if ( osg::equivalent(hpr[2],(v3::value_type)0.0,magic_epsilon) )
		if( fabs(hpr[2]) < magic_epsilon)
		{
			cr   = 1.0 ;
			sr   = 0.0 ; 
			srsp = 0.0 ;
			srcp = 0.0 ;
			crsp = sp ;
		}
		else
		{
			sr   = (f32)sin(hpr[2]);
			cr   = (f32)cos(hpr[2]);
			srsp = sr * sp ;
			crsp = cr * sp ;
			srcp = sr * cp ;
		}

		rotation.val[0][0] = f32(  ch * cr - sh * srsp ) ;
		rotation.val[1][0] = f32( -sh * cp ) ;
		rotation.val[2][0] = f32(  sr * ch + sh * crsp ) ;

		rotation.val[0][1] = f32( cr * sh + srsp * ch ) ;
		rotation.val[1][1] = f32( ch * cp ) ;
		rotation.val[2][1] = f32( sr * sh - crsp * ch ) ;

		rotation.val[0][2] = f32( -srcp ) ;
		rotation.val[1][2] = f32(  sp ) ;
		rotation.val[2][2] = f32(  cr * cp ) ;

		rotation.val[3][0] =  0.0;  // x trans
		rotation.val[3][1] =  0.0;  // y trans
		rotation.val[3][2] =  0.0;  // z trans

		rotation.val[0][3] =  0.0;
		rotation.val[1][3] =  0.0;
		rotation.val[2][3] =  0.0;
		rotation.val[3][3] =  1.0;
	}

	void MatrixToHpr( v3_64& hpr, const m4& rotation )
	{
		m4 mat;

		//v3 col1(rotation(0, 0), rotation(0, 1), rotation(0, 2));
		v3 col1((f32)rotation[0][0], (f32)rotation[0][1], (f32)rotation[0][2]);
		f64 s = col1.len();

		const f64 magic_epsilon = 0.00001;
		if ( s <= magic_epsilon )
		{
			//hpr.set(0.0f, 0.0f, 0.0f);
			hpr = v3_64::zero;
			return ;
		}


		f64 oneOverS = 1.0f / s;
		for( int i = 0; i < 3; i++ )
			for( int j = 0; j < 3; j++ )
				mat.val[i][j] = f32(rotation.val[i][j] * oneOverS);


		f64 sin_pitch = ClampUnity(mat.val[1][2]);
		f64 pitch = asin(sin_pitch);
		hpr[1] = f32(rad64(pitch).asDeg());

		f64 cp = cos(pitch);

		if ( cp > -magic_epsilon && cp < magic_epsilon )
		{
			f64 cr = ClampUnity(-mat.val[2][1]);
			f64 sr = ClampUnity(mat.val[0][1]);

			hpr[0] = 0.0f;
			hpr[2] = f32(rad64(atan2(sr,cr)).asDeg());
		}
		else
		{
			f64 one_over_cp = 1.0 / cp ;
			f64 sr = (f64)ClampUnity(-mat.val[0][2] * one_over_cp);
			f64 cr = (f64)ClampUnity( mat.val[2][2] * one_over_cp);
			f64 sh = (f64)ClampUnity(-mat.val[1][0] * one_over_cp);
			f64 ch = (f64)ClampUnity( mat.val[1][1] * one_over_cp);

			if ( (( fabs(sh)<magic_epsilon ) && (fabs(ch)<magic_epsilon) ) ||
				( ( fabs(sr)<magic_epsilon ) && (fabs(cr)<magic_epsilon) ) )
			{
				cr = ClampUnity(-mat.val[2][1]);
				sr = ClampUnity(mat.val[0][1]);;

				hpr[0] = 0.0f;
			}
			else
			{
				hpr[0] = f32(rad64(atan2(sh, ch)).asDeg());
			}

			hpr[2] = f32(rad64(atan2(sr, cr)).asDeg());
		}
	}
	bit IsFinite(const f64 value)
	{
//#if defined (WIN32) || defined (_WIN32) || defined (__WIN32__)
		return _finite(value) ? true : false;
//#else
//		return std::isfinite(value) ? true : false;
//#endif
	}

	void Clamp(f64& x, const f64 low, const f64 high)
	{
		if (x < low) x = low;
		if (x > high) x = high;
	}

	void Clamp(u32& x, const u32 low, const u32 high)
	{
		if (x < low) x = low;
		if (x > high) x = high;
	}

	void Clamp(i32& x, const i32 low, const i32 high)
	{
		if (x < low) x = low;
		if (x > high) x = high;
	}
	/*
	bit v3_directionEquals(v3& v,const v3& rhs,const rad& tolerance)
	{
	f32 dot = v.dot(rhs);
	rad angle = rad(acos(dot));

	return fabs(angle.asRad()) <= tolerance.asRad();
	}

	bit v3_positionEquals(v3& v,const v3& rhs, f32 tolerance)
	{
	return f32_equal(v.x, rhs.x, tolerance) &&
	f32_equal(v.y, rhs.y, tolerance) &&
	f32_equal(v.z, rhs.z, tolerance);
	}

	v3 v3_randomDeviant(v3& v,const rad& angle,const v3& up )
	{
	v3 newUp;

	if (up == v3::zero)
	{
	newUp = v.up();
	}
	else
	{
	newUp = up;
	}

	quat q;
	q.FromAngleAxis( rad(UnitRandom() * TWO_PI), v );
	newUp = q * newUp;

	q.FromAngleAxis( angle, newUp );
	return q * v;
	}

	quat v3_getRotationTo(v3& v,const v3& dest,const v3& fallbackAxis)
	{
	quat q;
	v3 v0 = v;
	v3 v1 = dest;
	v0.norm();
	v1.norm();

	v3 c = v0.cross(v1);

	f32 d = v0.dot(v1);

	if (d >= 1.0f)
	{
	return quat::id;
	}
	f32 s = sqrt( (1+d)*2 );
	if (s < 1e-6f)
	{
	if (fallbackAxis != v3::zero)
	{
	q.FromAngleAxis(rad(PI), fallbackAxis);
	}
	else
	{
	// Generate an axis
	v3 axis = v3::unitX.cross(v);
	if (axis.iszerolen())
	{
	axis = v3::unitY.cross(v);
	}
	axis.norm();
	q.FromAngleAxis(rad(PI), axis);
	}
	}
	else
	{
	f32 invs = 1 / s;

	q.x = c.x * invs;
	q.y = c.y * invs;
	q.z = c.z * invs;
	q.w = s * 0.5;
	}
	return q;
	}*/
}
