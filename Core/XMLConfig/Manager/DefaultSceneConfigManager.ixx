export module Misaka.Core.XMLConfig.DefaultSceneConfigManager;

import <vector>;
import <memory>;
import <string>;
import <unordered_map>;
import Misaka.Core.XMLConfig.IXMLConfigManager;
import Misaka.Core.XMLConfig.DefaultSceneConfigItem;
import Misaka.Core.CoreConfig;

namespace Misaka::Core::XMLConfig {

export class DefaultSceneConfigManager : public IXMLConfigManager {
public:
    virtual void Parse() override {
        ParseConfigFile<DefaultSceneConfigItem>(m_FileName);
    }

    std::shared_ptr<DefaultSceneConfigItem> GetItem(int id) {
        auto it = m_ConfigItems.find(id);
        if (it != m_ConfigItems.end()) {
            return std::dynamic_pointer_cast<DefaultSceneConfigItem>(it->second);
        }
        return nullptr;
    }
};

} // namespace Misaka::Core::XMLConfig