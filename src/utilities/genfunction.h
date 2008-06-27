#ifndef GENERALFUNCTION
#define GENERALFUNCTION
#include "base/datatypes.h"

extern str chrreplacestr(str src,str chrs,str cp);
extern std::vector<str> chrexplodestr(str delimiter,str input);
extern std::vector<str> strexplodestr(str delimiter,str input);
extern void str_unrepeat(i8* text,i8 chr);
extern void str_replace(i8* text,i8 target,i8 dest);
extern void str_ndx_extract(i8* text,i8* start,i8* end,u32& nstart,u32& nend);
extern i8* str_extract(i8* text,i8* start,i8* end);
extern i32 HexCharToInt(i8 ch);
extern str IntToStr(i32 Value);
extern str UIntToStr(u32 Value);
extern str UInt64ToStr(u64 Value);
extern str Int64ToStr(i64 Value);
extern str UInt16ToStr(u16 Value);
extern str Int16ToStr(i16 Value);
extern str UInt8ToStr(u8 Value);
extern str Int8ToStr(i8 Value);
extern i32 StrToInt(str Value);
extern i64 StrToInt64(str Value);
extern f32 StrToFloat(str Value);
extern f64 StrToFloat64(str Value);
extern str FloatToStr(f32 Value);
extern str Float64ToStr(f64 Value);
extern void explodestr(std::vector<str>& result,str& delimiter,str& input);
extern void MemToStr(u8* mem,u32 size,i8* out,u32 outbufsize);
extern void StrToMem(u8* mem,u32 size,str value);
extern u32 SizeOfType(u32 DType);
extern str TypeToStr(u32 DType);
extern str VarDtTypeToHexStr(u32 DType,u8* value);
extern str VarDtTypeToStr(u32 DType,void* value);
extern u32 NumDtTypeToU32(u32 DType,u8* value);
extern u32 StrTypeToDtType(str type);
extern str StrPrintf(const char *fmt, ...);
extern u16 ByteSwap16(u16 input);
extern u32 ByteSwap32(u32 input);
extern u64 ByteSwap64(u64 input);
extern f32 ByteSwapf32(f32 input);
extern f64 ByteSwapf64(f64 input);
extern void ByteSwap2x8(u8* left,u8* right);
extern void ByteSwap(IN OUT u8* bytes,u32 size);
extern const str& strtrim(str& toTrim);
extern bit VarDtTypeStrToMem(u8* mem,u32 size,u32 dttype,str value);
extern bit isFileExist(str filename);
extern f32 clampValue(f32 value, f32 min, f32 max);
extern f32 circularValue(f32 value, f32 min, f32 max);

#endif