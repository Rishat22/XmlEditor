#include "Tools/Exceptions.h"
#include "Serialization/MainWidgetSetting.h"
#include "SettingsModel.h"
#include "SettingsLoader.h"

namespace Serialization
{

SettingsLoader::SettingsLoader(SettingsModel& model)
	: CXmlHandler()
	, m_BaseSettingType(BaseSettingType::UnknownSettings)
	, m_SourceModel(model)
	, m_ParentItem(nullptr)
{
}

std::list<std::shared_ptr<BaseSetting>> SettingsLoader::Load(const std::string& strFileName)
{
	m_Settings.clear();
	CXmlHandler::Load(strFileName);
	return m_Settings;
}

std::shared_ptr<BaseSetting> SettingsLoader::CreateSettings()
{
	switch (m_BaseSettingType)
	{
		case BaseSettingType::MainWidgetSettings:
		{
			return std::make_shared<MainWidgetSetting>();
		}
		case BaseSettingType::UnknownSettings:
		default:
		{
			throw Tools::UnknownSettingsException();
		}
	}
	return nullptr;
}

bool SettingsLoader::Save(const std::string& strFileName)
{
	/*CXmlNode* document = */NewDocument(strFileName);

//	CXmlNode* parentNode = NewNode("MainSettings", document);
//	BaseSetting base_setting;
//	CXmlNode* nameNode = NewNode(base_setting.GetTag("NameWidget"), parentNode);
//	auto strData = base_setting.GetData().toString();
//	nameNode->SetValue(strData);

	bool bRes = SaveDocument();

	return bRes;
}

bool SettingsLoader::XmlNodeBegin(void)
{
	std::string currTagName;
	if(GetCurrentTag(currTagName))
	{
		qDebug() << "Create New tag: " <<  currTagName.data();
	}
	return true;
}

bool SettingsLoader::XmlNodeDecode(const std::string& strNodeValue)
{
	bool bRes = true;
	try
	{
		std::string currTagName;
		if(GetCurrentTag(currTagName))
		{
			auto curAddedSetting = CreateSettings();
			m_Settings.push_back(curAddedSetting);
			curAddedSetting->SetData(currTagName, strNodeValue);
		}
	}
	catch (const Tools::LoadSettingsException& exception)
	{
		std::cout << "Error loading Settings." << std::endl;
		std::cout << "Value = " << strNodeValue.data() << std::endl;
		exception.what();
	}
	catch (const Tools::TypeException& exception)
	{
		exception.what();
		bRes = false;
	}

	return bRes;
}

bool SettingsLoader::GetCurrentTag(std::string& tagName)
{
	auto emptyIt = std::find(m_vStrOfNodes.begin(), m_vStrOfNodes.end(), std::string());
	emptyIt--; //Last not empty
	tagName = *emptyIt;
	return emptyIt >= m_vStrOfNodes.begin() && emptyIt != m_vStrOfNodes.end();
}


}
