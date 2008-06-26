#ifndef HYPERMATH_CONSTANT
#define HYPERMATH_CONSTANT

#include <limits>
namespace hmath
{
	const f64 POS_INFINITY = std::numeric_limits<f64>::infinity();
	const f64 NEG_INFINITY = -std::numeric_limits<f64>::infinity();
	const f64 PI       = 3.14159265358979323e0;
	const f64 TWO_PI   = 2.0 * PI;
	const f64 HALF_PI  = 0.5 * PI;
	const f64 fDeg2Rad = PI / 180.0;
	const f64 fRad2Deg = 180.0 / PI;
	const f64 fEpsilon = 1e-04;
};

#endif
