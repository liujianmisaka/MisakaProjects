export module Misaka.Core.Utils.Singleton;

namespace Misaka::Core::Utils {

export template <typename T>
class Singleton {
public:
    // ��ȡ����ʵ���ľ�̬����
    static T& Instance() {
        // ʹ�þ�̬�ֲ�����ʵ������ʽ����
        static T instance;
        return instance;
    }

    virtual void Initialize() {}

    // ��ֹ��������͸�ֵ����
    Singleton(const Singleton&)            = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    // ���캯��������������Ϊ�����Է�ֹ�ⲿ����������ʵ��
    Singleton()  = default;
    ~Singleton() = default;
};

} // namespace Misaka::Core::Utils