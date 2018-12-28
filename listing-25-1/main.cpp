#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

template <typename T>
void display(const T& container)
{
	for (auto it = container.cbegin(); it != container.cend(); ++it)
	{
		cout << *it << ", ";
	}

	cout << endl;
}

int main()
{
	///
	{
		bitset<4> bs1;
		cout << bs1 << endl;

		// 超长字符串使用前5个
		bitset<5> bs2("010111");
		cout << bs2 << endl;

		// 超长0b整形数使用后5个
		bitset<5> bs3(0b1010111);
		cout << bs3 << endl;

		bitset<8> bs4(255);
		/// 编译期行为
		//bitset<10> bs5(bs4);
		bitset<8> bs5(bs4);
		cout << bs4 << endl;
		cout << bs5 << endl;
	}

	/// methods and operators
	{
		bitset<8> inputBits;
		cout << "input bitset:" << endl;
#if 0
		cin >> inputBits;
#endif
		cout << inputBits.size() << ", " << inputBits.count() << endl;
		cout << inputBits << endl;

		bitset<8> flipInputBits(inputBits);
		flipInputBits.flip();
		cout << "flipInputbits:" << flipInputBits << endl;

		flipInputBits <<= (2);
		cout << "<< = 2:" << flipInputBits << endl;
		
		flipInputBits >>= 1;
		cout << ">> = 1:" << flipInputBits << endl;

		cout << "and:" << (inputBits & flipInputBits) << endl;
		cout << "or:" << (inputBits | flipInputBits) << endl;
		cout << "xor" << (inputBits ^ flipInputBits) << endl;
		cout << "not" << ~inputBits << endl;
	}

	/// vector<bool>
	{
		vector<bool> bf1(10, true);
		vector<bool> bf2(bf1);
		//列表初始化
		vector<bool> bf3{ true, true, false };

		display(bf1);
		display(bf2);

		bf1.push_back(false);
		display(bf1);
		bf1.flip();
		display(bf1);
	}

    return 0;
}
