/*****************************************************************************
*
*   File: CBaseItem.cpp
*
*   Description: This file implements class CBaseItem.
*		 This class incapsulates item that has Id, Name, GUI Name and various data.
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
 *              BOOL operator ==(const CBaseItem& crItem) const \n
 *
 *   \par Purpose:
 * 				operator == \n
 *
 *   \par Inputs:
 * 				const CBaseItem& - const reference to CBaseItem instance \n
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
 *              BOOL operator !=(const CBaseItem& crItem) const \n
 *
 *   \par Purpose:
 * 				operator != \n
 *
 *   \par Inputs:
 * 				const CBaseItem& - const reference to CBaseItem instance \n
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
