# Singleton

保证一个类仅有一个实例，并提供一个访问它的全局访问点。

## 实现要点

- 构造函数应该声明为非公有，从而禁止外界创建实例。

- 拷贝操作和移动操作也应该禁止。

- 只能通过 Singleton 的公有特定类操作访问它的唯一实例（C++中的一个公有静态成员函数）。

- 有局部静态对象和动态内存分配两种实现，C++11起最佳实践是局部静态对象的方法。

- 线程安全。C++11起， Singleton 最佳实践的局部静态对象方法是线程安全的。C++11标准保证：如果多个线程试图同时初始化同一静态局部变量，则初始化严格只发生一次。见《C++ Concurrency in Action》Second Edition，Chapter 3.3.1，或者见 [Storage class specifiers - cppreference.com](https://en.cppreference.com/w/cpp/language/storage_duration#Static_local_variables) :

  > If multiple threads attempt to initialize the same static local variable concurrently, the initialization occurs exactly once.

  之所以将 Singleton 类的唯一实例 `static Singleton instance;` 定义为类成员函数中的 static local object 而不是类的 static data member ，因为类的 static data member 本质上是 global variable ，多线程环境下， global variable 的初始化存在 race condition ，见：

  - [I.3: Avoid singletons (isocpp.github.io)](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Ri-singleton)

  - [I.2: Avoid non-const global variables (isocpp.github.io)](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Ri-global)

  - [To-do: Unclassified proto-rules (isocpp.github.io)](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-unclassified) :

    > avoid static class members variables (race conditions, almost-global variables)



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

* [I.3: Avoid singletons (isocpp.github.io)](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Ri-singleton)

* [Storage class specifiers - cppreference.com](https://en.cppreference.com/w/cpp/language/storage_duration#Static_local_variables)

* [C++ 单例模式总结与剖析 - 行者孙 - 博客园 (cnblogs.com)](https://www.cnblogs.com/sunchaothu/p/10389842.html)

* [I.2: Avoid non-const global variables (isocpp.github.io)](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Ri-global)

* [To-do: Unclassified proto-rules (isocpp.github.io)](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-unclassified) :

  > avoid static class members variables (race conditions, almost-global variables)

