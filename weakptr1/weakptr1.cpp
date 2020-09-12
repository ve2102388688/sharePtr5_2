#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Person : public std::enable_shared_from_this<Person>{
public:
	std::string name;
	std::shared_ptr<Person> monther;
	std::shared_ptr<Person> father;
	std::vector<std::weak_ptr<Person>> kids;			// weak_ptr

	Person(std::string name, 
		std::shared_ptr<Person> m = nullptr,
		std::shared_ptr<Person> f = nullptr)
		: name(name), monther(m), father(f) {
		//if (m != nullptr) {
		//	m->kids.push_back(shared_from_this());					// ERROR ������������ڹ��캯������shared_from_this
		//}
		//if (f != nullptr) {
		//	f->kids.push_back(shared_from_this());					// ERROR ������������ڹ��캯������shared_from_this
		//}
	}

	~Person() { std::cout << "delete " << name << std::endl; }

	void setParentsAndTheirKids(std::shared_ptr<Person> m = nullptr, std::shared_ptr<Person> f = nullptr) {
		monther = m;
		father = f;
		if (m != nullptr) {
			//m->kids.push_back(std::shared_ptr<Person>(this));		// ERROR �������shared_ptrָ��ͬһ������
			m->kids.push_back(shared_from_this());					// OK
		}
		if (f != nullptr) {
			//f->kids.push_back(std::shared_ptr<Person>(this));		// ERROR �������shared_ptrָ��ͬһ������
			f->kids.push_back(shared_from_this());					// OK
		}
	}
};


std::shared_ptr<Person> initFamily(const std::string& name) {
	std::shared_ptr<Person> mom(new Person(name + "'s mom"));
	std::shared_ptr<Person> father(new Person(name + "'s dad"));
	std::shared_ptr<Person> kid(new Person(name, mom, father));
	//std::shared_ptr<Person> kid(new Person(name));
	//kid->setParentsAndTheirKids(mom, father);

	mom->kids.push_back(kid);
	father->kids.push_back(kid);
	
	return kid;
}




int main()
{
	std::shared_ptr<Person> p = initFamily("nico");
	std::cout << "nico's family exists " << std::endl;
	std::cout << "- nico is shared " << p.use_count() << " times" << std::endl;
	std::cout << "- name of 1st kid's of nico's mom:  " << p->monther->kids[0].lock()->name << " times" << std::endl;

	p = initFamily("jim");
	std::cout << "jim's family exists " << std::endl;


	try	{
		std::shared_ptr<std::string> sp(new std::string("hi"));
		std::weak_ptr<std::string> wp = sp;
		sp.reset();														// �ͷ�shared_ptr�Ķ��� 
		std::cout << wp.use_count() << std::endl;						// 0
		std::cout << std::boolalpha << wp.expired() << std::endl;		// true
		std::shared_ptr<std::string> p(wp);								// execption: bad_weak_ptr
	} catch (const std::exception& e)
	{
		std::cerr << "execption: " << e.what() << std::endl;
	}

	// double free �쳣
	//int* p2 = new int;
	//std::shared_ptr<int> sp1(p2);
	//std::shared_ptr<int> sp2(p2);

	// shared_ptr ǿ��ָ��ת��
	std::shared_ptr<void> ap(new int);
	//std::shared_ptr<int>(static_cast<int*>(ap.get()));		// ERROR ����ʹ������ķ�ʽ
	std::static_pointer_cast<int*>(ap);

}