/*****************************************************************************
*
*   File: CXmlHandler.h
*
*   Description: This file defines class CXmlHandler. This class incapsulates
*                structures and functions for accessing XML files
*
*
*****************************************************************************/
/**
 ******************************************************************************
 * \file CXmlHandler.h
 * File CXmlHandler.h is the header of class CXmlHandler.
 ******************************************************************************
 */
#ifndef _CXMLHANDLER_H_
#define _CXMLHANDLER_H_

#include <string>
#include <list>
#include <vector>
#include "CXmlNode.h"
#include "pugi/pugiconfig.hpp"
#include "pugi/pugixml.hpp"

namespace USerialization
{
	

/** \def Defines MAX_XMLDEPTH as 10 */
/** \brief Defines max depth of xml files as 10 */
#define	MAX_XMLDEPTH		10

/** \def Defines MAX_XMLATTRIBUTES as 10 */
/** \brief Defines max depth of xml node attributes as 10 */
#define	MAX_XMLATTRIBUTES		10


/**
 ******************************************************************************
 * Structure Attribute incapsulates attribute of xml node
 ******************************************************************************
 */
struct Attribute
{
	/** Default constructor */
	Attribute(void) {}
	 
	/** Attribute's name */
	std::string m_strName;
	
	/** Attribute's value */
	std::string m_strValue;
};

/**
 ******************************************************************************
 * Class CXmlNode incapsulates structures and functions for accessing XML files.
 ******************************************************************************
 */
class CXmlHandler : public pugi::xml_tree_walker
{
	//C_BASE_OBJECT(CXmlHandler)
public:
	CXmlHandler();
	virtual ~CXmlHandler();

	CXmlNode* NewDocument(std::string strFileName);
	CXmlNode* NewNode(std::string strNodeName, CXmlNode* pPreviousNode);
	bool SaveDocument(std::string strEncoding = "",
					  pugi::xml_encoding encoding = pugi::encoding_auto,
					  const pugi::char_t* indent = "\t",
					  unsigned int flags = pugi::format_default);

	bool Load(const std::string& strFileName);

	bool SetWriteMode(u_char u8WriteMode);

	virtual bool for_each(pugi::xml_node& xml_node);

	virtual bool XmlNodeBegin(void);

	/**
	 * Virtual function that decodes XML file. When this function is called
	 * m_vStrOfNodes - consists of Node's Names, strNodeValue - is value of specified node
	 */
	virtual bool XmlNodeDecode(const std::string& strNodeValue) = 0;


protected:
	/** Vector of Node's names */
	std::vector<std::string> m_vStrOfNodes;

	/** Vector of Attributes */
	std::vector<Attribute> m_vAttributes;

	/** List of nodes */
	std::list<CXmlNode> m_lstNodes;

	/** Name of the file to be written */
	std::string m_strFileName;
};

} /* End of namespace USerialization */

#endif /* _CXMLHANDLER_H_ */
