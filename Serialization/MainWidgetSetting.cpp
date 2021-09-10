/*****************************************************************************
*
*   File: MainWidgetSetting.cpp
*
*   Description: This file implements class MainWidgetSetting.
*	This class inherited from the BaseSetting in order to get the settings for main widget.
*
*
*****************************************************************************/
#include "MainWidgetSetting.h"

namespace Serialization
{

QVariant MainWidgetSetting::GetDataByTag(const std::string& strTag, const std::string& strData) const
{
	return QString(strData.data());
}


}
