
/**********************************************************************************************//**
 * \file	main.cpp.
 *
 * \brief	Implements the main class
 **************************************************************************************************/
 
#if 1
#include <iostream>

using namespace std;

class MyString
{
public:
	MyString(const char* ch)
	{
		cout << "ctor called" << endl;

		if (ch != NULL)
		{
			int strLen = strlen(ch);

			m_pBuffer = new char[strLen + 1];
			strcpy(m_pBuffer, ch);
		}
		else
		{
			m_pBuffer = NULL;
		}
	}

	MyString(const MyString& other)
	{
		m_pBuffer = NULL;

		if (other.m_pBuffer != NULL)
		{
			int strLen = strlen(other.m_pBuffer);

			m_pBuffer = new char(strLen + 1);
			
			strcpy(m_pBuffer, other.m_pBuffer);
			m_pBuffer[strLen] = 0;
		}
	}

	~MyString()
	{
		// shadow copy may double free
// 		if (m_pBuffer != NULL)
// 		{
// 			delete[] m_pBuffer;
// 			m_pBuffer = NULL;
// 		}

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

	MyString operator+ (const MyString& addThis)
	{
		MyString newString;

		if (addThis.buffer != NULL)
		{
			newString.buffer = new char[GetLength() + strlen(addThis.buffer) + 1];
			strcpy(newString.buffer, buffer);
			strcat(newString.buffer, addThis.buffer);
		}

		return newString;
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

void UseMyString(MyString str)
{
	cout << "String buffer in MyString is " << str.GetLength();
	cout << " characters long" << endl;

	cout << "buffer contains: " << str.GetString() << endl;
	return;
}

int main()
{
	MyString sayHello("Hello from String Class");
	UseMyString(sayHello);

	return 0;
}

#endif