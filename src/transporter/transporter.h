#ifndef TRANSPORTER_H
#define TRANSPORTER_H

#include "base/datatypes.h"
#include "base/object.h"
#include "base/ObjectFactory.h"
#include "utilities/Event.h"
#include "utilities/genfunction.h"
#include "math/HMath.h"

#include "transporter/visual/visualSystem.h"

class Game
{
protected : 
public    : Game() {};
			~Game() {};
			void run();
			VisualSystem visual;
};

#endif