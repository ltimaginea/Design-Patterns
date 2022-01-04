#include <iostream>
#include <memory>
#include <cassert>

class Singleton
{
public:
	static Singleton& Instance()
	{
		static std::unique_ptr<Singleton> instance_ptr(new Singleton());
		return *instance_ptr;
	}
public:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;
	~Singleton() = default;
private:
	Singleton() = default;
};

int main()
{
	auto& a = Singleton::Instance();
	auto& b = Singleton::Instance();
	assert(&a == &b);

	return 0;
}

// Tips:
// References(1): Never delete it. See https://google.github.io/styleguide/cppguide.html#Static_and_Global_Variables 其中的Common patterns段落。
// References(2): See http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Ri-singleton 
