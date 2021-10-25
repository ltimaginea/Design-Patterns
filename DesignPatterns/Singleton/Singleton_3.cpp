#include <iostream>
#include <cassert>

class Singleton
{
public:
	static Singleton* Instance()
	{
		if (instance_ == 0)
		{
			instance_ = new Singleton();
		}
		return instance_;
	}
public:
	~Singleton() {  }
private:
	// 将拷贝构造函数和拷贝赋值运算符声明为 private 但不定义它们，从而禁止拷贝操作
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
private:
	Singleton() {  }
private:
	static Singleton* instance_;
};

Singleton* Singleton::instance_ = 0;

int main()
{
	Singleton* a = Singleton::Instance();
	Singleton* b = Singleton::Instance();
	assert(a == b);

	// 完全不再使用后销毁Singleton实例的时机难以把握，当没有delete时会造成内存泄漏。
	// 当delete之后，对于那些已经获得Singleton实例的指针，它们将成为“空悬指针”，如程序中的 Singleton::instance_ , a 和 b 。
	delete Singleton::Instance();

	return 0;
}

// C++98 style的Singleton的缺点:
//	1. 完全不再使用后销毁Singleton实例的时机难以把握，当没有delete时会造成内存泄漏。当delete之后，对于那些已经获得Singleton实例的指针，它们将成为“空悬指针”，如示例中的 Singleton::instance_ , a 和 b 。
//	2. 存在线程安全的问题，因此还需要进一步优化（加锁）。
