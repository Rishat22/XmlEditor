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
	m_GetDataFunctions["ResizeType"] =
	[&](const std::string& strData) -> QVariant
	{
		return this->CreateResizeTypeList(strData);
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

QVariant MainWidgetSetting::CreateResizeTypeList(const std::string& strData)
{
	QStringList resizeTypes {"Fixed", "Expanded", "FixedHeight"};
	auto findIt = std::find(resizeTypes.begin(), resizeTypes.end(), strData.data());
	if(findIt == resizeTypes.end())
		throw Tools::IncorrectTagValueList(resizeTypes);
	std::iter_swap(resizeTypes.begin(), findIt); //Put current first
	return resizeTypes;
}


}
