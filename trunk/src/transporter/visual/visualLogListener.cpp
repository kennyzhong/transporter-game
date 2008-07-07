#include "transporter.h"

void VisualLogListener::messageLogged( const String& message, LogMessageLevel lml, bool maskDebug, const String &logName )
{
	RTLog::write(message);
}