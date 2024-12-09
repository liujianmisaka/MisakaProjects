module;

#include <tinyxml2.h>

export module Misaka.Core.XMLConfig.IXMLConfigManager;

import <string>;
import <vector>;
import <iostream>;
import <unordered_map>;
import Misaka.Core.CoreConfig;
import Misaka.Core.XMLConfig.IXMLConfigItem;

namespace Misaka::Core::XMLConfig {

export class IXMLConfigManager {
public:
    virtual void Parse() = 0;

    virtual void SetFileName(const std::string& name) {
        m_FileName = name;
    }

protected:
    template <typename Item>
    void ParseConfigFile(const std::string& fileName) {
        std::string filePath = (CoreConfig::Configs / fileName).string();

        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(filePath.c_str()) != tinyxml2::XML_SUCCESS) {
            std::cerr << "Failed to load file: " << filePath << std::endl;
            return;
        }

        const tinyxml2::XMLElement* root = doc.RootElement();
        if (root == nullptr) {
            std::cerr << "Failed to get root element." << std::endl;
            return;
        }

        const tinyxml2::XMLElement* itemsElement = root->FirstChildElement("Items");
        if (itemsElement == nullptr) {
            std::cerr << "Failed to find 'Items' element." << std::endl;
            return;
        }

        std::vector<const tinyxml2::XMLElement*> itemElements;

        for (const tinyxml2::XMLElement* itemElement = itemsElement->FirstChildElement("Item"); itemElement != nullptr;
             itemElement                             = itemElement->NextSiblingElement("Item")) {
            itemElements.push_back(itemElement);
        }

        if (itemElements.empty()) {
            std::cerr << "No 'Item' elements found in 'Items' element." << std::endl;
        }

        for (auto item : itemElements) {
            auto configItem = std::make_shared<Item>();
            configItem->Parse(item);
            m_ConfigItems[configItem->Id] = configItem;
        }

        return;
    }

    std::string m_FileName;

    std::unordered_map<int, std::shared_ptr<IXMLConfigItem>> m_ConfigItems;
};

} // namespace Misaka::Core::XMLConfig