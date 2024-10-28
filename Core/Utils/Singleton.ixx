export module Misaka.Core.Utils.Singleton;

namespace Misaka::Core::Utils {

export template <typename T>
class Singleton {
public:
    // 获取单例实例的静态方法
    static T& Instance() {
        // 使用静态局部变量实现懒汉式单例
        static T instance;
        return instance;
    }

    virtual void Initialize() {}

    // 禁止拷贝构造和赋值操作
    Singleton(const Singleton&)            = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    // 构造函数和析构函数设为保护以防止外部创建和销毁实例
    Singleton()  = default;
    ~Singleton() = default;
};

} // namespace Misaka::Core::Utils