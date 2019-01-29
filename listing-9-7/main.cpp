
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
	MyString() : buffer(NULL) {}
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
		if (buffer)
		{
			delete[] buffer;
		}
	}

	int GetLength()
	{
		//默认构造函数会跳过buffer的赋值,得到NULL,而strlen(buffer)是非法的
		return strlen(buffer);
	}

	const char* GetString()
	{
		return buffer;
	}

#if 0
	MyString(MyString&& moveSrc) // move constructor
	{
		cout << "Move constructor moves: " << moveSrc.buffer << endl;
		if (moveSrc.buffer != NULL)
		{
			buffer = moveSrc.buffer; // take ownership i.e.  'move'
			moveSrc.buffer = NULL;   // free move source
		}
	}

	MyString& operator= (MyString&& moveSrc) // move assignment op.
	{
		cout << "Move assignment op. moves: " << moveSrc.buffer << endl;
		if ((moveSrc.buffer != NULL) && (this != &moveSrc))
		{
			delete[] buffer; // release own buffer

			buffer = moveSrc.buffer; // take ownership i.e.  'move'
			moveSrc.buffer = NULL;   // free move source
		}

		return *this;
	}

	MyString operator+ (const MyString& addThis)
	{
		cout << "operator+ called: " << endl;
		MyString newStr;

		if (addThis.buffer != NULL)
		{
			newStr.buffer = new char[GetLength() + strlen(addThis.buffer) + 1];
			strcpy(newStr.buffer, buffer);
			strcat(newStr.buffer, addThis.buffer);
		}

		return newStr;
	}

	MyString& operator= (const MyString& copySrc) // Copy assignment op.
	{
		cout << "Copy assignment op. copies: " << copySrc.buffer << endl;
		if ((this != &copySrc) && (copySrc.buffer != NULL))
		{
			if (buffer != NULL)
				delete[] buffer;

			buffer = new char[strlen(copySrc.buffer) + 1];
			strcpy(buffer, copySrc.buffer);
		}

		return *this;
	}
#else
	// 以上为书中源码,以下为自己写的
	MyString(MyString&& moveSrc)
	{
		if (moveSrc.buffer != NULL)
		{
			//delete buffer; //移动构造中不能delete
			buffer = moveSrc.buffer;
			moveSrc.buffer = NULL;
		}
	}

	//如果等号是右侧
	MyString& operator=(MyString&& moveSrc) //数学语义:连等,所以返回引用
	{
		cout << "move assignment op. called" << endl;

		if (this != &moveSrc &&
			moveSrc.buffer != NULL)
		{
			if (buffer)
			{
				delete buffer;
			}

			buffer = moveSrc.buffer;
			moveSrc.buffer = NULL;
		}
		//=右侧为临时变量
		return *this;
	}

	MyString operator+(const MyString& addThis) //数学语义:不保存到第一个加数,所以按指返回
	{
		MyString tmp;

		if (addThis.buffer != NULL)
		{
			tmp.buffer = new char[GetLength() +  strlen(addThis.buffer) + 1]; //this buffer may null
			strcpy(tmp.buffer, buffer);
			strcat(tmp.buffer, addThis.buffer);
		}

		//局部变量构造临时变量返回，编译器知道局部变量即将析构，选择移动构造
		return tmp;
	}
#endif
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
	//MyString sayHello("Hello from String Class");
	//UseMyString(sayHello);

	{
		/*
		 * 问：在复制构造函数中，为何将指向源对象的引用作为参数？
		 * 答： 这是编译器对复制构造函数的要求。其原因是，如果按值接受源对象，复制构造函数将调用
		 * 自己，导致没完没了的复制循环。
		 */
		//MyString str1("Hello World");
		//CopySring(str1);
		//MyString str2(CopySring(str1));

		 // 移动构造函数
		 // 我们发现移动构造触发时机:局部变量,临时变量
		MyString Hello("Hello ");
		MyString World("World");
		MyString CPP(" of C++");

		MyString sayHelloAgain("overwrite this");
		sayHelloAgain = Hello + World + CPP;

//		MyString emptyStr;
//		MyString anothorPlus = emptyStr + Hello;
	}

	return 0;
}

#endif