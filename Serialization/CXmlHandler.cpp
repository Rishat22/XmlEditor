/*****************************************************************************
*
*   File: CXmlHandler.cpp
*
*   Description: This file implements class CXmlHandler. This class incapsulates
*                structures and functions for accessing XML files
*
*****************************************************************************/

#include "CXmlHandler.h"
#include "CXmlNode.h"

namespace USerialization
{
	
/**
 *******************************************************************************
 *
 *   \par Name:		
 *              CXmlHandler() \n
 *
 *   \par Purpose:
 * 				Default constructor \n
 *
 *   \par Inputs:     
 * 				None \n
 *
 *   \par Outputs:    
 * 				None \n
 *
 *   \par Returns:    
 * 				None \n
 *
 *   \par Notes:      
 * 				None \n
 *
 *******************************************************************************
 */
CXmlHandler::CXmlHandler()
	: m_vStrOfNodes(MAX_XMLDEPTH)
{
	m_vAttributes.reserve(MAX_XMLATTRIBUTES);
}



/**
 *******************************************************************************
 *
 *   \par Name:		
 *              ~CXmlHandler() \n
 *
 *   \par Purpose:
 * 				Destructor \n
 *
 *   \par Inputs:     
 * 				None \n
 *
 *   \par Outputs:    
 * 				None \n
 *
 *   \par Returns:    
 * 				None \n
 *
 *   \par Notes:      
 * 				None \n
 *
 *******************************************************************************
 */
CXmlHandler::~CXmlHandler()
{
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool NewDocument(std::string strFileName) \n
 *
 *   \par Purpose:
 * 				Makes new xml structure of the document \n
 *
 *   \par Inputs:     
 * 				std::string strFileName - name of file \n
 *
 *   \par Outputs:    
 * 				None \n
 *
 *   \par Returns:    
 * 				Pointer to the node \n
 *
 *   \par Notes:      
 * 				None \n
 *
 *******************************************************************************
 */
CXmlNode* CXmlHandler::NewDocument(std::string strFileName)
{
	m_lstNodes.clear();
	
	CXmlNode *pNode = NULL;
	m_lstNodes.push_back(CXmlNode());
	
	pNode = &( m_lstNodes.back() );

	m_strFileName = strFileName;

	if(pNode != NULL)
	{
		pNode->SetNode(m_strFileName);
	}

	return pNode;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool NewNode(std::string strNodeName, CXmlNode* pPreviousNode) \n
 *
 *   \par Purpose:
 * 				Makes new node in xml structure of the document \n
 *
 *   \par Inputs:     
 * 				std::string strNodeName - name of the node \n
 * 
 * 				CXmlNode* pPreviousNode - pointer to previous node in xml structure \n
 *
 *   \par Outputs:    
 * 				None \n
 *
 *   \par Returns:    
 * 				Pointer to the node \n
 *
 *   \par Notes:      
 * 				None \n
 *
 *******************************************************************************
 */
CXmlNode* CXmlHandler::NewNode(std::string strNodeName, CXmlNode* pPreviousNode)
{
	CXmlNode *pNode = NULL;
	m_lstNodes.push_back(CXmlNode());
	
	pNode = &( m_lstNodes.back() );
	
	if(pNode != NULL)
	{
		pNode->SetNode(strNodeName, pPreviousNode);
	}
	
	return pNode;
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              bool SaveDocument(std::string strEncoding = "",
 * 									pugi::xml_encoding encoding = pugi::encoding_auto,
 * 									const pugi::char_t* indent = "\t",
 * 									unsigned int flags = pugi::format_default) \n
 *
 *   \par Purpose:
 * 				Saves Document \n
 *
 *   \par Inputs:
 * 				std::string strEncoding - emcoding rules as String \n
 * 				xml_encoding encoding - encoding rules as pugi enum \n
 * 				const char_t* indent - ident \n
 * 				unsigned int flags - format flags \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				true if success, false if fails \n \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
bool CXmlHandler::SaveDocument(std::string strEncoding, pugi::xml_encoding encoding, const pugi::char_t* indent, unsigned int flags)
{
	if(m_lstNodes.empty())
	{
		return false;
	}

	bool bRes = m_lstNodes.front().SaveDocument(strEncoding, encoding, indent, flags);
	m_lstNodes.clear();

	return bRes;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              Load(std::string strFileName) \n
 *
 *   \par Purpose:
 * 				Reads data from a file \n
 *
 *   \par Inputs:     
 * 				std::string strFileName - name of file \n
 *
 *   \par Outputs:    
 * 				None \n
 *
 *   \par Returns:    
 * 				true if success, false if fails \n
 *
 *   \par Notes:      
 * 				None \n
 *
 *******************************************************************************
 */
bool CXmlHandler::Load(const std::string& strFileName)
{
	/* loading file */
	pugi::xml_document xml_document;
	pugi::xml_parse_result result;
	result = xml_document.load_file(strFileName.data());
	if(result.status != pugi::status_ok)
	{
		m_lstNodes.clear();
		return false; /* error */
	}

	if( xml_document.traverse(*this) == false)
	{
		m_lstNodes.clear();
		return false; /* error */
	}
	
	m_lstNodes.clear();
	return true;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool for_each(pugi::xml_node& xml_node) \n
 *
 *   \par Purpose:
 * 				Is called for each node traversed \n
 *
 *   \par Inputs:     
 * 				pugi::xml_node& xml_node - reference to xml node \n
 *
 *   \par Outputs:    
 * 				None \n
 *
 *   \par Returns:    
 * 				true if success, false if fails \n
 *
 *   \par Notes:      
 * 				None \n
 *
 *******************************************************************************
 */
bool CXmlHandler::for_each(pugi::xml_node& xml_node)
{
	if(xml_node.type() == pugi::node_element) /* Node name */
	{
		u_char u8Level = depth();
		if(u8Level < MAX_XMLDEPTH)
		{
			m_vStrOfNodes[u8Level] = xml_node.name(); /* Set Current node's name to its position */
			if((u8Level + 1) < MAX_XMLDEPTH) /* Clear next position */
			{
				m_vStrOfNodes[u8Level + 1] = "";
			}
			
			m_vAttributes.clear();
			pugi::xml_attribute_iterator iter = xml_node.attributes_begin();
			pugi::xml_attribute_iterator end = xml_node.attributes_end();
			for(; iter != end; ++iter)
			{
				if(m_vAttributes.size() < MAX_XMLATTRIBUTES)
				{
					Attribute attr;
					attr.m_strName  = iter->name();
					attr.m_strValue = iter->value();
					m_vAttributes.push_back(attr);
				}
				else
				{
					break;
				}	
			}
			
			if(XmlNodeBegin() == false)
			{
				return false; /* Error in XmlNodeBegin(...) function */
			}
		}
	}
	else /* Node value */
	{
		if(XmlNodeDecode(xml_node.value()) == false)
		{
			return false; /* Error in XmlNodeDecode(...) function */
		}
	}
	
	return true;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool XmlNodeBegin(void) \n
 *
 *   \par Purpose:
 * 				Virtual. Is called when traversal of node begins \n
 *
 *   \par Inputs:     
 * 				None \n
 *
 *   \par Outputs:    
 * 				None \n
 *
 *   \par Returns:    
 * 				true if success, false if fails \n
 *
 *   \par Notes:      
 * 				None \n
 *
 *******************************************************************************
 */
bool CXmlHandler::XmlNodeBegin(void)
{
	return true;
}

} /* End of namespace USerialization */
