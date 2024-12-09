export module Misaka.Core.GameModule.XMLConfigInitSystem;

import <unordered_map>;
import <memory>;
import <string>;
import Misaka.Core.GameModule.Interface.IInitSystem;
import Misaka.Core.XMLConfig.IXMLConfigManager;
import Misaka.Core.SingletonManager;
import Misaka.Core.XMLConfig.DefaultSceneConfigManager;

using namespace Misaka::Core::XMLConfig;

namespace Misaka::Core::GameModule {

template <typename T>
concept XMLConfigManagerType = std::is_base_of_v<IXMLConfigManager, T>;

export class XMLConfigInitSystem : public IInitSystem {
public:
    virtual void Initialize() override {
        AddConfigManager<DefaultSceneConfigManager>("DefaultScene.xml");
    }

private:
    template <XMLConfigManagerType T>
    void AddConfigManager(const std::string& name) {
        auto manager = SingletonManager::GetInstance<T>();
        manager->SetFileName(name);
        manager->Parse();
    }

    std::unordered_map<std::string, std::shared_ptr<IXMLConfigManager>> m_ConfigManagers;
};

} // namespace Misaka::Core::GameModule