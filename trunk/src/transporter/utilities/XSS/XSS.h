#ifndef XSS_H
#define XSS_H
#include "transporter.h"

#ifndef XSS_DATATYPE
#define XSS_DATATYPE
typedef int xss;
typedef int xss_item;
#endif

extern xss xss_loadfrom_file(xss object,i8* filename);
extern xss xss_loadfrom_str(xss object,i8* text);
extern u32 xss_saveto_file(xss object,i8* filename);
extern u32 xss_saveto_str(xss object,i8* str,u32 length);
extern bit xss_clear(xss object);
extern bit xss_destroy(xss object);
extern xss_item xss_child(xss_item parent,u32 index);
extern xss_item xss_parent(xss_item item);
extern xss_item xss_add(xss_item item);
extern bit xss_del(xss_item item);
extern u32 xss_count(xss_item parent);
extern const i8* xss_type(xss_item item);
extern const i8* xss_arg(xss_item item);
extern const i8* xss_ndx(xss_item item);
extern const i8* xss_value(xss_item item);
extern xss_item xss_find_child_type(xss_item parent,char* text);
extern xss_item xss_find_child_arg(xss_item parent,char* text);
extern xss_item xss_find_child_ndx(xss_item parent,char* text);
extern xss_item xss_find_child_value(xss_item parent,char* text);
extern xss_item xss_find_next_type(xss_item node,char* text);
extern xss_item xss_find_next_arg(xss_item node,char* text);
extern xss_item xss_find_next_ndx(xss_item node,char* text);
extern xss_item xss_find_next_value(xss_item node,char* text);

#endif
