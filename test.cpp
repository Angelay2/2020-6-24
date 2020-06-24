/*
多继承 显式继承多个父类，父类用，隔开
虚基表：存放当前位置相当于公共部分的偏移量

对象当中只存放成员变量，成员函数是存放在类中的
菱形虚拟（virtual）继承解决了菱形继承导致的 1.数据冗余和 2.二义性
实现原理：基类的公共部分只保存一份，把公共部分保存在子类对象的末尾，如果需要访问基类公共成员，
  1. 首先通过虚基表指针访问虚基表，
  2. 从虚基表当中获取偏移量
  3. 从当前位置开始，偏移指定的偏移量，
  4. 获取基类公共成员
  内存变大了，数据量变大了，当公共部分的基类成员占的空间大时，就可以体现出有限 只需要存虚基表指针 不需要存放原成员，整个对象只保存一份数据，没有二义性，用时间换空间了
  父类中已经不存公共部分的值了 存放的是虚基表指针

 2.多态 不同的对象通过同一行为产生不同的结果
 构成多态的条件：（三个条件缺一不可）
	1. 继承
	2. 父类中包含虚函数，子类需要重新写父类的虚函数（必须完全一致（返回值、函数名、参数全都相同），重载也不行）除过{}里的不一样，其他都一样
		虚函数的重写例外情况：返回值可以不同，但是必须是可以构成父子关系的指针或引用（协变）
	3. 调用虚函数的类型必须为指针或引用 

	非多态看类型 看变量的类型执行对应类型的函数
	多态看对象 看指针或引用指向的对象 就执行那个对象的成员函数
	实际场景：用父类指针/引用执行不同的子类对象，通过父类指针/引用调用虚函数时，实际调用是是不同的子类重写的虚函数逻辑，就会产生多态行为
	如果不想实现多态 就不要定义虚函数，没有意义

析构函数多态行为：
	1. 子类析构和父类析构底层函数名相同，编译器一般会把析构函数的名字统一处理成destructor
	2. 所以只要父类析构函数定义为虚函数，则子类析构和父类析构就会构成重写
	3. 一般都会把父类析构定义成虚函数，这个可以防止资源泄漏（可能子类中定义了更多的资源，如果不定义成虚函数，则会释放2次资源）

	函数重载： 同一个作用域，函数名相同，参数不同
	函数隐藏： 父子作用域，函数名相同
	函数重写：父子作用域，函数名相同，函数接口完全一致或者协变
	如果不能满足函数重写的所有条件，就会构成函数隐藏

*/
#include <string>
#include <iostream>
using namespace std;
//class Person
//{
//public:
//	string _name; // 姓名
//};
//
//class Student : virtual public Person
//{
//protected:
//	int _num; //学号
//};
//class Teacher : virtual public Person
//{
//protected:
//	int _id; // 职工编号
//};
//class Assistant : public Student, public Teacher
//{
//protected:
//	string _majorCourse; // 主修课程
//};
//
//void test()
//{
//	Assistant as;
//	//数据冗余， 二义性
//	as._name = "123";
//	as.Student::_name = "123";
//	as.Teacher::_name = "456";
//	cout << sizeof(as) << endl;
//}

//class A
//{
//public:
//	int _a;
//};
//
//class B : virtual public A
//{
//public:
//	int _b;
//};
//class C : virtual public A
//{
//public:
//	int _c;
//};
//
//class D : public B, public C
//{
//public:
//	int _d;
//};

//void test()
//{
//	D d;
//	d.B::_a = 1;
//	d._b = 2;
//	d.C::_a = 3;
//	d._c = 4;
//	d._d = 5;
//
//	//切片
//	B b = d;
//	C c = d;
//}

//构成的多态的条件：
// 1. 继承
// 2. 父类中包含虚函数， 并且子类重写父类的虚函数
// 3. 调用虚函数的类型必须为指针或者引用
class Person {
public:
	Person()
		:_num(new int)
	{}
	//virtual定义的函数为虚函数， 
	virtual void BuyTicket() { cout << "买票-全价" << endl; }

	virtual Person& Eat()
	{
		cout << "Person::Eat()" << endl;
		return Person();
	}
	//一般建议把父类的析构函数定义成虚函数， 可以防止多态行为下内存泄漏的问题
	virtual ~Person()
	{
		delete _num;
		cout << "~Person()" << endl;
	}
protected:
	int* _num;
};

class Student : public Person
{
public:
	Student()
		:_str(new char[10])
	{}
	//虚函数的重写: 子类重写的虚函数，其函数接口必须好父类完全相同(返回值，函数名， 参数列表）
	virtual void BuyTicket() { cout << "买票-半价" << endl; }

	//虚函数的重写： 例外---> 返回值可以不同，但是必须是可以构成父子关系的指针/引用 ---> 协变
	virtual Student& Eat()
	{
		cout << "Student::Eat()" << endl;
		return Student();
	}
	//如果父类的析构函数为虚函数，则子类的析构函数与父类析构函数构成重写
	//编译器编译的析构函数名是相同的
	virtual ~Student()
	{
		delete[] _str;
		cout << "~Student()" << endl;
	}
private:
	char* _str;

};

void func(Person p)
{
	p.BuyTicket();
}

void func2(Person& p)
{
	p.BuyTicket();
}

void func3(Person* p)
{
	p->BuyTicket();
}

void func4(Person& p)
{
	p.Eat();
}

void test()
{
	Person p;
	Student s;

	/*p.BuyTicket();
	s.BuyTicket();*/

	func(p);
	func(s);

	cout << "多态" << endl;

	func2(p);
	func2(s);

	func3(&p);
	func3(&s);

	func4(p);
	func4(s);
}

void test2()
{
	/*Person p;
	Student st;*/

	//多态行为：
	//具体执行哪一个函数，看指针/引用指向的对象
	/*Student* ptr = new Student;
	Person* ptrs = new Student;*/

	Student* ptr3 = (Student*) new Person;

	/*delete ptr;
	delete ptrs;*/

	delete ptr3;
}

int main()
{
	//test();
	test2();
	return 0;
}