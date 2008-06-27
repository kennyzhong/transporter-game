#ifndef OBJECTVECTOR_H
#define OBJECTVECTOR_H
#include "base/datatypes.h"
#include "base/CBaseObject.h"

template<class T> class CObjectVector
{
friend class CObjectVector<T>;
protected : const std::vector<T>* _vector;
public    : CObjectVector(void):_vector(NULL){};
			CObjectVector(std::vector<T>* objects):_vector(_objects){};
			CObjectVector(const CObjectVector<T>& objects):_vector(objects._vector){};
		    CObjectVector& operator=(const CObjectVector<T>& Robjects)
			{
				_vector = Robjects._vector;
				return *this;
			}
		    CObjectVector& operator=(const std::vector<T>* Robjects)
			{
				_vector = Robjects;
				return *this;
			}
		    bit operator==(const CObjectVector<T>& Robjects) { return (Robjects._vector == _vector); }
		    bit operator==(std::vector<T>* Robjects) { return (Robjects == _vector); }
		    bit operator!=(const CObjectVector<T>& Robjects) { return !operator=(Robjects); }
		    bit operator!=(std::vector<T>* Robjects) { return !operator=(Robjects); }
		    T operator[](u32 index) { return get(index); }
		    T operator[](str name) { return get(name); }

		    u32 indexof(T obj)
			{
				if(!_vector)
				{
					return (u32)-1;
				}
				for(u32 i=0 ; i<_vector->size() ; i++)
				{
					if(_vector->at(i) == obj)
					{
						return i;
					}
				}
				return (u32)-1;
			}
		    u32 indexof(str name)
			{
				if(!_vector)
				{
					return (u32)-1;
				}
				for(u32 i=0 ; i<_vector->size() ; i++)
				{
					if( ((CBaseObject*)_vector->at(i))->get_name() == name)
					{
						return i;
					}
				}
				return (u32)-1;
			}
		    u32 count(void)
			{
				if(!_vector)
				{
					return 0;
				}
				return _vector->size();
			}
		    T get(u32 index)
			{
				if(!_vector)
				{
					return NULL;
				}
				if(index < count())
				{
					return _vector.at(index);
				}
				return NULL;
			}
		    T get(str name)
			{
				if(!_vector)
				{
					return NULL;
				}
				u32 index = indexof(name);
				if(index != -1)
				{
					return _vector->at(index);
				}
				return NULL;
			}
};
#endif