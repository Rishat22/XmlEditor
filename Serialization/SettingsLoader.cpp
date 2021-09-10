#include "SettingsLoader.h"

namespace Serialization
{

SettingsLoader::SettingsLoader()
	: CXmlHandler()
{
}

void SettingsLoader::SetModel(const SettingsModel& /*model*/)
{
}

std::list<std::shared_ptr<BaseSetting>> SettingsLoader::Load(const std::string& strFileName)
{
	m_Settings.clear();
	CXmlHandler::Load(strFileName);
	return m_Settings;
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

//void SettingsLoader::saveName(CXmlNode* parentNode, const CStripItemConfig& itemConfig)
//{
//	for(int paramIndex = BaseSetting::Name; paramIndex < BaseSetting::DataTypeLastElem; paramIndex++)
//	{
//		const auto stripItem = itemConfig.Item();
//		if(!stripItem.HasData(paramIndex))
//		{
//			continue;
//		}
//		CXmlNode* itemNameParamNode = NewNode(stripItem.GetTag(paramIndex), parentNode);
//		auto strData = stripItem.GetData(paramIndex);
//		itemNameParamNode->SetValue(strData);
//	}
//}

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

	std::string currTagName;
	if(GetCurrentTag(currTagName))
	{
		auto curAddedSetting = std::make_shared<BaseSetting>();
		m_Settings.push_back(curAddedSetting);
		curAddedSetting->SetData(currTagName, strNodeValue);
		qDebug() << "Set data to tag: " <<  currTagName.data();
	}

//	if(m_vStrOfNodes[topNodeIndex] == "MainSettings")
//	{
//		if(m_vStrOfNodes[topNodeIndex + 1] == "NameWidget")
//		{
//			bRes = plastAddedSetting->SetData(m_vStrOfNodes[topNodeIndex + 1], strNodeValue);
//			if(!bRes)
//			{
//				printf("Wrong NameWidget : %s \n", strNodeValue.data());
//			}
//		}
//	}
	if(bRes == false)
	{
		qDebug() << "Error loading Settings.";
		qDebug() << "Value = " << strNodeValue.data();
	}
	return bRes;
}

bool SettingsLoader::GetCurrentTag(std::string& tagName)
{
	auto emptyIt = std::find_if(m_vStrOfNodes.begin(), m_vStrOfNodes.end(), std::string());
	emptyIt--; //Last not empty
	tagName = *emptyIt;
	return emptyIt >= m_vStrOfNodes.begin() && emptyIt != m_vStrOfNodes.end();
}

}
