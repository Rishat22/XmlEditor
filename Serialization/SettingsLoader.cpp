#include "Tools/Exceptions.h"
#include "SettingsModel.h"
#include "SettingsLoader.h"

namespace Serialization
{

SettingsLoader::SettingsLoader(SettingsModel& model)
	: CXmlHandler()
	, m_SourceModel(model)
	, m_RootItem(nullptr)
	, m_ParentItem(nullptr)
	, m_CurrentItem(nullptr)
{
}

std::list<std::shared_ptr<BaseSetting>> SettingsLoader::Load(const std::string& strFileName)
{
	m_Settings.clear();
	if(LoadTagsInfo(strFileName))
	{
		CXmlHandler::Load(strFileName);
	}
	return m_Settings;
}

bool SettingsLoader::LoadTagsInfo(const std::string& strFileName)
{
	std::size_t LastSlashPos = strFileName.find_last_of("/");
	auto tagInfoFileName = strFileName.substr(LastSlashPos + 1);
	tagInfoFileName = tagInfoFileName.substr(0, tagInfoFileName.find_last_of("."));
	m_TagsInfoLoader.Load(tagInfoFileName);
	if(m_TagsInfoLoader.IsSettingsInfoFound())
	{
		return true;
	}
	else
	{
		std::cout << "Information about the current name of the setting was not found: " << tagInfoFileName << std::endl;
		return false;
	}
}

//std::shared_ptr<BaseSetting> SettingsLoader::CreateSettings()
//{

//}

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
		QObject* newItem = (m_ParentItem == nullptr) ? new QObject() : new QObject(m_ParentItem);
		newItem->setObjectName(currTagName.data());
		newItem->setProperty("TagName", currTagName.data());
		if(m_ParentItem == nullptr)
		{
			m_ParentItem = newItem;
			m_RootItem = newItem;
			m_SourceModel.addItem(m_ParentItem, QModelIndex());
		}
		m_CurrentItem = newItem;
//		else
//		{
//			m_ParentItem->objectName()
//		}
//		QObject* item2 = new QObject(item1);
//		item2->setProperty("TagName", "Son");
		//Adds entire item1 branch
		/* ---------------------------------------*/
	}
	return true;
}

bool SettingsLoader::XmlNodeDecode(const std::string& strNodeValue)
{
	bool bRes = true;

	try
	{
//		std::string currTagName;
//		if(GetCurrentTag(currTagName))
//		{
//			auto currentTagInfo = CreateSettings();
//			m_ParentItem->setProperty("Type", "String");
//			m_ParentItem->setProperty("Value", strNodeValue.data());
//			curAddedSetting->SetData(currTagName, strNodeValue);
//		}

		std::string currTagName;
		SettingTagInfo tagInfo;
		if(GetCurrentTag(currTagName) && m_TagsInfoLoader.FindTagInfo(currTagName, tagInfo))
		{
			m_SourceModel.updateItem(m_CurrentItem, tagInfo);
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
