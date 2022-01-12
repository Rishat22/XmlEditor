/*****************************************************************************
*
*   File: CXmlNode.cpp
*
*   Description: This file incapsulates class CXmlNode. This class incapsulates
*                structures and functions for accessing XML files
*
*
*****************************************************************************/

#include "CXmlNode.h"

namespace Serialization
{
	
/**
 *******************************************************************************
 *
 *   \par Name:		
 *              CXmlNode() \n
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
CXmlNode::CXmlNode()
	: m_pPreviousNode(nullptr)
	, m_pxml_document(nullptr)
	, m_pxml_node(nullptr)
{
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              CXmlNode(const CXmlNode& crXmlNode) \n
 *
 *   \par Purpose:
 * 				Copy constructor \n
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
CXmlNode::CXmlNode(const CXmlNode& /*crXmlNode*/)
	: m_pPreviousNode(nullptr)
	, m_pxml_document(nullptr)
	, m_pxml_node(nullptr)
{
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              CXmlNode(std::string strNodeName, CXmlNode* pPreviousNode = nullptr) \n
 *
 *   \par Purpose:
 * 				Constructor of Node \n
 *
 *   \par Inputs:     
 * 				std::string strNodeName - name of the node. \n
 * 				if(pPreviousNode == nullptr) strNodeName is the name of the file \n
 * 				
 * 				CXmlNode* pPreviousNode - pointer to a previous node \n
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
CXmlNode::CXmlNode(std::string strNodeName, CXmlNode* pPreviousNode)
	: m_pPreviousNode(nullptr)
	, m_pxml_document(nullptr)
	, m_pxml_node(nullptr)
	, m_strNodeName(strNodeName)
{
	if(pPreviousNode == nullptr)
	{
		m_pxml_document = new(pugi::xml_document);
	}
	else
	{
		m_pxml_node = new(pugi::xml_node);
		
		if(pPreviousNode->m_pxml_document != nullptr)
		{
			*m_pxml_node = pPreviousNode->m_pxml_document->append_child();
		}
		if(pPreviousNode->m_pxml_node != nullptr)
		{
			*m_pxml_node = pPreviousNode->m_pxml_node->append_child();
		}
		
		m_pxml_node->set_name(m_strNodeName.data());
	}
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              ~CXmlNode() \n
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
CXmlNode::~CXmlNode()
{
	if(m_pxml_document != nullptr)
	{
		delete m_pxml_document;
	}
	if(m_pxml_node != nullptr)
	{
		delete m_pxml_node;
	}
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SetNode(std::string strNodeName, CXmlNode* pPreviousNode = nullptr) \n
 *
 *   \par Purpose:
 * 				Sets the Node \n
 *
 *   \par Inputs:     
 * 				std::string strNodeName - name of the node. \n
 * 				if(pPreviousNode == nullptr) strNodeName is the name of the file \n
 * 
 * 				CXmlNode* pPreviousNode - pointer to previous node in xml structure \n
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
bool CXmlNode::SetNode(std::string strNodeName, CXmlNode* pPreviousNode)
{
	m_strNodeName = strNodeName;
	
	if(pPreviousNode == nullptr)
	{
		if(m_pxml_document != nullptr)
		{
			return false;
		}
		m_pxml_document = new(pugi::xml_document);
	}
	else
	{
		if(m_pxml_node != nullptr)
		{
			return false;
		}
		
		m_pxml_node = new(pugi::xml_node);
		
		if(pPreviousNode->m_pxml_document != nullptr)
		{
			*m_pxml_node = pPreviousNode->m_pxml_document->append_child();
		}
		if(pPreviousNode->m_pxml_node != nullptr)
		{
			*m_pxml_node = pPreviousNode->m_pxml_node->append_child();
		}
		
		m_pxml_node->set_name(m_strNodeName.data());
	}
	
	return true;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SaveDocument(std::string strEncoding = "",
 * 									pugi::xml_encoding encoding = pugi::encoding_auto, 
 * 									const pugi::char_t* indent = "    ", 
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
bool CXmlNode::SaveDocument(std::string strEncoding, pugi::xml_encoding encoding, const pugi::char_t* indent, unsigned int flags)
{
	if(m_pxml_document != nullptr)
	{
		if(!strEncoding.empty())
		{
			pugi::xml_node decl = m_pxml_document->prepend_child(pugi::node_declaration);
			decl.append_attribute("version").set_value("1.0");
			decl.append_attribute("encoding").set_value(strEncoding.data());
		}
		
        try
        {
			bool bRes;
            bRes = m_pxml_document->save_file(m_strNodeName.data(), indent, flags, encoding);
            return bRes;
        }
        catch(...)
        {

        }
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool AddAttribute(std::string strAttributeName, int s32Attribute) \n
 *
 *   \par Purpose:
 * 				Sets attribute of the node \n
 *
 *   \par Inputs:     
 * 				std::string strAttributeName - attribute name \n
 *
 * 				int s32Attribute - attribute value \n
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
bool CXmlNode::AddAttribute(std::string strAttributeName, int s32Attribute)
{
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_attribute(strAttributeName.data()) = static_cast<int>( s32Attribute );
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool AddAttribute(std::string strAttributeName, double f64Attribute) \n
 *
 *   \par Purpose:
 * 				Sets attribute of the node \n
 *
 *   \par Inputs:     
 * 				std::string strAttributeName - attribute name \n
 *
 * 				u_int32_t u32Attribute - attribute value \n
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
bool CXmlNode::AddAttribute(std::string strAttributeName, double f64Attribute)
{
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_attribute(strAttributeName.data()) = f64Attribute;
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool AddAttribute(std::string strAttributeName, std::string strAttribute) \n
 *
 *   \par Purpose:
 * 				Sets attribute of the node \n
 *
 *   \par Inputs:     
 * 				std::string strAttributeName - attribute name \n
 *
 * 				std::string strAttribute - attribute value \n
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
bool CXmlNode::AddAttribute(std::string strAttributeName, std::string strAttribute)
{
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_attribute(strAttributeName.data()) = strAttribute.data();
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool AddAttribute(std::string strAttributeName, bool bAttribute) \n
 *
 *   \par Purpose:
 * 				Sets attribute of the node \n
 *
 *   \par Inputs:     
 * 				std::string strAttributeName - attribute name \n
 *
 * 				bool bAttribute - attribute value \n
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
bool CXmlNode::AddAttribute(std::string strAttributeName, bool bAttribute)
{
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_attribute(strAttributeName.data()) = bAttribute;
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SetValue(std::string strValue) \n
 *
 *   \par Purpose:
 * 				Sets value of the node \n
 *
 *   \par Inputs:     
 * 				std::string strValue - value \n
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
bool CXmlNode::SetValue(std::string strValue)
{
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_child(pugi::node_pcdata).set_value(strValue.data());
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SetValue(const char *pChar) \n
 *
 *   \par Purpose:
 * 				Sets value of the node \n
 *
 *   \par Inputs:     
 * 				const char *pChar - pointer to char string with the value \n
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
bool CXmlNode::SetValue(const char *pChar)
{
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_child(pugi::node_pcdata).set_value(pChar);
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SetValue(u_char u8Value) \n
 *
 *   \par Purpose:
 * 				Sets value of the node \n
 *
 *   \par Inputs:     
 * 				u_char u8Value - value \n
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
bool CXmlNode::SetValue(u_char u8Value)
{
	char s[256];
	sprintf(s, "%u", u8Value);
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_child(pugi::node_pcdata).set_value(s);
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SetValue(char s8Value) \n
 *
 *   \par Purpose:
 * 				Sets value of the node \n
 *
 *   \par Inputs:     
 * 				char s8Value - value \n
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
bool CXmlNode::SetValue(char s8Value)
{
	char s[256];
	sprintf(s, "%d", s8Value);
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_child(pugi::node_pcdata).set_value(s);
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SetValue(u_int32_t u32Value) \n
 *
 *   \par Purpose:
 * 				Sets value of the node \n
 *
 *   \par Inputs:     
 * 				u_int32_t u32Value - value \n
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
bool CXmlNode::SetValue(u_int32_t u32Value)
{
	char s[256];
	sprintf(s, "%u", u32Value);
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_child(pugi::node_pcdata).set_value(s);
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SetValue(int s32Value) \n
 *
 *   \par Purpose:
 * 				Sets value of the node \n
 *
 *   \par Inputs:     
 * 				int s32Value - value \n
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
bool CXmlNode::SetValue(int s32Value)
{
	char s[256];
	sprintf(s, "%d", s32Value);
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_child(pugi::node_pcdata).set_value(s);
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SetValue(double f64Value) \n
 *
 *   \par Purpose:
 * 				Sets value of the node \n
 *
 *   \par Inputs:     
 * 				double f64Value - value \n
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
bool CXmlNode::SetValue(double f64Value)
{
	char s[256];
	sprintf(s, "%lf", f64Value);
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_child(pugi::node_pcdata).set_value(s);
		return true;
	}
	
	return false;
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              bool SetValue(ulong u64Value) \n
 *
 *   \par Purpose:
 * 				Sets value of the node \n
 *
 *   \par Inputs:
 * 				ulong u64Value - value \n
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
bool CXmlNode::SetValue(ulong u64Value)
{
	char s[256];
	sprintf(s, "%lu", u64Value);
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_child(pugi::node_pcdata).set_value(s);
		return true;
	}

	return false;
}


/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SetValue(bool bValue) \n
 *
 *   \par Purpose:
 * 				Sets value of the node \n
 *
 *   \par Inputs:     
 * 				bool bValue - value \n
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
bool CXmlNode::SetValue(bool bValue)
{
	if(bValue == true)
	{
		SetValue("true");
		return true;
	}
	if(bValue == false)
	{
		SetValue("false");
		return true;
	}
	
	return false;
}


/**
 *******************************************************************************
 *
 *   \par Name:		
 *              bool SetComment(std::string strComment) \n
 *
 *   \par Purpose:
 * 				Sets comments to the node \n
 *
 *   \par Inputs:     
 * 				std::string strComment - comment \n
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
bool CXmlNode::SetComment(std::string strComment)
{
	if(m_pxml_document != nullptr)
	{
		m_pxml_document->append_child(pugi::node_comment).set_value(strComment.data());
		return true;
	}
	if(m_pxml_node != nullptr)
	{
		m_pxml_node->append_child(pugi::node_comment).set_value(strComment.data());
		return true;
	}
	
	return false;
}

} /* End of namespace USerialization */
