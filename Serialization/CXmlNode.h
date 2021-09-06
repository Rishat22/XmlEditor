/*****************************************************************************
*
*   File: CXmlNode.h
*
*   Description: This file defines class CXmlNode. This class incapsulates
*                structures and functions for accessing XML files
*
*
*****************************************************************************/
/**
 ******************************************************************************
 * \file CXmlNode.h
 * File CXmlNode.h is the header of class CXmlNode.
 ******************************************************************************
 */
#ifndef _CXMLNODE_H_
#define _CXMLNODE_H_

#include <string>
#include "pugi/pugixml.hpp"

namespace USerialization
{
	
/**
 ******************************************************************************
 * Class CXmlNode incapsulates structures and functions for accessing XML files.
 ******************************************************************************
 */
class CXmlNode 
{
public:
	CXmlNode();
	CXmlNode(const CXmlNode& crXmlNode);
	CXmlNode(std::string strFileName, CXmlNode* pPreviousNode = NULL);
	
	~CXmlNode();
	
	bool SetNode(std::string strNodeName, CXmlNode* pPreviousNode = NULL);
	
	bool AddAttribute(std::string strAttributeName, int s32Attribute);
	bool AddAttribute(std::string strAttributeName, double f64Attribute);
	bool AddAttribute(std::string strAttributeName, std::string strAttribute);
	bool AddAttribute(std::string strAttributeName, bool bAttribute);
	bool SetComment(std::string strComment);
	
	bool SetValue(std::string strValue);
	bool SetValue(const char *pChar);
	
	bool SetValue(u_char u8Value);
	bool SetValue(char s8Value);
	bool SetValue(u_int32_t u32Value);
	bool SetValueHex(u_int32_t u32Value);
	bool SetValue(int s32Value);
	bool SetValue(ulong u64Value);
	bool SetValue(double f64Value);
	bool SetValue(bool bValue);
	
	bool SaveDocument(std::string strEncoding = "",
						pugi::xml_encoding encoding = pugi::encoding_auto,
						const pugi::char_t* indent = "    ",
						unsigned int flags = pugi::format_default);
	
	/** Pointer to previous node */
	CXmlNode* m_pPreviousNode;
	
	/** Pointer to XML document */
	pugi::xml_document* m_pxml_document;
	
	/** Pointer to XML node */
	pugi::xml_node* m_pxml_node;
	
protected:
	/** Node's name */
	std::string m_strNodeName;

};

} /* End of namespace USerialization */

#endif /* _CXMLNODE_H_ */
