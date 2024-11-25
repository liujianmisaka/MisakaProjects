module;

#include <entt/entt.hpp>

export module Misaka.Core.Entity.MisakaEntity;

import <memory>;
import Misaka.Core.Entity.IEntity;
import Misaka.Core.Utils.Registry;

namespace Misaka::Core::Entity {

export class MisakaEntity : public IEntity {
public:
    MisakaEntity() = default;
    MisakaEntity(entt::entity entity, std::shared_ptr<Utils::Registry> registry) : m_Entity(entity), m_Registry(registry) {
    }
    MisakaEntity(const MisakaEntity& other) = default;
    virtual ~MisakaEntity()                 = default;

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        return m_Registry->emplace<T>(m_Entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T& GetComponent() {
        if (HasComponent<T>()) {
            return m_Registry->get<T>(m_Entity);
        } else {
            return AddComponent<T>();
        }
    }

    template <typename T>
    bool HasComponent() {
        return m_Registry->all_of<T>(m_Entity);
    }

    template <typename T>
    void RemoveComponent() {
        m_Registry->remove<T>(m_Entity);
    }

    operator bool() const {
        return m_Entity != entt::null;
    }
    operator entt::entity() const {
        return m_Entity;
    }
    bool operator==(const MisakaEntity& other) const {
        return m_Entity == other.m_Entity && m_Registry == other.m_Registry;
    }
    bool operator!=(const MisakaEntity& other) const {
        return !(*this == other);
    }

protected:
    entt::entity                     m_Entity   = entt::null;
    std::shared_ptr<Utils::Registry> m_Registry = nullptr;
};

} // namespace Misaka::Core::Entity