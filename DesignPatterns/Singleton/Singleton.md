# Singleton

保证一个类仅有一个实例，并提供一个访问它的全局访问点。

## 实现要点

- 构造函数应该声明为非公有，从而禁止外界创建实例。
- 拷贝操作和移动操作也应该禁止。
- 只能通过 Singleton 的公有特定类操作访问它的唯一实例（C++中的一个公有静态成员函数）。
- 有局部静态对象和动态内存分配两种实现，C++11起最佳实践是局部静态对象的方法。
- 线程安全。

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
* [C++ 单例模式总结与剖析 - 行者孙 - 博客园 (cnblogs.com)](https://www.cnblogs.com/sunchaothu/p/10389842.html)

