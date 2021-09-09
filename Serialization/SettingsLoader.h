#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H
#include <memory>
#include <Serialization/CXmlHandler.h>
#include "StableDeclaration.h"
#include "BaseSetting.h"

namespace Serialization
{

class SettingsLoader : public CXmlHandler
{

public:
    SettingsLoader() = default;
    virtual ~SettingsLoader() = default;
public:
    void setData(const std::list<BaseSetting>& settings);
    bool save(const std::string& strFileName);
    std::list<BaseSetting> load(const std::string& strFileName);

    bool XmlNodeBegin(void) override;
    bool XmlNodeDecode(const std::string& strNodeValue) override;

private:
    std::list<std::shared_ptr<BaseSetting>> m_Settings;
};

}

#endif // SETTINGSLOADER_H
