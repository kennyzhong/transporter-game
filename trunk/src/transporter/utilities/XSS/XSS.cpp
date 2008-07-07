#include "transporter.h"

//========================================================================================

xss xss_loadfrom_file(xss object,i8* filename)
{
	Csparse* cs;
	if(!object)
	{
		cs = new Csparse;
	}
	else
	{
		cs = (Csparse*)object;		
	}
	if(!cs->LoadFromFile(str(filename)))
	{
		delete cs;
		cs = NULL;
	}
	return (xss)cs;
}

//........................................................................................

xss xss_loadfrom_str(xss object,i8* text)
{
	Csparse* cs;
	if(!object)
	{
		cs = new Csparse;
	}
	else
	{
		cs = (Csparse*)object;		
	}
	cs->LoadFromString(text);
	return (xss)cs;
}

//........................................................................................

u32 xss_saveto_file(xss object,i8* filename)
{
	if(object)
	{
		Csparse* cs = (Csparse*)object;
		return cs->SaveToFile(str(filename));
	}
	return 0;
}

//........................................................................................

u32 xss_saveto_str(xss object,i8* str,u32 length)
{
	if(object)
	{
		Csparse* cs = (Csparse*)object;
		std::string data = cs->SaveToString();
		u32 cpLength = (data.length() < length) ? data.length()-1 : length-1;
		memcpy(str,data.c_str(),cpLength);
		str[cpLength] = 0;
		return cpLength;
	}
	return 0;
}

//........................................................................................

bit xss_clear(xss object)
{
	Csparse* cs = (Csparse*)object;
	if(cs)
	{
		cs->Clear();
		return true;
	}
	return false;
}

//........................................................................................

bit xss_destroy(xss object)
{
	Csparse* cs = (Csparse*)object;
	if(cs)
	{
		delete cs;
		return true;
	}
	return false;
}

//........................................................................................

xss_item xss_child(xss_item parent,u32 index)
{
	CStructItem* item = (CStructItem*)parent;
	if(item && (i32)index<item->count())
	{
		return (xss_item)item->at(index);
	}
	return NULL;
}

//........................................................................................

xss_item xss_parent(xss_item item)
{
	CStructItem* si = (CStructItem*)item;
	if(si)
	{
		return (xss_item)si->get_parent();
	}
	return NULL;
}

//........................................................................................

xss_item xss_add(xss_item item)
{
	CStructItem* si = (CStructItem*)item;
	if(si)
	{
		return (xss_item)si->add();
	}
	return NULL;
}

//........................................................................................

bit xss_del(xss_item item)
{
	CStructItem* si = (CStructItem*)item;
	if(si)
	{
		si->del();
		return true;
	}
	return false;
}

//........................................................................................

u32 xss_count(xss_item parent)
{
	CStructItem* item = (CStructItem*)parent;
	if(item)
	{
		return item->count();
	}
	return 0;
}

//........................................................................................

const i8* xss_type(xss_item item)
{
	CStructItem* si = (CStructItem*)item;
	if(si)
	{
		return si->type.c_str();
	}
	return NULL;
}

//........................................................................................

const i8* xss_arg(xss_item item)
{
	CStructItem* si = (CStructItem*)item;
	if(si)
	{
		return si->arg.c_str();
	}
	return NULL;
}

//........................................................................................

const i8* xss_ndx(xss_item item)
{
	CStructItem* si = (CStructItem*)item;
	if(si)
	{
		return si->ndx.c_str();
	}
	return NULL;
}

//........................................................................................

const i8* xss_value(xss_item item)
{
	CStructItem* si = (CStructItem*)item;
	if(si)
	{
		return si->value.c_str();
	}
	return NULL;
}

//........................................................................................

xss_item xss_find_child_type( xss_item parent,char* text )
{
	CStructItem* si = (CStructItem*)parent;
	if(si)
	{
		for(int i=0 ; i<si->count() ; i++)
		{
			CStructItem* ch = si->at(i);
			if(ch->type == str(text))
			{
				return (xss_item)ch;
			}
		}
	}
	return NULL;
}

//........................................................................................

xss_item xss_find_child_arg( xss_item parent,char* text )
{
	CStructItem* si = (CStructItem*)parent;
	if(si)
	{
		for(int i=0 ; i<si->count() ; i++)
		{
			CStructItem* ch = si->at(i);
			if(ch->arg == str(text))
			{
				return (xss_item)ch;
			}
		}
	}
	return NULL;
}

//........................................................................................

xss_item xss_find_child_ndx( xss_item parent,char* text )
{
	CStructItem* si = (CStructItem*)parent;
	if(si)
	{
		for(int i=0 ; i<si->count() ; i++)
		{
			CStructItem* ch = si->at(i);
			if(ch->ndx == str(text))
			{
				return (xss_item)ch;
			}
		}
	}
	return NULL;
}

//........................................................................................

xss_item xss_find_child_value( xss_item parent,char* text )
{
	CStructItem* si = (CStructItem*)parent;
	if(si)
	{
		for(int i=0 ; i<si->count() ; i++)
		{
			CStructItem* ch = si->at(i);
			if(ch->value == str(text))
			{
				return (xss_item)ch;
			}
		}
	}
	return NULL;
}

//........................................................................................

xss_item xss_find_next_type( xss_item node,char* text )
{
	CStructItem* si = (CStructItem*)node;
	if(si)
	{
		CStructItem* parent = si->get_parent();
		if(parent)
		{
			i32 ndx = parent->indexof(si);
			if(ndx > 0)
			{
				for(int i=ndx+1 ; i<parent->count() ; i++)
				{
					if(parent->at(i)->type == str(text))
					{
						return (xss_item)parent->at(i);
					}
				}
			}
		}
	}
	return NULL;
}

//........................................................................................

xss_item xss_find_next_arg( xss_item node,char* text )
{
	CStructItem* si = (CStructItem*)node;
	if(si)
	{
		CStructItem* parent = si->get_parent();
		if(parent)
		{
			i32 ndx = parent->indexof(si);
			if(ndx > 0)
			{
				for(int i=ndx+1 ; i<parent->count() ; i++)
				{
					if(parent->at(i)->arg == str(text))
					{
						return (xss_item)parent->at(i);
					}
				}
			}
		}
	}
	return NULL;
}

//........................................................................................

xss_item xss_find_next_ndx( xss_item node,char* text )
{
	CStructItem* si = (CStructItem*)node;
	if(si)
	{
		CStructItem* parent = si->get_parent();
		if(parent)
		{
			i32 ndx = parent->indexof(si);
			if(ndx > 0)
			{
				for(int i=ndx+1 ; i<parent->count() ; i++)
				{
					if(parent->at(i)->ndx == str(text))
					{
						return (xss_item)parent->at(i);
					}
				}
			}
		}
	}
	return NULL;
}

//........................................................................................

xss_item xss_find_next_value( xss_item node,char* text )
{
	CStructItem* si = (CStructItem*)node;
	if(si)
	{
		CStructItem* parent = si->get_parent();
		if(parent)
		{
			i32 ndx = parent->indexof(si);
			if(ndx > 0)
			{
				for(int i=ndx+1 ; i<parent->count() ; i++)
				{
					if(parent->at(i)->value == str(text))
					{
						return (xss_item)parent->at(i);
					}
				}
			}
		}
	}
	return NULL;
}
//========================================================================================

