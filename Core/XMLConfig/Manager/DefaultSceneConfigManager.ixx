export module Misaka.Core.XMLConfig.DefaultSceneConfigManager;

import <vector>;
import <memory>;
import <unordered_map>;
import Misaka.Core.XMLConfig.IXMLConfigManager;
import Misaka.Core.XMLConfig.DefaultSceneConfigItem;

namespace Misaka::Core::XMLConfig {

export class DefaultSceneConfigManager : public IXMLConfigManager {
public:
    virtual void Parse() override {
        auto configItems = ParseConfigFile("DefaultSceneConfig.xml");
        for (auto item : configItems) {
            auto configItem = std::make_shared<DefaultSceneConfigItem>();
            configItem->Parse(item);
            m_ConfigItems[configItem->Id] = configItem;
        }
    }

    std::shared_ptr<DefaultSceneConfigItem> GetItem(int id) {
        return m_ConfigItems[id];
    }

private:
    std::unordered_map<int, std::shared_ptr<DefaultSceneConfigItem>> m_ConfigItems;
};

} // namespace Misaka::Core::XMLConfig