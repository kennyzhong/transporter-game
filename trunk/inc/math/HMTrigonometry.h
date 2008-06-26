#ifndef HYPERMATH_TRIGONOMETRY
#define HYPERMATH_TRIGONOMETRY
#include "math/HMath.h"

namespace hmath
{
	inline f32 asm_acos( f32 r );
	inline f32 asm_asin( f32 r );
	inline f32 asm_atan( f32 r );
	inline f32 asm_sin( f32 r );
	inline f32 asm_cos( f32 r );
	inline f32 asm_tan( f32 r );
	inline f32 tbl_sin (f32 r);
	inline f32 tbl_tan(f32 r);
	inline f32 tbl_cos(f32 r);

	void init_trig_table(u32 TableSize);
	void release_trig_table(void);
};

#endif
