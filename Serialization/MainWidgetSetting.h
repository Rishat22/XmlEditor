/*****************************************************************************
*
*   File: MainWidgetSetting.h
*
*   Description: This file implements class MainWidgetSetting.
*	This class inherited from the BaseSetting in order to get the settings for main widget.
*
*
*****************************************************************************/
/**
 ******************************************************************************
 * \file MainWidgetSetting.h
 * File MainWidgetSetting.h is the header of class MainWidgetSetting.
 ******************************************************************************
 */
#ifndef _MAINWIDGETSETTING_H_
#define _MAINWIDGETSETTING_H_

#include <StableDeclaration.h>
#include "BaseSetting.h"

namespace Serialization
{

class MainWidgetSetting : public BaseSetting
{
public:
    MainWidgetSetting() = default;
    virtual ~MainWidgetSetting() = default;
protected:
    virtual QVariant GetDataByTag(const std::string& strTag, const std::string& strData) const override;
};

}
#endif // _MAINWIDGETSETTING_H_
