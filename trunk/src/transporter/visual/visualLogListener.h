#ifndef VISUALLOGLISTENER_H
#define VISUALLOGLISTENER_H
#include "transporter.h"

class VisualLogListener : public Ogre::LogListener
{
protected :
public    : void messageLogged( const str& message, Ogre::LogMessageLevel lml, bit maskDebug, const str& logName );
};
#endif