#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H
#include <memory>
#include <Serialization/CXmlHandler.h>
#include "StableDeclaration.h"
#include "BaseSetting.h"

namespace Serialization
{
enum class BaseSettingType
{
	UnknownSettings,
	MainWidgetSettings
};

class SettingsLoader : public CXmlHandler
{

public:
	SettingsLoader(SettingsModel& model);
    virtual ~SettingsLoader() = default;
public:
    bool Save(const std::string& strFileName);
    std::list<std::shared_ptr<BaseSetting> > Load(const std::string& strFileName);

	std::shared_ptr<BaseSetting> CreateSettings();
    bool XmlNodeBegin(void) override;
    bool XmlNodeDecode(const std::string& strNodeValue) override;

private:
    bool GetCurrentTag(std::string& tagName);
private:
    std::list<std::shared_ptr<BaseSetting>> m_Settings;
	BaseSettingType m_BaseSettingType;
	SettingsModel& m_SourceModel;
	QObject* m_ParentItem;
};

}

#endif // SETTINGSLOADER_H
