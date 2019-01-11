#include <iostream>

using namespace std;

//类型转换是一种机制，强迫编译器遵从自己的意愿,让程序员能够暂时或永久性改变编译器对对象的解释

//请牢记，将 Derived*转换为 Base*被称为向上转
//换；这种转换是安全的。
//请牢记，将 Base*转换为 Derived*被称为向下转
//换；除非使用 dynamic_cast 并核实转换成功，否则
//这种转换不安全。
//请牢记，创建继承层次结构时，应尽量将函数
//声明为虚函数。这样通过基类指针调用这些函数时，
//如果该指针指向的是派生类对象，将调用相应类的
//函数版本。

//使用 dynamic_cast 时，别忘了对转换得到的指
//针进行检查，看其是否有效。
//设计应用程序时，不要使用 dynamic_cast 来依					---> 这句话不明白.有性能损失?
//赖于 RTTI。

class Base 
{
public:
	//运行时dynamic_cast的操作数必须包含多态类型,也即基类必须含有虚函数
	//一开始漏掉了public关键字,子类无法重写Base::~Base()
	virtual ~Base() {};
};
class Drived : public Base {};
class AnotherDrived : public Base {};
class Unreleated {};

class Display
{
public:
	void display() {};
};

void display(const Display* cd)
{
	//严重性	代码	说明	项目	文件	行	禁止显示状态
	//不能将“this”指针从“const Display”转换为“Display &”
	//cd->display();

	Display* d = const_cast<Display*>(cd);
	d->display();
}

void RTTITest(Base* base)
{
	Drived *d = dynamic_cast<Drived *>(base);
	if (NULL != d)
	{
		cout << "it's drived" << endl;
		return;
	}

	AnotherDrived *ad = dynamic_cast<AnotherDrived *>(base);
	if (NULL != ad)
	{
		cout << "it's anothor" << endl;
		return;
	}

	cout << "nonsense" << endl;
	return;
}

int main()
{
	//static_cast
	{
		//基本数据类型的显示转换
		double dpi = 3.14156;
		int ipi = static_cast<int>(dpi);

		//编译阶段的类型相关的向下类型转换

		//无法检测不完整的类型转换:
		Base* base = new Base;
		Drived* drived = static_cast<Drived*>(base);

		base = new Drived;
		drived = static_cast<Drived*>(base);

		//向上类型转换
		base = drived;

		//Unreleated* unreleated = static_cast<Unreleated*>(base); //类型转换无效
	}

	//dynamic_cat
	{
		//RTTI-->动态类型识别
		Base* pbase = new Base;
		Drived* pdri = new Drived;
		AnotherDrived* padri = new AnotherDrived;

		RTTITest(pbase);
		RTTITest(pdri);
		RTTITest(padri);
	}

	//reinterpret_cast
	{
		//与C风格类型转换最为接近,不管是否相关,有悖类型安全
		Base* pbase = new Base;
		Unreleated* punrelated = reinterpret_cast<Unreleated*>(pbase);
		unsigned char* pchar = reinterpret_cast<unsigned char*>(punrelated);
	}

	//const_cast
	{
		//关闭对象的访问修饰符const
	}

    return 0;
}
