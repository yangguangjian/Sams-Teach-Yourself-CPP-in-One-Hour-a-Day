#include <iostream>
#include <string>
#include <tuple>

using namespace std;

//预处理器进行死板的文字替换
#define ARRAY_LENGTH 25
#define PI 3.1415
#define MY_DOUBLE double
#define FAV_WHISKY "Jack Daniels"

//尽量修改为const变量
const int N_ARRAY_LENGTH = 25;

template <typename type>
const type& max(const type& v1, const type& v2)
{
	return v1 > v2 ? v1 : v2;
}

template <typename T, typename T2 = int>
class HoldVarTypeT
{
public:
// 	void setValue(const char* v)
// 	{
// 
// 	}

	void setValue(const T v)
	{
		//static_assert(sizeof(double) != sizeof(T), "okkkkkkkkkkkkkkkk");

		m_value = v;
	}

	//1.非常量成员函数
// 	T& getValue()
// 	{
// 		return m_value;
// 	}
	//2.常量成员函数不能返回非常量引用,因为不能保证被修改
// 	T& getValue() const
// 	{
// 		return m_value;
// 	}
	//3.按值返回-->
	//基本类型不能作为左值 holdInt.getValue() = 12;
	//自定义类型
// 	T getValue() const
// 	{
// 		return m_value;
// 	}
	//4.
	T& getValue()
	{
		return m_value;
	}

private:
	T m_value;
};

//具体化模版
template<> class HoldVarTypeT<int, int>
{
public:
	void setValue(const int v1, const int v2 = 12)
	{
		m_v1 = v1;
		m_v2 = v2;
	}

	int& getValue()
	{
		cout << "getValue in specialization" << endl;
		//非常量的初始化值必须为左值
		//return m_v1 + m_v2;
		return m_v1;
	}

private:
	int m_v1;
	int m_v2;
};

template <typename T>
class StaticTest
{
public:
	//静态成员变量要初始化，对静态成员使用泛型是无意义的
	//static T m_member;
	static int m_member;
};

//template <typename T> T StaticTest<T>::m_member = 12;
//template <typename T> int StaticTest<T>::m_member = 12;
template <typename T> int StaticTest<T>::m_member = 1;

template <typename Result, typename Operand>
Result sum(Result re, Operand op)
{
	cout << "internal sum called" << endl;

	return re + op;
}

template <typename Result, typename Operand, typename... Rest>
Result sum(Result& re, Operand op, Rest... rest)
{
	cout << "external sum called:" << sizeof...(rest) << endl;
	re += op;
	return sum(re, rest...);
}

template <typename T>
void DisplayTuple(T& tpl)
{
	int s = tuple_size<T>::value;
	cout << "tuple size:" << s << endl;
	cout << "last element in tuple:" << get<tuple_size<T>::value - 1>(tpl) << endl;
}

int main()
{
	{
		int numbers[ARRAY_LENGTH] = { 0 };
		MY_DOUBLE mydouble = PI;
		string mystring = FAV_WHISKY;

		//宏函数
		//使用宏函数减少了代码行，
		//这是一种细微的优势，诱使有些程序员使用宏来定义简单函数。宏函数将在编译前就地展开，因此简
		//单宏的性能优于常规函数调用。 这是因为函数调用要求创建调用栈、 传递参数等， 这些开销占用的 CPU
		//时间通常比 MIN 执行的计算还多。
		//然而，宏不支持任何形式的类型安全，这是一个严重的缺点。另外，复杂的宏调试起来也不容易。
		//如果需要编写独立于类型的泛型函数，又要确保类型安全，可使用模板函数，而不是宏函数。
	}

	{
		//类型安全
		//调用模板函数时没有必要显示指定类型。您无需指定模板参数的类型，因为编译器能够自动推断
		//出类型；但使用模板类时，需要这样做
		int i1(2), i2(1);
		double d1(1.2), d2(2.1);

		cout << max(i1, i2) << "," << max<int>(i1, i2) << "," << max<double>(d1, d2) << endl;
	}

	{
		//typename T2存在默认值,此处省略
		HoldVarTypeT<string> holdString;
		holdString.setValue("Hello");
		cout << holdString.getValue() << endl;
		holdString.getValue() = "World";
		cout << holdString.getValue() << endl;

		HoldVarTypeT<int> holdInt;
		holdInt.setValue(1);
		cout << holdInt.getValue() << endl;
		holdInt.getValue() = 12;
		cout << holdInt.getValue() << endl;

		char fname[] = "derek";
		HoldVarTypeT<char*> holdCharP;
		//const T&在实例化char*模版时,指的char*为const,也即char* const,对于此种情况不能指定const char*
		//ISO C++11 does not allow conversion from string literal to 'char *const'
		//gcc warning,而vc++认为是err
		//holdCharP.setValue("Hello World");
		//holdCharP.getValue() = "Yang";
		holdCharP.setValue(fname);
		
		cout << holdCharP.getValue() << endl;
	}

	// 模板类和静态成员
	// 每个具体化的实例保存单独的静态成员,具体化实例的对象之间共享静态成员
	{
// 		StaticTest<int> staticInt;
// 		cout << "staticInt.m_merber=" << staticInt.m_member << endl;
// 
// 		StaticTest<string> staticString;
// 		cout << "staticInt.m_merber=" << staticInt.m_member << endl;
// 
// 		StaticTest<char*> staticCharp;
// 		cout << "staticInt.m_merber=" << staticCharp.m_member << endl;

		StaticTest<int>::m_member = 12;
		StaticTest<string>::m_member = 21;
		cout << "StaticTest<int>::m_member = " << StaticTest<int>::m_member << endl;
		cout << "StaticTest<string>::m_member = " << StaticTest<string>::m_member << endl;

		//问：对于特定模板类，每个静态成员有多少个版本？
		//答：这完全取决于针对多少种类型实例化了该模板类。如果针对 int、 string 和自定义类型 X 实例
		//化了该模板类，则每个静态成员都有三个不同的版本—每种模板实例化一个。
	}

	//参数数量可变的模版函数
	{
		int ret = 0;
		sum(ret, 1, 2, 3, 4);
		cout << ret << endl;
	}

	//元组
	{
		cout << "-----------" << endl;

		tuple<int, char, string> tpl1(make_tuple(12, 't', "test"));
		DisplayTuple(tpl1);

		auto tpl2(make_tuple(12.2, true));
		DisplayTuple(tpl2);

		auto tpl3(tuple_cat(tpl2, tpl1));
		DisplayTuple(tpl3);

		double d(0);
		string str;
		tie(d, ignore, ignore, ignore, str) = tpl3;
		cout << "d=" << d << ", str=" << str << endl;
	}

    return 0;
}
