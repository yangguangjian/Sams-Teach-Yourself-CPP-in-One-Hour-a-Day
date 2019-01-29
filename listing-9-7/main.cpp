
/**********************************************************************************************//**
 * \file	main.cpp.
 *
 * \brief	Implements the main class
 **************************************************************************************************/
 
#if 0
// 异常，未能定位，待查，搁置。
#include <iostream>

using namespace std;

class MyString
{
public:
	MyString(const char* ch)
	{
		cout << "ctor called" << endl;
		m_pBuffer = NULL;

		if (ch != NULL)
		{
			int strLen = strlen(ch);

			m_pBuffer = new char[strLen + 1];
			strcpy(m_pBuffer, ch);
		}
	}

	MyString(const MyString& other)
	{
		m_pBuffer = NULL;

		if (other.m_pBuffer != NULL) //不能从外部访问类的私有数据成员和方法
		{
			int strLen = strlen(other.m_pBuffer);

			m_pBuffer = new char(strLen + 1);
			
			strcpy(m_pBuffer, other.m_pBuffer);
			m_pBuffer[strLen] = 0;
		}
	}

	~MyString()
	{
		delete[] m_pBuffer;

		cout << "dtor called" << endl;
	}

	int GetStringLength() const
	{
		//z-string, may heap leak
		return strlen(m_pBuffer);
	}

	const char* GetString() const
	{
		return m_pBuffer;
	}

public:
	char* m_pBuffer;
};

void PrintMyString(MyString str)
{
	cout << "string length:" << str.GetStringLength() << endl;
	cout << "string content:" << str.GetString() << endl;
}

int main()
{
	MyString mystr("Hello World");
	PrintMyString(mystr);

    return 0;
}

#else

#include <iostream>
#include <string.h>
using namespace std;

class MyString
{
private:
	char* buffer;

public:
	MyString() {}
	MyString(const char* initString) // constructor
	{
		buffer = NULL;
		cout << "Default constructor: creating new MyString" << endl;
		if (initString != NULL)
		{
			buffer = new char[strlen(initString) + 1];
			strcpy(buffer, initString);

			cout << "buffer points to: 0x" << hex;
			cout << (unsigned int*)buffer << endl;
		}
	}

	MyString(const MyString& copySource) // Copy constructor
	{
		buffer = NULL;
		cout << "Copy constructor: copying from MyString" << endl;
		if (copySource.buffer != NULL)
		{
			// allocate own buffer 
			buffer = new char[strlen(copySource.buffer) + 1];

			// deep copy from the source into local buffer
			strcpy(buffer, copySource.buffer);

			cout << "buffer points to: 0x" << hex;
			cout << (unsigned int*)buffer << endl;
		}
	}

	// Destructor
	~MyString()
	{
		cout << "Invoking destructor, clearing up" << endl;
		delete[] buffer;
	}

	int GetLength()
	{
		return strlen(buffer);
	}

	const char* GetString()
	{
		return buffer;
	}
};

void UseMyString(MyString& str)
{
	cout << "String buffer in MyString is " << str.GetLength();
	cout << " characters long" << endl;

	cout << "buffer contains: " << str.GetString() << endl;
	return;
}

MyString CopySring(MyString& src)
{
	MyString copy(src.GetString());
	return copy;
}

int main()
{
	MyString sayHello("Hello from String Class");
	UseMyString(sayHello);

	{
		/*
		 * 问：在复制构造函数中，为何将指向源对象的引用作为参数？
		 * 答： 这是编译器对复制构造函数的要求。其原因是，如果按值接受源对象，复制构造函数将调用
		 * 自己，导致没完没了的复制循环。
		 */
		MyString str1;
		CopySring(str1);

		 //移动构造函数

	}

	return 0;
}

#endif