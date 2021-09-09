/*****************************************************************************
*
*   File: CBaseItem.h
*
*   Description: This file defines class CBaseItem.
*		 This class incapsulates item that has Id, Name, GUI Name and various data.
*
*
*****************************************************************************/
/**
 ******************************************************************************
 * \file CBaseItem.h
 * File CBaseItem.h is the header of class CBaseItem.
 ******************************************************************************
 */
#ifndef _CBASEITEM_H_
#define _CBASEITEM_H_

#include <Serialization/CXmlHandler.h>
#include <StableDeclaration.h>

namespace Serialization
{

class BaseSetting
{
public:
    BaseSetting() = default;
    virtual ~BaseSetting() = default;
    virtual bool operator ==(const BaseSetting& crItem) const;
    virtual bool operator != (const BaseSetting& crItem) const;
    virtual void Clear(void);
    virtual bool SetData(const std::string& strTag, const std::string& strData);
    const QVariant& GetData(void) const;
    QVariant GetData(void);
    std::string Tag() const;
protected:
    virtual QVariant GetDataByTag(const std::string& strTag, const std::string& strData) const = 0;
private:
    QVariant m_Data;
    std::string m_Tag;
};

}
#endif // _CBASEITEM_H_
