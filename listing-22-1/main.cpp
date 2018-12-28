#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string> //不包含此头文件,cout string报错

using namespace std;

/// lamda exp是实现了operator()的匿名类(或结构)

/// lambda 表达式的语句块（{}）包含多条语句时，别忘了显式地指定返回类型。
/// 不要使用很长（包含多条语句）的 lambda 表达式，而应转而使用函数对象，因为每次使用 lambda表达式时，都需要重新定义它，这无助于提高代码的可重用性

/// []捕获列表传递局部变量,[=]传递所有局部变量
/// 值传递,不可修改,显示指定mutable可以在内部修改,外部无效,[&var, &var]使得exp对变量所做的修改在exp外部仍然有效


template <typename T>
struct DisplayItem
{
    void operator()(const T& element) const
    {
        cout << element << ", ";
    }
};

template <typename T>
void DisplayContent(const T& container)
{
    for (auto element = container.cbegin();
         element != container.cend();
         ++element)
    {
        cout << *element << ",";
    }
}

int main()
{
    ///// functor and lamda expression
    {
        vector<int> vec{1, 2, 3, 4, 5};
        list<char> lst{'a', 'b', 'c', 'd'};

        //functor
        for_each(vec.cbegin(), vec.cend(), DisplayItem<int>());
        cout << endl;

        for_each(lst.cbegin(), lst.cend(), DisplayItem<char>());
        cout << endl;

        //lamda expression
        //务必使用 const 来限定输入参数，在输入参数为引用时尤其如此。这样可避免无意间修改容器中元素的值。
        for_each(vec.cbegin(), vec.cend(), [](const int& ele) { cout << ele << "*"; });
        cout << endl;

        //use auto in lamda expression
        for_each(lst.cbegin(), lst.cend(), [](auto ele) { cout << ele << "*"; });
        cout << endl;
    }

    ///// unary predicate
    {
        vector<int> intnum{55, 77, 99, -50};
        auto itor = find_if(intnum.cbegin(), intnum.cend(), [](const int& i) {return i % 2 == 0;});

        if(itor != intnum.cend())
        {
            cout << "find_if:" << *itor << endl;
        }
    }

    ///// capture list
    {
#if 0
        vector<int> intnum{4, 9, 16, 15};
        int divisor(2);

        cout << "intput your divisor:" << endl;
        cin >> divisor;


        auto it = find_if(intnum.cbegin(), intnum.cend(),
                          [divisor](const int& div) {
                            // divisor = 2; //// non-mutable lamda
                            return div % divisor == 0;
                          }
        );

        if(it != intnum.cend())
        {
            cout << "it:" << *it << endl;
        }
#endif
    }

    ///// binary function
    {
		vector<int> intvec1{ 0, 1, 2, 3, 4 };
		vector<int> intvec2{ 100, 101, 102, 103, 104 };

		cout << endl << "intvec1:" << endl;
		DisplayContent(intvec1);
		cout << endl << "intvec2:" << endl;
		DisplayContent(intvec2);
		
		vector<int> result;
		result.resize(intvec1.size());
		transform(intvec1.begin(), intvec1.end(),
			intvec2.begin(), result.begin(), 
			[](const int one, const int two) {return one * two; });

		cout << endl << "result:" << endl;
		DisplayContent(result);
    }

    ///// binary predicate
    {
        vector<string> name{"jim", "Jack", "Sam", "Anna"};
		cout << endl << "Original:" << endl;
        DisplayContent(name);

		sort(name.begin(), name.end());
		cout << endl << "Sor Default:" << endl;
		DisplayContent(name);

		//没有找到接受“const std::basic_string<char, std::char_traits<char>, std::allocator<char>>”类型的左操作数的运算符(或没有可接受的转换)
        //sort(name.cbegin(), name.cend(),
		sort(name.begin(), name.end(),
			// 如果 lambda 表达式包含多行代码，您必须显式地指定返回类型
			// 对于多行lamda exp,仅便于确定返回值,不影响编译及功能
             [](const string& str1, const string& str2) -> bool {
                string str1l;
                str1l.resize(str1.size());
				//错误	C3892	“_UDest” : 不能给常量赋值
                //transform(str1.cbegin(), str1.end(), str1l.cbegin(), ::tolower);
				transform(str1.cbegin(), str1.cend(), str1l.begin(), ::tolower);

                string str2l;
                str2l.resize(str2.size());
                transform(str2.begin(), str2.end(), str2l.begin(), ::tolower);

                return str1l < str2l;
        });

		cout << endl << "Sort No Case:" << endl;
        DisplayContent(name);
    }

    return 0;
}
