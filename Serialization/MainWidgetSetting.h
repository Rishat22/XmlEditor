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

#include <map>
#include <StableDeclaration.h>
#include "BaseSetting.h"

namespace Serialization
{

class MainWidgetSetting : public BaseSetting
{
	using GetDataByTagFunc = std::function<QVariant(const std::string& strData)>;
public:
	MainWidgetSetting();
    virtual ~MainWidgetSetting() = default;
protected:
    virtual QVariant GetDataByTag(const std::string& strTag, const std::string& strData) const override;
private:
	QVariant CreateZoomTypeList(const std::string& strData);
private:
	std::map< std::string, GetDataByTagFunc > m_GetDataFunctions;
};

}
#endif // _MAINWIDGETSETTING_H_
