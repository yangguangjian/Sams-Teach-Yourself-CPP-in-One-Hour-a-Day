#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	// manipulator
   
	// std::cout
	{
#if 0
		cout << "enter an integer:";
		int input(0);
		cin >> input;

		cout << "in oct:" << oct << input << endl;
		cout << "in dec:" << hex << input << endl;

		cout << setiosflags(ios_base::hex | ios_base::showbase | ios_base::uppercase);
		cout << input << endl;

		cout << resetiosflags(ios_base::showbase);
		cout << input << endl;

		cout << setiosflags(ios_base::hex | ios_base::uppercase);
		cout << input << endl;

		const double PI = 22.0 / 7;
		cout << PI << endl;

		cout << setprecision(10);
		cout << "fixed:" << fixed << PI << endl;
		cout << "scientific:" << scientific << PI << endl;

		cout << setw(99) << setfill('*');

		cout << PI * 9.99 * 9.99 << endl;
#endif
	}

	//std::cin
	{
#if 0
		int i(0);
		double d(0.0);
		cout << "input int and double:" << endl;
		cin >> i >> d;
		cout << "i=" << i << ", d=" << d << endl;

		char ch1(0), ch2(0), ch3(0);
		cout << "input char:" << endl;
		cin >> ch1 >> ch2 >> ch3;
		cout << "chs:" << ch1 << ", " << ch2 << ", " << ch3 << endl;

		cin.ignore(INT_MAX, '\n');

		char chBuf[10];
		cout << "input a line" << endl;
		cin.get(chBuf, 9);
		cout << chBuf << endl;

		string name;
		cout << "intput name:" << endl;
		cin >> name;
		cout << name << endl;

		//cin.get()
		//继续cin前,应将流中的数据取出、清空等，不然换行符会被getline捕获
		//cin.ignore(INT_MAX, '\n');

		cout << "intput name again:" << endl;
		getline(cin, name);
		cout << name;
#endif
	}
	// std::fstream
	// public basic_iostream
	{
		cout << "write>" << endl;

		ofstream myfile;
		myfile.open("test.txt", ios_base::trunc);

		if (myfile.is_open())
		{
			myfile << "Hello World!";
			myfile << "Derek Yang";

			myfile.close();
		}

		cout << "read>" << endl;

		//fstream ifm; //使用fstream读取就有问题
		ifstream ifm;
		ifm.open("test.txt", ios_base::app);
		if (ifm.is_open())
		{
			string line;
			int i(0);
			while (ifm.good())
			{
				getline(ifm, line);
				cout << i << ":" << line << endl;
				i++;
			}

			ifm.close();
		}
	}

	// ios::binary
	{
		struct SHuman
		{
			SHuman()
			{

			}

			SHuman(const char* const fname, const char* lname, int age)
			{
				strncpy_s(m_fname, sizeof(m_fname), fname, sizeof(fname));
				strncpy_s(m_lname, sizeof(lname), fname, sizeof(lname));
				m_age = age;
			}

			char m_fname[128];
			char m_lname[128];
			int  m_age;
		};

		SHuman h1("Derek", "Yang", 18);

		ofstream of;
		of.open("human.dat", ios_base::trunc | ios_base::binary);
		of.write((const char*)&h1, sizeof(h1));
		of.close();

		ifstream ifs;
		ifs.open("human.dat", ios_base::binary);
		SHuman h2;
		ifs.read((char*)&h2, sizeof(SHuman));
		ifs.close();

		cout << "h2:" << h2.m_fname << "," << h2.m_lname << "," << h2.m_age << endl;
	}

	//std::stringstream
	//<TODO 示例过少,需要其他资料展开
	{
		stringstream ss;
		ss << 12;
		string intstr;
		ss >> intstr;
		cout << intstr;
	}

    return 0;
}
