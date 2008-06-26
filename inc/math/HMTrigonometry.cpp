#include "math/HMath.h"

namespace hmath
{
	static u32 TrigTableSize;
	static f32 TrigTableFactor;
	static f32 *SinTable = NULL;
	static f32 *TanTable = NULL;
	static f32 *CosTable = NULL;

	void init_trig_table(u32 TableSize)
	{
		TrigTableSize = TableSize;
		TrigTableFactor = TrigTableSize / (f32)TWO_PI;

		SinTable = new f32[TrigTableSize];
		TanTable = new f32[TrigTableSize];
		CosTable = new f32[TrigTableSize];

		f32 angle;
		for (u32 i = 0; i < TrigTableSize; ++i)
		{
			angle = (f32)TWO_PI * i / TrigTableSize;
			SinTable[i] = sin(angle);
			TanTable[i] = tan(angle);
			CosTable[i] = cos(angle);
		}
	}

	void release_trig_table(void)
	{
		if(SinTable)
		{
			delete[] SinTable;
			SinTable = NULL;
		}
		if(TanTable)
		{
			delete[] TanTable;
			TanTable = NULL;
		}
		if(CosTable)
		{
			delete[] CosTable;
			CosTable = NULL;
		}
	}

	f32 tbl_sin (f32 r)
	{
		i32 idx;
		if (r >= 0)
		{
			idx = i32(r * TrigTableFactor) % TrigTableSize;
		}
		else
		{
			idx = TrigTableSize - (i32(-r * TrigTableFactor) % TrigTableSize) - 1;
		}

		return SinTable[idx];
	}

	f32 tbl_tan(f32 r)
	{
		int idx = int(r *= TrigTableFactor) % TrigTableSize;
		return TanTable[idx];
	}

	f32 tbl_cos(f32 r)
	{
		i32 idx;
		if (r >= 0)
		{
			idx = i32(r * TrigTableFactor) % TrigTableSize;
		}
		else
		{
			idx = TrigTableSize - (i32(-r * TrigTableFactor) % TrigTableSize) - 1;
		}

		return CosTable[idx];
	}

	f32 asm_acos( f32 r )
	{
		f32 asm_one = 1.f;
		f32 asm_half_pi = (f32)HALF_PI;
		__asm 
		{
			fld r // r0 = r
				fld r // r1 = r0, r0 = r
				fmul r // r0 = r0 * r
				fsubr asm_one // r0 = r0 - 1.f
				fsqrt // r0 = sqrtf( r0 )
				fchs // r0 = - r0
				fdiv // r0 = r1 / r0
				fld1 // {{ r0 = atan( r0 )
				fpatan // }}
				fadd asm_half_pi // r0 = r0 + pi / 2
		} // returns r0
	}

	f32 asm_asin( f32 r )
	{
		const f32 asm_one = 1.f;
		__asm 
		{
			fld r // r0 = r
				fld r // r1 = r0, r0 = r
				fmul r // r0 = r0 * r
				fsubr asm_one // r0 = r0 - 1.f
				fsqrt // r0 = sqrtf( r0 )
				fdiv // r0 = r1 / r0
				fld1 // {{ r0 = atan( r0 )
				fpatan // }}
		} // returns r0
	}

	f32 asm_atan( f32 r )
	{
		__asm 
		{
			fld r // r0 = r
				fld1 // {{ r0 = atan( r0 )
				fpatan // }}
		} // returns r0
	}

	f32 asm_sin( f32 r )
	{
		__asm 
		{
			fld r // r0 = r
				fsin // r0 = sinf( r0 )
		} // returns r0
	}

	f32 asm_cos( f32 r )
	{
		__asm 
		{
			fld r // r0 = r
				fcos // r0 = cosf( r0 )
		} // returns r0
	}

	f32 asm_tan( f32 r )
	{
		__asm 
		{
			fld r // r0 = r
				fsin // r0 = sinf( r0 )
				fld r // r1 = r0, r0 = r
				fcos // r0 = cosf( r0 )
				fdiv // r0 = r1 / r0
		} // returns r0
	}
};

