#ifndef CONFIGMGR_H
#define CONFIGMGR_H
#include "transporter.h"

class ConfigMgr
{
private   : static void destroyConfigMgr();
protected : ConfigMgr();
			~ConfigMgr();
			static ConfigMgr* getInstance();
			std::map<str,XSSNode*> configMap;
public    : static XSSNode* get(str configFile);
			static void close(str configFile);
};
#endif