#include <iostream>
#include <cassert>

class Singleton
{
public:
	static Singleton& Instance()
	{
		static Singleton& instance = *(new Singleton());
		return instance;	// potential leak
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

	delete (&Singleton::Instance());

	return 0;
}

// Tips:
// References(1): Never delete it. See https://google.github.io/styleguide/cppguide.html#Static_and_Global_Variables 其中的Common patterns段落。
// References(2): See http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Ri-singleton 
//  Details: In a multi-threaded environment, 
//  if the destruction of Singleton involves an operation that needs to be synchronized, we must use this less simple solution: 即正文中的代码实现。
//  Now someone must delete that object in some suitably thread-safe way.
//  对于C++核心指南的I.3条款，我认为可能对应的一种实际案例是：如果类Singleton的析构函数中援引了另一编译单元内的全局对象，因为不同编译单元内的全局对象的构造和析构顺序是不确定的，
//  所以对于Singleton的最佳实现方法(function-local static object)，在程序结束时，静态局部对象被自动销毁时，其析构函数中援引的另一全局对象可能已经被销毁，这样便会出错了。
//  所以，我们现在采用了这种动态内存分配Singleton唯一实例的 function-local static raw pointer 的方法，从而我们可以自己控制析构的时机，
//  确保在Singleton的析构函数援引的全局对象销毁之前进行销毁Singleton的唯一实例。
