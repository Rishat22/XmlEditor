/*****************************************************************************
*
*   File: MainWidgetSetting.cpp
*
*   Description: This file implements class MainWidgetSetting.
*	This class inherited from the BaseSetting in order to get the settings for main widget.
*
*
*****************************************************************************/
#include <QColor>
#include <Tools/MathFunc.h>
#include <Tools/LoadSettingsExceptions.h>
#include "MainWidgetSetting.h"

namespace Serialization
{

MainWidgetSetting::MainWidgetSetting()
{
	m_GetDataFunctions["NameWidget"] =
	[](const std::string& strData) -> QVariant
	{
		return QString(strData.data());
	};
	m_GetDataFunctions["ZoomType"] =
	[&](const std::string& strData) -> QVariant
	{
		return this->CreateZoomTypeList(strData);
	};
	m_GetDataFunctions["MainColor"] =
			[](const std::string& strData) -> QVariant
	{
		return Tools::MathFunc::StringToColor(strData);
	};
}

QVariant MainWidgetSetting::GetDataByTag(const std::string& strTag, const std::string& strData) const
{
	const auto tagDataIt = m_GetDataFunctions.find(strTag);
	if(tagDataIt == m_GetDataFunctions.end())
		throw Tools::LoadSettingsException();
	return tagDataIt->second(strData);
}

QVariant MainWidgetSetting::CreateZoomTypeList(const std::string& strData)
{
	QStringList zoomTypes {"Fixed", "Expanded", "FixedHeight"};
	auto findIt = std::find(zoomTypes.begin(), zoomTypes.end(), strData.data());
	if(findIt == zoomTypes.end())
		throw Tools::IncorrectTagValueList(zoomTypes);
	std::iter_swap(zoomTypes.begin(), findIt); //Put current first
	return zoomTypes;
}


}
