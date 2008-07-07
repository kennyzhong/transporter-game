#ifndef SPARSE_H
#define SPARSE_H
#include "transporter.h"

class CStructItem;
template <class T> class Csinterface
{
friend class Csinterface;
protected: std::vector<T*> items;
		   void remove(T* item)
		   {
			   for(unsigned int i=0 ; i<items.size() ; i++)
			   {
				   if(items.at(i) == item)
				   {
					   items.erase(items.begin()+i);
					   return;
				   }
			   }
		   }
		   T* parent;
		   T* self;
public : T* operator[](std::string arg);
		 T* operator[](int index){ return at(index); }
		 T* at(int index);
		 int count(void){ return (u32)items.size(); }
		 void del(void)
		 {
			 if(parent)
			 {
				 parent->remove(self);
			 }	
			 for(unsigned int i=0 ; i<items.size() ; i++)
			 {
				 delete items.at(i);
			 }
			 items.clear();
			 delete this;
		 }
		 T* add(void)
		 {
			 T* newitem = new T;
			 newitem->parent = self;
			 items.push_back(newitem);
			 return newitem;
		 }
		 int indexof(T* item)
		 {
			 for(unsigned int i=0 ; i<items.size() ; i++)
			 {
				 if(items.at(i) == item)
				 {
					 return i;
				 }
			 }
			 return -1;
		 }
		 T* get_parent(void){ return parent; }
		 Csinterface(void)
		 {
			 parent = NULL;
			 self = NULL;
		 }
};

class Csparse;
class CStructItem : public Csinterface<CStructItem>
{
friend class Csparse;
friend class Csinterface<CStructItem>;
private :
		  CStructItem(void);
		  ~CStructItem(void);
		  void set(char* item);
		  std::string itemstr;		  
public  :	
	std::string type;
	std::string arg;
	std::string ndx;
	std::string value;		
};

class Csparse : public Csinterface<CStructItem>
{
private : void parse(char* src,CStructItem* parent);
		  CStructItem* createItem(char* src,CStructItem* parent);
		  char* fetchblock(char* src);
		  char* findblock(char* src,int& blocklen);
		  char* NoComments(char* src);
		  void WriteToStr(CStructItem* item,std::string* text,int indent=0);

public  : Csparse(void);
		  ~Csparse(void);
		  void Clear(void);
		  bool LoadFromFile(std::string filename);
		  void LoadFromString(char* text);
		  int SaveToFile(std::string filename);
		  std::string SaveToString(void);
};
#endif
