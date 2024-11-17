export module Misaka.Core.Entity.MisakaEntity;

import <memory>;
import <entt/entt.hpp>;
import Misaka.Core.Entity.IEntity;

namespace Misaka::Core::Entity {

export class MisakaEntity : public IEntity {
public:
    MisakaEntity() = default;
    MisakaEntity(entt::entity entity, std::shared_ptr<entt::registry> registry) : m_Entity(entity), m_Registry(registry) {}
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

    operator bool() const { return m_Entity != entt::null; }
    operator entt::entity() const { return m_Entity; }

protected:
    entt::entity                    m_Entity   = entt::null;
    std::shared_ptr<entt::registry> m_Registry = nullptr;
};

} // namespace Misaka::Core::Entity