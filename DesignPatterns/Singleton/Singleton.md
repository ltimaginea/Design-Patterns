# Singleton

保证一个类仅有一个实例，并提供一个访问它的全局访问点。

## 实现要点

- 构造函数应该声明为非公有，从而禁止外界创建实例。

- 拷贝操作和移动操作也应该禁止。

- 只能通过 Singleton 的公有特定类操作访问它的唯一实例（C++中的一个公有静态成员函数）。

- C++11起，Singleton 最佳实现是静态局部对象的方法，该方法是线程安全的。C++11标准保证：如果多个线程试图同时初始化同一静态局部对象，则初始化严格只发生一次。见《C++ Concurrency in Action》Second Edition，Chapter 3.3.1，或者见 [Storage class specifiers - cppreference.com](https://en.cppreference.com/w/cpp/language/storage_duration#Static_local_variables) :

  > If multiple threads attempt to initialize the same static local variable concurrently, the initialization occurs exactly once.

  之所以把类 Singleton 的唯一实例定义为 function-local static object 而非 static data member ，因为 static data member 本质上是 global object ， global object 存在 initialization order 和异常安全方面的问题，见 [StaticLocalVariable_GlobalVariable.md](https://github.com/ltimaginea/Cpp-Primer/blob/main/CppPrimer/Content/Ch02_VariablesAndBasicTypes/Ch02_02_StaticLocalVariable_GlobalVariable.md) 。



## Best Practices

```cpp
#include <iostream>
#include <cassert>

class Singleton
{
public:
	static Singleton& Instance()
	{
		static Singleton instance;
		return instance;
	}
public:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;
private:
	Singleton() = default;
	~Singleton() = default;
};

int main()
{
	auto& a = Singleton::Instance();
	auto& b = Singleton::Instance();
	assert(&a == &b);

	return 0;
}
```



## References

* [Design-Patterns-in-Cpp17/Singleton.cpp at master · downdemo/Design-Patterns-in-Cpp17 · GitHub](https://github.com/downdemo/Design-Patterns-in-Cpp17/blob/master/src/Singleton.cpp)
* [DesignPatterns/Singleton at master · pezy/DesignPatterns · GitHub](https://github.com/pezy/DesignPatterns/blob/master/Singleton/main.cpp)
* [Storage class specifiers - cppreference.com](https://en.cppreference.com/w/cpp/language/storage_duration#Static_local_variables)
* [C++ 单例模式总结与剖析 - 行者孙 - 博客园 (cnblogs.com)](https://www.cnblogs.com/sunchaothu/p/10389842.html)
* [I.2: Avoid non-const global variables (isocpp.github.io)](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Ri-global)
* [I.3: Avoid singletons (isocpp.github.io)](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Ri-singleton)
* [Static_and_Global_Variables (Google C++ Style Guide)](http://link.zhihu.com/?target=https%3A//google.github.io/styleguide/cppguide.html%23Static_and_Global_Variables)

