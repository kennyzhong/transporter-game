#ifndef RTLOG_H
#define RTLOG_H
#include "transporter.h"

class RTLog
{
private   : static void destroyRTLog();
protected : RTLog();
			~RTLog();

			std::vector<str> logs;
			CRITICAL_SECTION lock;
			static RTLog* getInstance();
public    : static void write(str logText);
			static str getLog(u32 index);
			static u32 count();
};
#endif