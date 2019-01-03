#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename type>
struct DisplayItem
{
public:
	DisplayItem()
		: m_count(0)
	{

	}

	int get_count() const { return m_count; }
	void set_count(const int cnt) { m_count = cnt; }

	void operator()(const type& item)
	{
		++m_count;
		cout << m_count << ">" << item << endl;
	}

private:
	int m_count;
};

// 函数对象 vs 简单函数:存储与状态有关的信息
// 谓词:返回布尔值的特殊函数对象

int main()
{
	// 一元函数
	{
		vector<int> voi{ 1,2,3,4,5 };
		vector<char> voc{ 'a','b','b' ,'c' ,'b' ,'f' ,'b' };

		DisplayItem<int> di;
		di.set_count(10);
		cout << di.get_count();
		cout << endl << "-----" << endl;
		//已经存在的对象,pass by value
		//for_each对成员变量m_count的修改不会返回
		for_each(voi.begin(), voi.end(), di);
		cout << "m_count=" << di.get_count() << endl;

		cout << "-----" << endl;
		//使用DisplayItem<char>()构造临时对象
		for_each(voc.begin(), voc.end(), DisplayItem<char>());

		cout << endl << "-----" << endl;
		for_each(voi.begin(), voi.end(), [](const auto& item) {cout << item << endl; });
		cout << endl << "-----" << endl;
		for_each(voc.begin(), voc.end(), [](const auto& item) {cout << item << endl; });
	}

	// 一元谓词
	// std::find_if

	// 二元函数
	// std::transform

	// 二元谓词
	// std::sort

    return 0;
}
