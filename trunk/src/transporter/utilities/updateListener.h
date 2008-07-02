#ifndef UPDATELISTENER_H
#define UPDATELISTENER_H
#include "transporter.h"

class UpdateListener
{
protected : 
public    : UpdateListener();
			~UpdateListener();

			virtual void update(u32 evId,u32 param);
};
#endif