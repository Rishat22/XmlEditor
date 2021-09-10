/*****************************************************************************
*
*   File: BaseSetting.cpp
*
*   Description: This file implements class BaseSetting.
*		 This class is an interface for storing settings data.
*		 For specific settings, you need to override GetDataByTag method
*
*
*****************************************************************************/
#include "BaseSetting.h"

namespace Serialization
{

/**
 *******************************************************************************
 *
 *   \par Name:
 *              BOOL operator ==(const BaseSetting& crItem) const \n
 *
 *   \par Purpose:
 * 				operator == \n
 *
 *   \par Inputs:
 * 				const BaseSetting& - const reference to BaseSetting instance \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				TRUE if items are equal, FALSE if not \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
bool BaseSetting::operator == (const BaseSetting& crItem) const
{
	return m_Data == crItem.m_Data;
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              BOOL operator !=(const BaseSetting& crItem) const \n
 *
 *   \par Purpose:
 * 				operator != \n
 *
 *   \par Inputs:
 * 				const BaseSetting& - const reference to BaseSetting instance \n
 *
 *   \par Outputs:
 * 				None \n
 *
 *   \par Returns:
 * 				FALSE if items are equal, TRUE if not \n
 *
 *   \par Notes:
 * 				None \n
 *
 *******************************************************************************
 */
bool BaseSetting::operator != (const BaseSetting& crItem) const
{
	return m_Data != crItem.m_Data;
}

/**
 *******************************************************************************
 *
 *   \par Name:
 *              void Clear(void) \n
 *
 *   \par Purpose:
 * 				Clears item's data \n
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
void BaseSetting::Clear(void)
{
	m_Data.clear();
}


/**
 *******************************************************************************
 *
 *	\par Name:
 *				BOOL SetData(const std::string& crstrTag, const std::string& crstrData) \n
 *
 *	\par Purpose:
 *				Set data in accordance with tag \n
 *
 *	\par Inputs:
 *				const std::string& strTag - const reference to tag string \n
 *				const std::string& strData - const reference to data string \n
 *
 *	\par Outputs:
 *				None \n
 *
 *	\par Returns:
 *				TRUE if data is set, FALSE if not \n
 *
 *	\par Notes:
 *				None \n
 *
 *******************************************************************************
 */
bool BaseSetting::SetData(const std::string& strTag, const std::string& strData)
{
	m_Tag = strTag;
	auto data = GetDataByTag(m_Tag, strData);
	return data.isValid();
}

const QVariant& BaseSetting::GetData() const
{
	return m_Data;
}

QVariant BaseSetting::GetData()
{
	return m_Data;
}

std::string BaseSetting::Tag() const
{
	return m_Tag;
}

}
