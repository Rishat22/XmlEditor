#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H
#include <memory>
#include <Serialization/CXmlHandler.h>
#include "StableDeclaration.h"
#include "SettingsModel.h"
#include "BaseSetting.h"

namespace Serialization
{

class SettingsLoader : public CXmlHandler
{

public:
    SettingsLoader();
    virtual ~SettingsLoader() = default;
public:
    void SetModel(const SettingsModel& model);
    bool Save(const std::string& strFileName);
    std::list<std::shared_ptr<BaseSetting> > Load(const std::string& strFileName);

    bool XmlNodeBegin(void) override;
    bool XmlNodeDecode(const std::string& strNodeValue) override;

private:
    bool GetCurrentTag(std::string& tagName);
private:
    std::list<std::shared_ptr<BaseSetting>> m_Settings;
};

}

#endif // SETTINGSLOADER_H
