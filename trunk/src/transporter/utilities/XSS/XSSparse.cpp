#include "transporter.h"
//========================================================================================

CStructItem::CStructItem(void)
{
	parent = NULL;
	self = this;
}

CStructItem::~CStructItem(void)
{
	for(u32 i=0 ; i<items.size() ; i++)
	{
		delete items.at(i);
	}
	items.clear();
}

void CStructItem::set(char* item)
{
	if(strlen(item))
	{
		itemstr = std::string(item);
		std::vector<std::string> expstr = strexplodestr("=",itemstr);
		std::string lval = expstr.at(0);
		if(expstr.size()>1)
		{			
			value = expstr.at(1);
			int start = value.find_first_not_of(" \n\t\r");
			value = value.substr(start,value.length()-start);
			
			if(value[0] == '\"' && value.find('\"',1) != std::string::npos)
			{
				value = value.substr(1,value.find('\"',1)-1);
			}
			else
			{
				int sep = value.find(' ',start);
				if(sep != std::string::npos)
				{
					value = value.substr(0,sep);
				}
				value = chrreplacestr(value," \n\t\r","");
			}		
		}
		expstr = strexplodestr("[",lval);
		if(expstr.size() > 1)
		{
			std::vector<std::string> expstr2 = strexplodestr("]",expstr.at(1));
			ndx = expstr2.at(0);

			if(ndx[0] == '\"' && ndx.find('\"',1) != std::string::npos)
			{
				ndx = ndx.substr(1,ndx.find('\"',1)-1);
			}
			else
			{
				int start = ndx.find_first_not_of(" \n\t\r");
				int sep = ndx.find(' ',start);
				if(sep != std::string::npos)
				{
					ndx = ndx.substr(0,sep);
				}
				ndx = chrreplacestr(value," \n\t\r","");
			}
		}
		expstr = chrexplodestr(" \n\t",expstr.at(0));
		if(expstr.size()>1)
		{
			arg = chrreplacestr(expstr.at(expstr.size()-1)," \n\t\r","");
			std::string typestr = "";
			for(u32 i=0 ; i<expstr.size()-1 ; i++)
			{
				if(i>0)
				{
					typestr+=" ";
				}
				typestr += chrreplacestr(expstr.at(i)," \n\t\r","");
			}
			type = typestr;
		}
		else if(expstr.size())
		{
			arg = chrreplacestr(expstr.at(0)," \n\t\r","");
		}
	}
}

//========================================================================================

Csparse::Csparse(void)
{
	
}

Csparse::~Csparse(void)
{
	Clear();
}

void Csparse::Clear(void)
{
	for(u32 i=0 ; i<items.size() ; i++)
	{
		delete items.at(i);
	}
	items.clear();
}

char* Csparse::NoComments(char* src)
{
	char* result = NULL;
	if(src && strlen(src))
	{
		result = new char[strlen(src)+1];
		char* rptr = result;
		char* first = src;
		char* last  = first;
		char* last2 = first;
		while(first)
		{
			last  = strstr(first,"//");
			last2 = strstr(first,"/*");
			if(last && last < last2)last2 = NULL;
			else if(last2 && last2 < last)last = NULL;
			if(last)
			{
				memcpy(rptr,first,last-first);
				rptr+=last-first;
				first = strstr(last,"\n");
				if(!first)
				{
					first = NULL;
					rptr[1] = 0;
				}
			}
			else if(last2)
			{
				memcpy(rptr,first,last2-first);
				rptr+=last2-first;
				first = strstr(last2,"*/");
				if(first)
				{
					first += strlen("*/");
				}
				else
				{
					first = NULL;
					rptr[1] = NULL;
				}
			}
			else
			{
				memcpy(rptr,first,strlen(src)-(first-src));
				rptr+=strlen(src)-(first-src);
				rptr[0] = NULL;
				first = NULL;
			}
		}
	}
	return result;
}

char* Csparse::findblock(char* src,int& blocklen)
{
	char* start = strchr(src,'{');
	int skip = 1;
	int i=0;
	blocklen = 0;
	int len = strlen(src);
	if(start)
	{
		start += 1;
		int skip = 1;
		for(i ; i<=len ; i++)
		{
			if(start[i] == '{') skip++;
			else if(start[i] == '}')
			{
				skip--;
				if(!skip) 
				{
					//start[i] = 0;
					blocklen = i;
					break;
				}
			}
		}
		return start-1;
	}
	return NULL;
}

char* Csparse::fetchblock(char* src) 
{
	char* term = strchr(src,';');
	char* stbl = strchr(src,'{');
	if( ((term && stbl) && (stbl < term)) || (!term && stbl) )
	{
		int len = 0;
		term = findblock(src,len);
		return len ? term+len+1 : stbl+1;
	}
	else if(term)
	{
		return term;
	}	
	return NULL;
}

CStructItem* Csparse::createItem(char* src,CStructItem* parent)
{
	if(!src || strlen(src)==0)
	{
		return NULL;
	}
	CStructItem* newitem = NULL;

	char* term = strchr(src,';');
	char* stbl = strchr(src,'{');
	if( ((term && stbl) && (stbl < term)) || (!term && stbl) )
	{
		char temp = stbl[0];
		stbl[0] = 0;
		newitem = new CStructItem;
		newitem->parent = parent;
		newitem->set(src);
		stbl[0] = temp;

		int len = 0;
		term = findblock(src,len) + 1;
		if(len)
		{
			temp = term[len];
			term[len] = 0;
			parse(term,newitem);
			term[len] = temp;			
		}
	}
	else if(term)
	{
		char temp = term[0];
		term[0] = 0;
		if(strlen(src))
		{
			newitem = new CStructItem;
			newitem->parent = parent;
			newitem->set(src);
		}		
		term[0] = temp;
	}	
	return newitem;
}

void Csparse::parse(char* src,CStructItem* parent)
{
	char* block;
	while( (block = fetchblock(src)) != NULL )
	{
		block++;
		char temp = block[0];
		block[0] = 0;

		CStructItem* item = createItem(src,parent);
		if(item)
		{
			if(!parent)
			{
				items.push_back(item);
			}
			else parent->items.push_back(item);
		}

		block[0] = temp;
		src = block;
	}
}

void Csparse::LoadFromString(char* text)
{
	char* src = NoComments(text);
	for(u32 i=0 ; i<items.size() ; i++)
	{
		delete items.at(i);
	}
	items.clear();
	parse(src,NULL);
	delete[] src;	
}

bool Csparse::LoadFromFile(std::string filename)
{
	FILE* fp = fopen(filename.c_str(),"r");
	if(fp)
	{
		fseek(fp,0,SEEK_END);
		int size = ftell(fp);
		if( size )
		{
			fseek(fp,0,SEEK_SET);
			char* buffer = new char[size+1];
			buffer[size] = 0;
			int read = (int)fread(buffer,sizeof(char),size,fp);
			if( read )
			{
				LoadFromString(buffer);
			}
			delete[] buffer;
			return true;
		}
		fclose(fp);
	}
	return false;
}

int Csparse::SaveToFile(std::string filename)
{
	FILE* fp = fopen(filename.c_str(),"w+");
	if(fp)
	{
		std::string out = SaveToString();
		int write = fwrite(out.c_str(),out.length()+1,1,fp);
		fflush(fp);
		fclose(fp);
		return write;
	}
	return false;
}

void Csparse::WriteToStr(CStructItem* item,std::string* text,int indent)
{
	text->append(indent,' ');
	if( !item->type.empty() )
	{		
		*text += item->type;
		if(item->arg.empty() && item->ndx.empty() && item->value.empty() && !item->count())
		{
			*text+= ";\n";
		}
		else
		{
			*text+= " ";
		}
	}
	if( !item->arg.empty() )
	{
		*text += item->arg;
		if(item->ndx.empty() && item->value.empty() && !item->count())
		{
			*text+= ";\n";
		}
	}
	if( !item->ndx.empty() )
	{
		*text += "["+item->ndx+"]";
		if(item->value.empty() && !item->count() )
		{
			*text+= ";\n";
		}
	}
	if( !item->value.empty() )
	{
		*text += " = ";
		if( item->value.find(' ') != std::string::npos )
		{
			*text += "\""+item->value+"\"";
		}
		else
		{
			*text += item->value;
		}
		if( !item->count() )
		{
			*text += ";\n";
		}
	}
	if( item->count() )
	{
		*text += "\n";
		text->append(indent,' ');
		*text += "{\n";
	}
	for(int i=0 ; i<item->count() ; i++)
	{
		CStructItem* subitem = item->at(i);
		WriteToStr(subitem,text,indent+4);
	}
	if( item->count() )
	{
		//*text += "\n";
		text->append(indent,' ');
		*text += "}\n";
	}
}

std::string Csparse::SaveToString(void)
{
	std::string result;
	for(u32 i=0 ; i<items.size() ; i++)
	{
		CStructItem* item = items.at(i);
		WriteToStr(item,&result,0);
	}
	return result;
}

//========================================================================================

template <class T> T* Csinterface<T>::operator[](std::string arg)
{
	for(int i=0 ; i<items.size() ; i++)
	{
		CStructItem* item = items.at(i);
		if(item->arg == arg)
		{
			return item;
		}
	}
	return NULL;
}

template <class T> T* Csinterface<T>::at(int index)
{
	if(index>=0 && index<count())
	{
		return items.at(index);
	}
	return NULL;
}



//========================================================================================
/*
void main(int argc, char* argv[])
{
	if(argc<=1)return;
	Csparse sparse;
	sparse.LoadFromFile(argv[1]);
	std::string out = sparse.SaveToString();

	printf("%s",out.c_str());
	
	_getch();
}
*/