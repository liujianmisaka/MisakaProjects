export module Misaka.Core.Component.TagComponent;

import <string>;

namespace Misaka::Core::Component {

export class TagComponent {
public:
    TagComponent() = default;
    TagComponent(const std::string& tag) : Tag(tag) {
    }
    std::string Tag;
};

} // namespace Misaka::Core::Component