/*****************************************************************************
*
*   File: BaseSetting.h
*
*   Description: This file implements class BaseSetting.
*		 This class is an interface for storing settings data.
*		 For specific settings, you need to override GetDataByTag method
*
*
*****************************************************************************/
/**
 ******************************************************************************
 * \file BaseSetting.h
 * File BaseSetting.h is the header of class BaseSetting.
 ******************************************************************************
 */
#ifndef _BASESETTING_H_
#define _BASESETTING_H_

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
#endif // _BASESETTING_H_
