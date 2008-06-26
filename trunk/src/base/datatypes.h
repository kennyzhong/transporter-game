#ifndef base_datatypes
#define base_datatypes

#include <string>
#include <vector>
#include <map>

typedef unsigned char      u8 ;
typedef unsigned short int u16;
typedef unsigned int       u32;
typedef unsigned __int64   u64;
typedef char               i8 ;
typedef short int          i16;
typedef int                i32;
typedef __int64            i64;
typedef float              f32;
typedef double             f64;
//typedef long double        f80;
typedef bool               bit;
typedef std::string        str;

#define DT_void 0x00
#define DT_bit  0x01
#define DT_u8   0x02
#define DT_u16  0x03
#define DT_u32  0x04
#define DT_u64  0x05
#define DT_i8   0x06
#define DT_i16  0x07
#define DT_i32  0x08
#define DT_i64  0x09
#define DT_f32  0x0A
#define DT_f64  0x0B
#define DT_f80  0x0C
#define DT_str  0x0D
#define DT_rec  0x0E

#ifndef NULL
#define NULL 0
#endif

#ifndef NULL
#define NULL 0
#endif

#define IN 
#define OUT

#endif