#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Fish
{
public:
	Fish(string name)
		: m_name(name)
	{
		cout << "Fish " << m_name << " Constructor!" << endl;
	}

	~Fish()
	{
		cout << "Fish " << m_name << " Destructor!" << endl;
	}

	void Swim()
	{
		//当所有权由move语义转移,可以执行Swim方法,如下的cout不会发生运行时错误,虽然此时unique_str为NULL
		//cout << "Fish Swim!" << endl;
		//然而当试图访问其成员变量时,会引发运行时错误:
		cout << "Fish " << m_name << " Swim!" << endl;
	}

	friend ostream & operator<<(ostream &out, Fish &obj);

private:
	string m_name;
};

ostream & operator<<(ostream &out, Fish &obj)
{
	out << &obj << "," << obj.m_name;
	return out;
}

void SwimHelp(const unique_ptr<Fish>& pFish) //临时对象->const &
//void SwimHelp(unique_ptr<Fish> pFish) //禁止拷貝语义
{
	pFish->Swim();
}

int main()
{
	/// types of smart pointers: the ownership model implemented
	/// Deep Copy, Copy on Write, Reference-Counted, Reference-Linked, Destructive Copy

	/// Destructive Copy-->std::auto_ptr
	/// 1)复制构造函数和赋值运算符不能接受 const 引用，因为它在复制源引用后使其无效
	/// 2)不仅不符合传统复制构造函数和赋值运算符的语义，还让智能指针类的用法不直观。复制或赋值后销毁源引用不符合预期
	/// 3)鉴于这种智能指针销毁源引用，这也使得它不适合用于 STL 容器，如std::vector 或其他任何动态集合类。这些容器需要在内部复制内容，这将导致指针失效。

	/// unique_ptr
	{
		//移动语义
		unique_ptr<Fish> pFish(new Fish("pFish"));
		pFish->Swim();

		unique_ptr<Fish> pFish2 = std::move(pFish);
		cout << "pFish:" << pFish << endl;
		cout << "pFish2" << pFish2 << endl;

		//Swim成员函数中访问成员变量,运行时错误
		//pFish->Swim();
		pFish2->Swim();

		//释放内存
		pFish.reset(); // pFish no ctrl, no descon called, no double free
		pFish2.reset();
		//运行时错误
		//pFish2->Swim();

		unique_ptr<Fish> pFish3(new Fish("pFish3"));
		pFish3.reset(new Fish("pFish3-reset"));
		pFish3->Swim();

		//释放控制权
		unique_ptr<Fish> pFish4(new Fish("pFish4"));
		//pFish4将控制权转移到传统指针,但未调用析构,未释放内存
		Fish* fish = pFish4.release();
		fish->Swim();
		//unique_ptr包含无效指针,运行时错误
		//pFish4->Swim();
		delete fish;
		fish = NULL;
	}

	/// shared_ptr
	/// 引用计数
	{
		shared_ptr<Fish> pFish(new Fish("shared_ptr"));
		shared_ptr<Fish> pFish2(pFish);

		cout << pFish2.use_count() << endl;

		pFish.reset();
		cout << pFish2.use_count() << endl;

		cout << "pInt=" << pFish << endl;
		cout << "pInt2=" << pFish2 << endl;

		if (pFish2)
		{
			pFish2->Swim();
		}
		
		if (pFish)
		{
			pFish->Swim();
		}	

		//引用为0时，释放指针
		//问：假设有一个应用程序，其中的 Class1 和 Class2 类分别包含一个指向 Class2 对象和 Class1
		//	对象的成员属性。在这种情况下，是否应使用引用计数指针？
		//答： 不应该。由于生命周期依赖性，引用计数将不会减少到零，导致两个类的对象永久性地留在
		//	堆中
		pFish2.reset();
		cout << pFish2.use_count() << endl;
	}

	/// weak_ptr
	/// weak_ptr的构造析构不会引起引用数的变化
	{
		shared_ptr<Fish> pfish(new Fish("pfish"));
		shared_ptr<Fish> pfish2(pfish);
		
		{
			weak_ptr<Fish> pwfish = pfish;
			cout << pwfish.use_count() << endl;

			shared_ptr<Fish> pfish3 = pwfish.lock();
			cout << pwfish.use_count() << endl;
		}

		cout << pfish.use_count() << endl;

		pfish.reset();
		pfish2.reset();

		weak_ptr<Fish> pwfish(pfish);
		cout << (pwfish.lock() == nullptr) << endl;
	}

    return 0;
}
