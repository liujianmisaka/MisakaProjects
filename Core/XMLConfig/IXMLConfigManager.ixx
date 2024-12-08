module;

#include <tinyxml2.h>

export module Misaka.Core.XMLConfig.IXMLConfigManager;

import <string>;
import <vector>;
import <iostream>;
import Misaka.Core.CoreConfig;

namespace Misaka::Core::XMLConfig {

export class IXMLConfigManager {
public:
    virtual void Parse() = 0;

protected:
    virtual std::vector<tinyxml2::XMLElement*> ParseConfigFile(const std::string& fileName) {
        std::string filePath = (CoreConfig::Configs / fileName).string();

        std::vector<tinyxml2::XMLElement*> configItems;

        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(filePath.c_str()) != tinyxml2::XML_SUCCESS) {
            std::cerr << "Failed to load file: " << filePath << std::endl;
            return configItems;
        }

        const tinyxml2::XMLElement* root = doc.RootElement();
        if (root == nullptr) {
            std::cerr << "Failed to get root element." << std::endl;
            return configItems;
        }

        const tinyxml2::XMLElement* itemsElement = root->FirstChildElement("Items");
        if (itemsElement) {
            for (const tinyxml2::XMLElement* itemElement = itemsElement->FirstChildElement("Item"); itemElement != nullptr;
                 itemElement                             = itemElement->NextSiblingElement("Item")) {
                configItems.push_back(const_cast<tinyxml2::XMLElement*>(itemElement));
            }
        }

        return configItems;
    }
};

} // namespace Misaka::Core::XMLConfig