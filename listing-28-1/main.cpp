#include <iostream>
#include <exception>
#include <string>

using namespace std;

class MyException : public exception
{
public:
	MyException(const char* reason)
		: exception(reason), m_reason(reason)
	{

	}

	//对异常类的约束,意味着异常类本身不会引发异常
	//virtual const char* what() const throw() //throw()未生效
	virtual const char* what() const
	{
		if (m_reason.size() == 0)
		{
			throw "reason empty";
		}

		return m_reason.c_str();
	}

private:
	string m_reason;
};

double divide(double d1, double d2)
{
	if (abs(d2 - 0) < 1e-10)
	{
		//是否在try块中?按照调用栈展开,退栈的过程中查看是否有catch此type exception?否则
		//throw "CustomException: Dividing by 0 is a crime";
		throw MyException("CustomException: Dividing by 0 is a crime");
	}

	return d1 / d2;
}

struct SA
{
	SA()
	{
		cout << "SA constructor" << endl;
	}

	~SA()
	{
		cout << "SA descructor" << endl;
	}
};

struct SB
{
	SB()
	{
		cout << "SB constructor" << endl;
	}

	~SB()
	{
		cout << "SB descructor" << endl;
	}
};

void funcb();

void funca()
{
	try
	{
		cout << "in funca" << endl;

		//临时对象构造就析构了
		//SA();
		///SB();

		SA a;
		SB b;

		funcb();
	}
	catch (const char* e)
	{
		cout << "catch exception in funca:" << e << endl;
		throw;
	}
}

void funcb()
{
	cout << "in funcb" << endl;

	SA a;
	SB b;

	throw "expcetion in funcb";
}

int main()
{
	/// desconstructor
	//引发异常时将对局部对象调用析构函数。如果因出现异常而被调用的析构函数也引发异常，将导致应用程序异常终止
	{
		try
		{
			cout << "in main" << endl;

			funca();
		}
		catch (const char* msg)
		{
			cout << "exception catched in main:" << msg << endl;
		}
	}

	/// 自定义异常
	{
		double d1(10), d2(0);

		try
		{
			cout << divide(d1, d2) << endl;
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "exception occured" << endl;
		}
	}

    return 0;
}
