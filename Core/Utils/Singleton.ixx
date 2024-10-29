export module Misaka.Core.Utils.Singleton;

namespace Misaka::Core::Utils {

export template <typename T>
class Singleton {
public:
    static T& Instance() {
        static T instance;
        return instance;
    }

    virtual void Initialize() {}

    Singleton(const Singleton&)            = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton()  = default;
    ~Singleton() = default;
};

} // namespace Misaka::Core::Utils