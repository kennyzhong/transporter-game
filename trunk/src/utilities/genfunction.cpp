#include "utilities/genfunction.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

str chrreplacestr(str src,str chrs,str cp)
{
	str result;
	for(u32 i=0 ; i<src.length() ; i++)
	{
		char ch = src.at(i);
		if( chrs.find(ch) == str::npos )
		{
			result += ch;
		}
		else
		{
			result += cp;
		}
	}
	return result;
}

//————————————————————————————————————————————————————————————————————————————————————————

 std::vector<str> chrexplodestr(str delimiter,str input)
{
	i32 ndxS, ndxE=0;
	std::vector<str> result;

	while ( (ndxS = (i32)input.find_first_not_of( delimiter, ndxE )) != -1)
	{
		ndxE = (i32)input.find_first_of( delimiter, ndxS );
		if (ndxE == -1) 
		{
			ndxE = (i32)input.length();
		}
		result.push_back(input.substr(ndxS,ndxE-ndxS));
	}
	return result;
}

 //————————————————————————————————————————————————————————————————————————————————————————

 std::vector<str> strexplodestr(str delimiter,str input)
{
	i32 ndxS=0, ndxE;
	std::vector<str> result;

	do{
		if ( (ndxE = (i32)input.find( delimiter, ndxS )) == -1) 
		{
			ndxE = (i32)input.length();
		}
		result.push_back(input.substr(ndxS,ndxE-ndxS));

		ndxS = ndxE + (i32)delimiter.length();
	}
	while ( ndxS < (i32)input.length());    
	return result;
}

 //————————————————————————————————————————————————————————————————————————————————————————

 i32 HexCharToInt(i8 ch)
{
	if(ch>='0' && ch<='9')
	{
		return 9-('9'-ch);
	}
	else if(ch>='a' && ch<='f')
	{
		return 15-('f'-ch);
	}
	else if(ch>='A' && ch<='F')
	{
		return 15-('F'-ch);
	}
	else return 0;
}

 //————————————————————————————————————————————————————————————————————————————————————————

 str IntToStr(i32 Value)
 {
	 i8 result[32];
	 //_itoa_s(Value,result,sizeof(i8)*32,10); for VS8
	 itoa(Value,result,10);
	 return str(result);
 }

 //————————————————————————————————————————————————————————————————————————————————————————

 str UIntToStr(u32 Value)
 {
	 i8 result[32];
	 //_ultoa_s(Value,result,sizeof(i8)*32,10); for VS8
	 ultoa(Value,result,10);
	 return str(result);
 }

 //————————————————————————————————————————————————————————————————————————————————————————

 str UInt64ToStr(u64 Value)
 {
	 i8 result[128];
	 //_ui64toa_s(Value,result,sizeof(i8)*32,10); for VS8
	 _ui64toa(Value,result,10);
	 return str(result);
 }

 //————————————————————————————————————————————————————————————————————————————————————————

 str Int64ToStr(i64 Value)
 {
	 i8 result[128];
	 //_ui64toa_s(Value,result,sizeof(i8)*32,10); for VS8
	 _i64toa(Value,result,10);
	 return str(result);
 }

 //————————————————————————————————————————————————————————————————————————————————————————

 str UInt16ToStr(u16 Value)
 {
	 return UIntToStr(Value);
 }

 //————————————————————————————————————————————————————————————————————————————————————————

 str Int16ToStr(i16 Value)
 {
	 return IntToStr(Value);
 }

 //————————————————————————————————————————————————————————————————————————————————————————

 str UInt8ToStr(u8 Value)
 {
	 return UIntToStr(Value);
 }

 //————————————————————————————————————————————————————————————————————————————————————————

 str Int8ToStr(i8 Value)
 {
	 return IntToStr(Value);
 }

 //————————————————————————————————————————————————————————————————————————————————————————

 i32 StrToInt(str Value)
{
	if(!Value.empty())
	{
		return atoi(Value.c_str());
	}
	else
	{
		return 0;
	}
}

 //————————————————————————————————————————————————————————————————————————————————————————

 i64 StrToInt64( str Value )
 {
	 if(!Value.empty())
	 {
		 return _atoi64(Value.c_str());
	 }
	 else
	 {
		 return 0;
	 }
 }

 //————————————————————————————————————————————————————————————————————————————————————————

 f32 StrToFloat(str Value)
{
	if(!Value.empty())
	{	
		double result = atof(Value.c_str());
		return (f32)result;
	}
	return 0;
}

//————————————————————————————————————————————————————————————————————————————————————————

f64 StrToFloat64(str Value)
{
	if(!Value.empty())
	{	
		f64 result = atof(Value.c_str());
		return result;
	}
	return 0;
}

//————————————————————————————————————————————————————————————————————————————————————————

str FloatToStr(f32 Value)
{
	i8 result[64];
	//sprintf_s(result,sizeof(i8)*64,"%f",Value); for VS8
	sprintf(result,"%f",Value);
	return str(result);
}

//————————————————————————————————————————————————————————————————————————————————————————

str Float64ToStr(f64 Value)
{
	i8 result[64];
	//sprintf_s(result,sizeof(i8)*64,"%f",Value); for VS8
	sprintf(result,"%f",Value);
	return str(result);
}

//————————————————————————————————————————————————————————————————————————————————————————

void str_unrepeat(i8* text,i8 chr)
{
	for(unsigned int i=0,s=0 ; i<=strlen(text) ; i++,s++)
	{
		if(text[i] == chr)
		{
			text[s++] = text[i];
			while(text[++i] && text[i] == chr);
		}
		text[s] = text[i];
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

 void str_replace(i8* text,i8 target,i8 dest)
{
	while(*text)
	{
		if(*text == target)
		{
			*text = dest;
		}
		text++;
	}
}

//————————————————————————————————————————————————————————————————————————————————————————

 void str_ndx_extract(i8* text,i8* start,i8* end,u32& nstart,u32& nend)
{
	nend   = (unsigned int)strcspn(text,end);
	nstart = start?(unsigned int)(strlen(start) + strcspn(text,start)):0;
}

//————————————————————————————————————————————————————————————————————————————————————————

i8* str_extract(i8* text,i8* start,i8* end)
{
	unsigned int s,e;
	str_ndx_extract(text,start,end,s,e);
	i8* result = (i8*)malloc(e-s+1);
	memcpy(result,text+s,e-s);
	result[e-s] = 0;
	return result;
}

//————————————————————————————————————————————————————————————————————————————————————————

 void explodestr(std::vector<str>& result,str& delimiter,str& input)
{ 
	unsigned int ndxS=0, ndxE; 
	do{ 
		if ( (ndxE = input.find( delimiter, ndxS )) == -1){ 
			ndxE = input.length(); 
		} 
		result.push_back(input.substr(ndxS,ndxE-ndxS)); 
		ndxS = ndxE + delimiter.length(); 
	}while ( ndxS < input.length()); 
}

//.......................................................................................

void MemToStr(unsigned char* mem,u32 size,char* out,u32 outbufsize)
{
	if(size)
	{
		char bytechar[3];
		out[0] = 0;
		for(u32 i=0 ; i<size ; i++)
		{
			//_itoa_s(mem[i],bytechar,sizeof(char)*3,16); VS8
			itoa(mem[i],bytechar,16);
			bytechar[2] = 0;
			if(strlen(bytechar) < 2)
			{
			 bytechar[1] = bytechar[0];
			 bytechar[0] = '0';
			}
			//strcat_s(out,outbufsize,bytechar); // VS8
			strcat(out,bytechar);
		}
	}
}

//.......................................................................................
 
 u32 SizeOfType(u32 DType)
  {
 	 switch(DType)
 	 {
 	 case DT_void : return 0;
 	 case DT_bit  : return 1;
 	 case DT_u8   : return 1;
 	 case DT_u16  : return 2;
 	 case DT_u32  : return 4;
 	 case DT_u64  : return 8;
 	 case DT_i8   : return 1;
 	 case DT_i16  : return 2;
 	 case DT_i32  : return 4;
 	 case DT_i64  : return 8;
 	 case DT_f32  : return 4;
 	 case DT_f64  : return 8;
 	 case DT_f80  : return 10;
 	 case DT_str  : return u32(-1);
 	 case DT_rec  : return u32(-1);
 	 default : return 0; 
 	 }
  }
 
//.......................................................................................

   str TypeToStr(u32 DType)
   {
 	  switch(DType)
 	  {
 	  case DT_void : return "void";
 	  case DT_bit  : return "bit";
 	  case DT_u8   : return "8bit-unsigned-integer";
 	  case DT_u16  : return "16bit-unsigned-integer";
 	  case DT_u32  : return "32bit-unsigned-integer";
 	  case DT_u64  : return "64bit-unsigned-integer";
 	  case DT_i8   : return "8bit-signed-integer";
 	  case DT_i16  : return "16bit-signed-integer";
 	  case DT_i32  : return "32bit-signed-integer";
 	  case DT_i64  : return "64bit-signed-integer";
 	  case DT_f32  : return "32bit-floating-point";
 	  case DT_f64  : return "64bit-floating-point";
 	  case DT_f80  : return "80bit-floating-point";
 	  case DT_str  : return "string";
 	  case DT_rec  : return "record";
 	  default : return "unknown"; 
 	  }
   }

//.......................................................................................
   
   str VarDtTypeToHexStr(u32 DType,u8* value)
   {
 	  if(!value)
 	  {
 		  return "0x??";
 	  }
 	  if(DType == DT_rec)
 	  {
 		  return "record!";
 	  }
 	  else if(DType == DT_void)
 	  {
 		  return "void!";
 	  }
 	  else
 	  {
 		  u8 buf[33];
 		  ::MemToStr(value,SizeOfType(DType),(i8*)buf,33);
 		  return "0x"+str((char*)buf);
 	  }
   }

//.......................................................................................
  
   str VarDtTypeToStr(u32 DType,void* value)
   {
   	if(!value)
 	  {
 		  return "NULL";
 	  }
 	  if(DType == DT_rec)
 	  {
 		  return "record!";
 	  }
 	  else if(DType == DT_void)
 	  {
 		  return "void!";
 	  }
 	  else
 	  {
 		  switch(DType)
 		  {
 		  case DT_str :{ return str((char*)value); }
 		  case DT_f32 :{ f32* v = (f32*)value; return FloatToStr(*v); }
 		  case DT_f64 :{ f64* v = (f64*)value; return Float64ToStr(*v); }
 		  //case DT_f80 :{ f80* v = (f80*)value; return FloatToStr(*v); }
 		  case DT_u8  :{ return ::UInt8ToStr(*(u8*)value); }
 		  case DT_i8  :{ return ::Int8ToStr(*(i8*)value); }
 		  case DT_u16 :{ return ::UInt16ToStr(      ByteSwap16(*(u16*)value)); }
 		  case DT_i16 :{ return ::Int16ToStr ( (i16)ByteSwap16(*(u16*)value)); }
 		  case DT_u64 :{ return ::UInt64ToStr(      ByteSwap64(*(u64*)value)); }
 		  case DT_i64 :{ return ::Int64ToStr ( (i64)ByteSwap64(*(u64*)value)); }
 		  case DT_u32 :{ return ::UIntToStr  (      ByteSwap32(*(u32*)value)); }
 		  case DT_i32 :{ return ::IntToStr   ( (i32)ByteSwap32(*(u32*)value)); }
 		  case DT_bit :
 			  {
 				  if( (*(u8*)value)!=0 )
 				  {
 					  return "true";
 				  }
 				  else
 				  {
 					  return "false";
 				  }
 			  }
 		  }
 	  }
 	  return "unknown";
   }

//.......................................................................................

   u32 NumDtTypeToU32(u32 DType,u8* value)
   {
 	  if(!value)
 	  {
 		  return 0;
 	  }
 	  switch(DType)
 	  {
 	  case DT_str :{ return StrToInt(str((char*)value)); }
 	  case DT_f32 :{ f32* v = (f32*)value; return u32(*v); }
 	  case DT_f64 :{ f64* v = (f64*)value; return u32(*v); }
 	  //case DT_f80 :{ f80* v = (f80*)value; return u32(*v); }
 	  case DT_u8  :{ return u32(*(u8*)value); }
 	  case DT_i8  :{ return u32(*(i8*)value); }
 	  case DT_u16 :{ return u32(      ByteSwap16(*(u16*)value)); }
 	  case DT_i16 :{ return u32( (i16)ByteSwap16(*(u16*)value)); }
 	  case DT_u64 :{ return u32(      ByteSwap64(*(u64*)value)); }
 	  case DT_i64 :{ return u32( (i64)ByteSwap64(*(u64*)value)); }
 	  case DT_u32 :{ return u32(      ByteSwap32(*(u32*)value)); }
 	  case DT_i32 :{ return u32( (i32)ByteSwap32(*(u32*)value)); }
 	  case DT_rec : return u32(-1);
 	  case DT_bit :
 		  {
 			  if( (*(u8*)value)!=0 )
 			  {
 				  return 1;
 			  }
 			  else
 			  {
 				  return 0;
 			  }
 		  }
 	  default : return (u32)-1;
 	  }
   }

//.......................................................................................
  
   u32 StrTypeToDtType( str type )
   {
 	if(type == "void")return DT_void;
 	else if(type == "bit")return DT_bit;
 	else if(type == "u8")return DT_u8;
 	else if(type == "u16")return DT_u16;
 	else if(type == "u32")return DT_u32;
 	else if(type == "u64")return DT_u64;
 	else if(type == "i8")return DT_i8;
 	else if(type == "i16")return DT_i16;
 	else if(type == "i32")return DT_i32;
 	else if(type == "i64")return DT_i64;
 	else if(type == "f32")return DT_f32;
 	else if(type == "f64")return DT_f64;
 	//else if(type == "f80")return DT_f80;
 	else if(type == "str")return DT_str;
 	else if(type == "rec")return DT_rec;
 	return DT_void;
   }

//.......................................................................................

  str StrPrintf(const char *fmt, ...)
  {
	  va_list	ap;
	  va_start(ap, fmt);
	  i32 len   = vsnprintf(NULL,0,fmt,ap);//_vscprintf(fmt,ap);
	  i8* tmp = new i8[len + 1];
	  vsprintf(tmp, fmt, ap);	
	  str result = str(tmp);
	  delete[] tmp;
	  va_end(ap);	
	  return result;
  }

//.......................................................................................
  
  u16 ByteSwap16(u16 input)
  {
	  return (input>>8) | (input<<8);
  }

//.......................................................................................

  u32 ByteSwap32(u32 input)
  {
	  return (input<<24) | 
		    ((input<< 8) & 0x00FF0000) | 
			((input>> 8) & 0x0000FF00) | 
			 (input>>24);
  }

//.......................................................................................

  u64 ByteSwap64(u64 input)
  {
	  return (input<<56) | 
			((input<<40) & u64(0x00FF000000000000)) |
			((input<<24) & u64(0x0000FF0000000000)) |
			((input<< 8) & u64(0x000000FF00000000)) |
			((input>> 8) & u64(0x00000000FF000000)) |
			((input>>24) & u64(0x0000000000FF0000)) |
			((input>>40) & u64(0x000000000000FF00)) |
		     (input>>56);
  }

//.......................................................................................
  
  f32 ByteSwapf32(f32 input)
  {
	  u32 inp = *(u32*)&input;
	  inp = ByteSwap32(inp);
	  return *(f32*)&inp;
  }

//.......................................................................................
  
  f64 ByteSwapf64(f64 input)
  {
	  u64 inp = *(u64*)&input;
	  inp = ByteSwap64(inp);
	  return *(f64*)&inp;
  }

//.......................................................................................

  void ByteSwap2x8(u8* left,u8* right)
  {
	  u8 temp = *left;
	  *left = *right;
	  *right = temp;
  }

//.......................................................................................

  void ByteSwap(IN OUT u8* bytes,u32 size)
  {
	  if(size<1)return;
	  u8 temp;
	  for(u32 i=0 ; i<size/2 ; i++)
	  {
		  temp = bytes[i];
		  bytes[i] = bytes[size-i-1];
		  bytes[size-i-1] = temp;
	  }
  }

//.......................................................................................

  void StrToMem(u8* mem,u32 size,str value)
  {
	  if(mem && size)
	  {
		  if(value.substr(0,2) == "0x")
		  {
			  str v = value.substr(2,value.length()-2);
			  if(v.length() % 2 != 0 )
			  {
				  v.insert(0,"0");
			  }
			  u32 cpsize = v.length()/2;
			  if(size < cpsize)
			  {
				  cpsize = size;
			  }
			  ZeroMemory(mem,size);
			  for(u32 s=size - cpsize ; s<size ; s++)
			  {
				  i8 c0 = v.at(2*(s-(size - cpsize)));
				  i8 c1 = v.at(2*(s-(size - cpsize))+1);
				  mem[s] = HexCharToInt(c0)*16+HexCharToInt(c1);
			  }
		  }
		  else if(value.at(value.length()-1) == 'f')
		  {
			  f32 v = StrToFloat(value);
			  i32 cpsize = sizeof(f32);
			  i32 rem = size - cpsize;
			  if(rem < 0)
			  {
				  rem = 0;
				  cpsize = size;
			  }
			  ZeroMemory(mem,size);
			  memcpy(mem+rem,&v,cpsize);
		  }
		  else if(isalpha(value.at(0)))
		  {
			  i32 cpsize = value.length();
			  i32 rem = size - cpsize;
			  if(rem < 0)
			  {
				  rem = 0;
				  cpsize = size;
			  }
			  ZeroMemory(mem,size);
			  memcpy(mem+rem,value.c_str(),cpsize);
		  }
		  else
		  {
			  i32 v = atoi(value.c_str());
			  i32 cpsize = sizeof(i32);
			  i32 rem = size - cpsize;			  
			  if(rem < 0)
			  {
				  rem = 0;
				  cpsize = size;
			  }
			  ZeroMemory(mem,size);
			  memcpy(mem+rem,&v,cpsize);
		  }
	  }
  }

//.......................................................................................
  
  const str& strtrim(str& toTrim)
  {
	  if( toTrim.empty() )
	  {
		  return toTrim;
	  }

	  // TODO: All this code should be replaced with STL algorithms

	  for( str::iterator i = toTrim.begin(); i != toTrim.end(); )
	  {
		  if( isspace(*i) )
		  {
			  i = toTrim.erase(i);
		  }
		  else
		  {
			  break;
		  }
	  }

	  if(toTrim.empty())
		  return toTrim;

	  for (unsigned int i = (toTrim.size() - 1); i >= 0; --i)
	  {
		  if( isspace(toTrim[i]) )
		  {
			  //we can just erase from the end because
			  //it will shorted the part of the string already covered by the loop.
			  toTrim.erase(i);
		  }
		  else
		  {
			  break;
		  }
	  }
	  return toTrim;
  }

//.......................................................................................
  
  bit VarDtTypeStrToMem( u8* mem,u32 size,u32 dttype,str value )
  {
	  if(!mem || !size)
	  {
		  return false;
	  }

	  if(dttype == DT_bit)
	  {
		  str val = str(strlwr((char*)value.c_str()));
		  u8* ptr = (u8*)mem;
		  if(val == "false" || val == "0" || val=="null" || val=="nil" || val =="zero")
		  {			 
			  *ptr = 0;
		  }
		  else
		  {
			  *ptr = 1;
		  }
	  }
	  else if(dttype == DT_u8 || dttype == DT_i8)
	  {
		  u8* ptr = (u8*)mem;
		  i32 val = StrToInt(value);
		  *ptr = val;
	  }
	  else if((dttype == DT_u16 || dttype == DT_i16)  && size>=2)
	  {
		  u16* ptr = (u16*)mem;
		  i32 val = StrToInt(value);
		  *ptr = val;
	  }
	  else if((dttype == DT_u32 || dttype == DT_i32)  && size>=4)
	  {
		  u32* ptr = (u32*)mem;
		  *ptr = StrToInt(value);
	  }	
	  else if((dttype == DT_u32 || dttype == DT_i32)  && size>=4)
	  {
		  u64* ptr = (u64*)mem;
		  *ptr = StrToInt64(value);
	  }	
	  else if(dttype == DT_f32 && size>=4)
	  {
		  f32* ptr = (f32*)mem;
		  *ptr = StrToFloat(value);
	  }	
	  else if(dttype == DT_f64 && size>=8)
	  {
		  f64* ptr = (f64*)mem;
		  *ptr = StrToFloat64(value);
	  }	
	  else if(dttype == DT_str && size >=value.length()+1)
	  {
		  strcpy((char*)mem,value.c_str());
	  }
	  else return false;

	  return true;
  }

//.......................................................................................
  
  bit isFileExist( str filename )
  {
		FILE* fp = fopen(filename.c_str(),"r");
		if(fp)
		{
			fclose(fp);
			return true;
		}
		return false;
  }