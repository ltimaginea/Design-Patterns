#include <iostream>
#include <memory>
#include <cassert>

class Singleton
{
public:
	static std::shared_ptr<Singleton> Instance()
	{
		if (instance_ == nullptr)
		{
			// 之所以没有使用make_shared，是因为make_shared的函数体中无法访问Singleton类的私有构造函数，所以这里使用了new
			instance_ = std::shared_ptr<Singleton>(new Singleton());
		}
		return instance_;
	}
public:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;
public:
	~Singleton() = default;
private:
	Singleton() = default;
private:
	static std::shared_ptr<Singleton> instance_;
};

std::shared_ptr<Singleton> Singleton::instance_(nullptr);

int main()
{
	auto a = Singleton::Instance();
	auto b = Singleton::Instance();
	assert(a.get() == b.get());

	return 0;
}

// Tips:
//	1. 各客户共享唯一实例，所以应该使用 std::shared_ptr 而不是 std::unique_ptr
//	2. 以 std::shared_ptr 实现的 Singleton ，虽然解决了C++98普通指针风格Singleton的内存泄漏问题，但该示例还存在线程安全的问题，因此还需要进一步优化（加锁）
