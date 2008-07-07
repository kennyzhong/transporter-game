#ifndef XSSNODE_H
#define XSSNODE_H
#include "transporter.h"
#include <vector>
#include <string>
#include <map>

class XSSNode
{
friend class XSSNode;
protected : str key;
			str type;
			str ndx;
			str value;
			XSSNode* parent;
			std::vector<XSSNode*> configs;
			std::map<str,XSSNode*> configMap;
			void addConfig(xss_item item, str parentStr);
			void addConfigNode(xss_item item, str nodeKey);
			XSSNode(str key,XSSNode* parent = NULL,str value="",str type="", str ndx="");			

public    : XSSNode();
			~XSSNode();
			str getNdx() const;
			str getType() const;
			str getKey() const;
			str getValue() const;
			i32 getValueAsInt() const;
			f32 getValueAsFloat() const;
			bit getValueAsBool() const;
			void setValue(str value);

			XSSNode* operator[] (str keyName) const;
			XSSNode* get(str keyName,bool upRecursive = false) const;
			u32 countChild() const;
			XSSNode* getChild(u32 index) const;
			XSSNode* getParent() const;

			bit loadConfig(str fileName);
			void clearConfig();
			
};
#endif