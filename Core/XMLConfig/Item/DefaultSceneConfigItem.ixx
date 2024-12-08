module;

#include <tinyxml2.h>

export module Misaka.Core.XMLConfig.DefaultSceneConfigItem;

import <vector>;
import <string>;
import glm;
import Misaka.Core.XMLConfig.IXMLConfigItem;

namespace Misaka::Core::XMLConfig {

export class DefaultSceneConfigItem : public IXMLConfigItem {
public:
    virtual void Parse(const tinyxml2::XMLElement* element) override {
        ParseElement(element->FirstChildElement("Id"), Id);
        ParseArray(element->FirstChildElement("Meshs"), Meshs);
        ParseVector3(element->FirstChildElement("PositionOffset"), PositionOffset);
    }

    int                      Id;
    std::vector<std::string> Meshs;
    glm::vec3                PositionOffset;
};

} // namespace Misaka::Core::XMLConfig