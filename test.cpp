/*
��̳� ��ʽ�̳ж�����࣬�����ã�����
�������ŵ�ǰλ���൱�ڹ������ֵ�ƫ����

������ֻ��ų�Ա��������Ա�����Ǵ�������е�
�������⣨virtual���̳н�������μ̳е��µ� 1.��������� 2.������
ʵ��ԭ������Ĺ�������ֻ����һ�ݣ��ѹ������ֱ�������������ĩβ�������Ҫ���ʻ��๫����Ա��
  1. ����ͨ�������ָ����������
  2. ��������л�ȡƫ����
  3. �ӵ�ǰλ�ÿ�ʼ��ƫ��ָ����ƫ������
  4. ��ȡ���๫����Ա
  �ڴ����ˣ�����������ˣ����������ֵĻ����Առ�Ŀռ��ʱ���Ϳ������ֳ����� ֻ��Ҫ�������ָ�� ����Ҫ���ԭ��Ա����������ֻ����һ�����ݣ�û�ж����ԣ���ʱ�任�ռ���
  �������Ѿ����湫�����ֵ�ֵ�� ��ŵ��������ָ��

 2.��̬ ��ͬ�Ķ���ͨ��ͬһ��Ϊ������ͬ�Ľ��
 ���ɶ�̬������������������ȱһ���ɣ�
	1. �̳�
	2. �����а����麯����������Ҫ����д������麯����������ȫһ�£�����ֵ��������������ȫ����ͬ��������Ҳ���У�����{}��Ĳ�һ����������һ��
		�麯������д�������������ֵ���Բ�ͬ�����Ǳ����ǿ��Թ��ɸ��ӹ�ϵ��ָ������ã�Э�䣩
	3. �����麯�������ͱ���Ϊָ������� 

	�Ƕ�̬������ ������������ִ�ж�Ӧ���͵ĺ���
	��̬������ ��ָ�������ָ��Ķ��� ��ִ���Ǹ�����ĳ�Ա����
	ʵ�ʳ������ø���ָ��/����ִ�в�ͬ���������ͨ������ָ��/���õ����麯��ʱ��ʵ�ʵ������ǲ�ͬ��������д���麯���߼����ͻ������̬��Ϊ
	�������ʵ�ֶ�̬ �Ͳ�Ҫ�����麯����û������

����������̬��Ϊ��
	1. ���������͸��������ײ㺯������ͬ��������һ������������������ͳһ�����destructor
	2. ����ֻҪ����������������Ϊ�麯���������������͸��������ͻṹ����д
	3. һ�㶼��Ѹ�������������麯����������Է�ֹ��Դй©�����������ж����˸������Դ�������������麯��������ͷ�2����Դ��

	�������أ� ͬһ�������򣬺�������ͬ��������ͬ
	�������أ� ���������򣬺�������ͬ
	������д�����������򣬺�������ͬ�������ӿ���ȫһ�»���Э��
	����������㺯����д�������������ͻṹ�ɺ�������

*/
#include <string>
#include <iostream>
using namespace std;
//class Person
//{
//public:
//	string _name; // ����
//};
//
//class Student : virtual public Person
//{
//protected:
//	int _num; //ѧ��
//};
//class Teacher : virtual public Person
//{
//protected:
//	int _id; // ְ�����
//};
//class Assistant : public Student, public Teacher
//{
//protected:
//	string _majorCourse; // ���޿γ�
//};
//
//void test()
//{
//	Assistant as;
//	//�������࣬ ������
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
//	//��Ƭ
//	B b = d;
//	C c = d;
//}

//���ɵĶ�̬��������
// 1. �̳�
// 2. �����а����麯���� ����������д������麯��
// 3. �����麯�������ͱ���Ϊָ���������
class Person {
public:
	Person()
		:_num(new int)
	{}
	//virtual����ĺ���Ϊ�麯���� 
	virtual void BuyTicket() { cout << "��Ʊ-ȫ��" << endl; }

	virtual Person& Eat()
	{
		cout << "Person::Eat()" << endl;
		return Person();
	}
	//һ�㽨��Ѹ������������������麯���� ���Է�ֹ��̬��Ϊ���ڴ�й©������
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
	//�麯������д: ������д���麯�����亯���ӿڱ���ø�����ȫ��ͬ(����ֵ���������� �����б�
	virtual void BuyTicket() { cout << "��Ʊ-���" << endl; }

	//�麯������д�� ����---> ����ֵ���Բ�ͬ�����Ǳ����ǿ��Թ��ɸ��ӹ�ϵ��ָ��/���� ---> Э��
	virtual Student& Eat()
	{
		cout << "Student::Eat()" << endl;
		return Student();
	}
	//����������������Ϊ�麯��������������������븸����������������д
	//�������������������������ͬ��
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

	cout << "��̬" << endl;

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

	//��̬��Ϊ��
	//����ִ����һ����������ָ��/����ָ��Ķ���
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