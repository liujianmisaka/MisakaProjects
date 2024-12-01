module;

#include <entt/entt.hpp>

export module Misaka.Core.Entity.MisakaEntity;

import <memory>;
import Misaka.Core.Entity.IEntity;
import Misaka.Core.SingletonManager;
import Misaka.Core.CoreConfig;

namespace Misaka::Core::Entity {

export class MisakaEntity : public IEntity {
public:
    MisakaEntity() {
        m_Entity   = entt::null;
        m_Registry = SingletonManager::GetInstance<entt::registry>();
    }

    MisakaEntity(entt::entity entity, std::shared_ptr<entt::registry> registry) : m_Entity(entity) {
        m_Registry = SingletonManager::GetInstance<entt::registry>();
    };

    MisakaEntity(MisakaEntity& other) = default;

    virtual ~MisakaEntity() = default;

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

    bool IsValid() const {
        return m_Registry->valid(m_Entity);
    }

    operator bool() const {
        return m_Entity != entt::null;
    }

    operator uint32_t() const {
        return static_cast<uint32_t>(m_Entity);
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
    entt::entity                    m_Entity   = entt::null;
    std::shared_ptr<entt::registry> m_Registry = nullptr;
};

} // namespace Misaka::Core::Entity