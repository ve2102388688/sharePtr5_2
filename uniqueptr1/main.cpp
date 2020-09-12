#include <iostream>
#include <memory>
#include <dirent.h>
#include <string>
#include <functional>

class classA {

};

class classADeleter {
public:
	void operator() (classA* p) {
		std::cout << "call delete for classA object" << std::endl;
	}
};

template <typename T>
using uniquePtr = std::unique_ptr<T, void (*)(T*)>;		// alias template


int main()
{
	// copyʱ��������е�ʱ��ERROR
	std::string* sp = new std::string("hello");
	std::unique_ptr<std::string> up1(sp);
	//std::unique_ptr<std::string> up2(sp);		// ERROR ���е�ʱ���֪��

	{
		// copy assignment��unique_ptr�Ǵ���ģ���Ҫmove
		std::unique_ptr<classA> up3(new classA);

		// unique_ptr��������
		//std::unique_ptr<classA> up4(up3);
		//std::unique_ptr<classA> up4(std::move(up3));

		// unique_ptr������assignment
		std::unique_ptr<classA> up4;
		//up4 = up3;
		up4 = std::move(up3);
	}

	{
		// C++11 unique_ptr֧�ֶ�array������Ϊ�ڲ��ṩһ��ƫ���⻯�ĺ���
		//std::unique_ptr<std::string> up(new std::string[10]);		//  ERROR runtime
		std::unique_ptr<std::string[]> up(new std::string[10]);		//  OK

		//std::cout << *up << std::endl;								// �������͵ģ���ֹʹ��*��->,��[]�����
		std::cout << up[0] << std::endl;

		// unique_ptr�����Լ���deleter,�����ǿɵ��õĺ����ࡢLambda������ָ�롢decltype��std::function
		// �ɵ��õĺ�����
		std::unique_ptr<classA, classADeleter> up2(new classA());
		 // ����ָ��
		std::unique_ptr<int, void (*)(int*)> up3(new int[10], [](int* p) {
			std::cout << "call delete for int[] object 1" << std::endl;
			delete[] p;});
		// std::function
		std::unique_ptr<int, std::function<void (int*)>> up4(new int[10], [](int* p) {
			std::cout << "call delete for int[] object 2" << std::endl;
			delete[] p;});
		// decltype
		auto l = [](int* p) {
			std::cout << "call delete for int[] object 3" << std::endl;
			delete[] p; };
		std::unique_ptr<int, decltype(l)> up5(new int[10], l);
		// alias template
		uniquePtr<int> up6(new int[10], [](int* p) {
			std::cout << "call delete for int[] object 4" << std::endl;
			delete[] p; });
	}

	{

	}
}