#include <iostream>
#include <memory>
#include <vector>
#include <string>


int main()
{
	// �Զ���deleter
	std::shared_ptr<std::string> pNico(new std::string("nico"), 
										[](std::string* p) {
											std::cout << "delete " << *p << std::endl;
											delete p;
										});
	//std::shared_ptr<std::string> pNico = new std::string("nico");		// ���캯����explicit����ʽ��ʼ������
	std::shared_ptr<std::string> pJutta(new std::string("jutta"));
	// ʹ��reset��ֵ
	std::shared_ptr<std::string> pNico4;
	pNico4.reset(new std::string("nico"));
	//pNico4 = new std::string("nico");			// ֻ��ʹ������ķ�ʽ

	// �޸Ĳ���Ԫ��
	(*pNico)[0] = 'N';
	pJutta->replace(0, 1, "J");

	std::vector<std::shared_ptr<std::string>> whoMageCoffe;
	whoMageCoffe.push_back(pJutta);
	whoMageCoffe.push_back(pJutta);
	whoMageCoffe.push_back(pNico);
	whoMageCoffe.push_back(pJutta);
	whoMageCoffe.push_back(pNico);

	// �������5��
	for (auto ptr : whoMageCoffe)
		std::cout << *ptr << "  ";
	std::cout << std::endl;

	// ��Ӧ������Ԫ�ض���ı�
	*pNico = "NIcolai";
	for (auto ptr : whoMageCoffe)
		std::cout << *ptr << "  ";
	std::cout << std::endl;

	pNico = nullptr;			// ���������������������˳�������
	//whoMageCoffe.resize(2);	

	std::cout << "use_count: " << whoMageCoffe[0].use_count() << std::endl;

	std::shared_ptr<int> p(new int[10], [](int* p) {delete[] p; });
	std::shared_ptr<int> p2(new int[10], std::default_delete<int[]>());
	//auto sp3 = std::make_shared<int[]>();



	return 0;
}














