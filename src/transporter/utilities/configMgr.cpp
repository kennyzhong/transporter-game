#include "transporter.h"

static ConfigMgr* volatile configMgr;

ConfigMgr::ConfigMgr()
{

}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

ConfigMgr::~ConfigMgr()
{
	std::map<str,XSSNode*>::iterator it = configMap.begin();
	for(it ; it!=configMap.end() ; it++)
	{
		XSSNode* node = it->second;
		delete node;
	}
	configMap.clear();
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void ConfigMgr::destroyConfigMgr()
{
	if(configMgr)
	{
		delete configMgr;
		configMgr = NULL;
	}
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

ConfigMgr* ConfigMgr::getInstance()
{
	static ConfigMgr* volatile selfPtr;
	if( selfPtr == NULL)
	{
		ConfigMgr* newConfigMgr = new ConfigMgr;
		LONG value = InterlockedCompareExchange((LONG*)&selfPtr,(LONG)newConfigMgr,NULL);
		if( value != NULL )
		{
			delete newConfigMgr;
		}
		else
		{
			configMgr = selfPtr;
			atexit(destroyConfigMgr);
		}
	}	
	return selfPtr;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

XSSNode* ConfigMgr::get( str configFile )
{
	ConfigMgr* This = ConfigMgr::getInstance();
	std::map<str,XSSNode*>::iterator it = This->configMap.find(configFile);
	if(it != This->configMap.end())
	{
		return it->second;
	}
	else
	{
		if(isFileExist(configFile))
		{
			XSSNode* configNode = new XSSNode;
			if(configNode->loadConfig(configFile))
			{
				This->configMap[configFile] = configNode;
				return configNode;
			}
		}
	}
	return NULL;
}

//覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧

void ConfigMgr::close( str configFile )
{
	ConfigMgr* This = ConfigMgr::getInstance();
	std::map<str,XSSNode*>::iterator it = This->configMap.find(configFile);
	if(it != This->configMap.end())
	{
		XSSNode* configNode = it->second;
		This->configMap.erase(it);
		delete configNode;
	}
}