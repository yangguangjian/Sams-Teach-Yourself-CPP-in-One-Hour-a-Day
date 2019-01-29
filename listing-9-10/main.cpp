#include <iostream>
#include <string>

using namespace std;

class President
{
public:
    static President& getInstance()
    {
        static President ins;
        return ins;
    }

public:
    void cnt()
    {
        static int ncnt = 0;

        ++ncnt;
        cout << ncnt << endl;
    }

//private
public:
    President() {}
    President(const President&);
    President& operator=(const President&);

private:
    string m_strName;
};

class MonsterDB
{
public:
    MonsterDB() {}

public:
    static void DestoryInstance(MonsterDB* pdb)
    {
        if(pdb)
        {
            delete  pdb;
            pdb = NULL;
        }
    }

private:
    ~MonsterDB() {}
};

class Human
{
public:
    constexpr explicit Human(int age) : m_age(age) {}
	int m_age;
};

void howoldareu(Human h)
{
	cout << "human:" << h.m_age << endl;
}

#if 0
void howoldareu(int h)
{
	cout << "int" << h << endl;
}
#endif

int main()
{
    {
        President& one = President::getInstance();
    //  President second;
    //  second = one;
    //  second(one);

        one.cnt();

        President two;
        two.cnt();
    }

    {
        //MonsterDB db1; //private destructor
        MonsterDB* db2 = new MonsterDB;
        if(db2)
        {
            MonsterDB::DestoryInstance(db2);
        }
    }

	{
        //implicit
        //howoldareu(1);

        howoldareu(Human(1));
	}

    {
        //调用静态方法时，不会隐式地传递 this 指针，因为静态函数不与类实例相关联，而由所有实例共享。
        //要在静态函数中使用实例变量，应显式地声明一个形参，并将实参设置为 this 指针。
    }

    {
        //友元类
        //友元函数
    }

    {
        //共用体:与结构一样，成员默认公有，但共用体不能继承
        //sizeof用于共用体时,结果是共用体最大成员的长度

        struct ComplexType
        {
            union Value
            {
                int num;
                char alphabet;
            } value;

            Value v;
        };

        cout << "sizeof(ComplexType) = " << sizeof(ComplexType) << endl;
        ComplexType ct;
        ct.v.alphabet = 'a';
        cout << "ct.v.num = " << ct.v.num << endl;
    }

    {
        //聚合初始化:对于类来说,条件极为苛刻
        //聚合初始化只初始化共用体的第一个非静态成员
    }

    {
        //constexpr
        constexpr Human h1(12);
        Human h2(2); //非常量实体-->没有将实例 anotherPerson 声明为常量，因此编译器不会将实例化它的代码视为常量表达式
    }

    return 0;
}
