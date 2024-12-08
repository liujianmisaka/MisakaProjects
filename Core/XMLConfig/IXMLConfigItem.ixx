module;

#include <tinyxml2.h>

export module Misaka.Core.XMLConfig.IXMLConfigItem;

import <vector>;
import <string>;
import glm;

namespace Misaka::Core::XMLConfig {

export class IXMLConfigItem {
public:
    virtual void Parse(const tinyxml2::XMLElement* element) = 0;

protected:
    template <typename T>
    void ParseElement(const tinyxml2::XMLElement* element, T& value);

    template <typename T>
    void ParseArray(const tinyxml2::XMLElement* element, std::vector<T>& array);

    void ParseVector3(const tinyxml2::XMLElement* element, glm::vec3& vector3);
};

template <>
inline void IXMLConfigItem::ParseElement<int>(const tinyxml2::XMLElement* element, int& value) {
    element->QueryIntText(&value);
}

template <>
inline void IXMLConfigItem::ParseElement<float>(const tinyxml2::XMLElement* element, float& value) {
    element->QueryFloatText(&value);
}

template <>
inline void IXMLConfigItem::ParseElement<std::string>(const tinyxml2::XMLElement* element, std::string& value) {
    value = element->GetText();
}

template <typename T>
void IXMLConfigItem::ParseArray(const tinyxml2::XMLElement* element, std::vector<T>& array) {
    for (const tinyxml2::XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        T value;
        ParseElement(child, value);
        array.push_back(value);
    }
}

void IXMLConfigItem::ParseVector3(const tinyxml2::XMLElement* element, glm::vec3& vector3) {
    for (const tinyxml2::XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        if (child->Name() == "X") {
            ParseElement(child, vector3.x);
        } else if (child->Name() == "Y") {
            ParseElement(child, vector3.y);
        } else if (child->Name() == "Z") {
            ParseElement(child, vector3.z);
        }
    }
}

} // namespace Misaka::Core::XMLConfig