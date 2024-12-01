export module Misaka.Core.SingletonManager;

import <any>;
import <memory>;
import <unordered_map>;
import <type_traits>;
import <mutex>;
import <typeindex>;
import <stdexcept>;

namespace Misaka::Core {

export class SingletonManager {
public:
    // 获取单例对象
    template <typename T>
    static std::shared_ptr<T> GetInstance() {
        const std::type_index key = typeid(std::type_identity_t<T>);

        {
            std::scoped_lock lock(m_GlobalMutex); // 确保线程安全
            auto             it = m_Instances.find(key);

            if (it != m_Instances.end()) {
                return std::any_cast<std::shared_ptr<T>>(it->second);
            }

            // 先插入一个占位符
            m_Instances[key] = std::shared_ptr<T>(nullptr);
        }

        // 创建实例
        auto instance = std::make_shared<T>();

        {
            std::scoped_lock lock(m_GlobalMutex); // 确保线程安全
            m_Instances[key] = instance;
        }

        return instance;
    }

    // 销毁单例对象
    template <typename T>
    static void DestroyInstance() {
        const std::type_index key = typeid(std::type_identity_t<T>);

        std::scoped_lock lock(m_GlobalMutex);
        auto             it = m_Instances.find(key);

        if (it != m_Instances.end()) {
            m_Instances.erase(it); // 删除
        }
    }

private:
    SingletonManager() = delete; // 禁止实例化

    // 全局保存所有类型的单例对象
    static inline std::unordered_map<std::type_index, std::any> m_Instances   = {};
    static inline std::mutex                                    m_GlobalMutex = {};
};

} // namespace Misaka::Core