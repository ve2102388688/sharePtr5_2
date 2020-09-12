#include <iostream>
#include <memory>
#include <vector>
#include <string>


int main()
{
	// 自定义deleter
	std::shared_ptr<std::string> pNico(new std::string("nico"), 
										[](std::string* p) {
											std::cout << "delete " << *p << std::endl;
											delete p;
										});
	//std::shared_ptr<std::string> pNico = new std::string("nico");		// 构造函数是explicit，隐式初始化出错
	std::shared_ptr<std::string> pJutta(new std::string("jutta"));
	// 使用reset赋值
	std::shared_ptr<std::string> pNico4;
	pNico4.reset(new std::string("nico"));
	//pNico4 = new std::string("nico");			// 只能使用上面的方式

	// 修改部分元素
	(*pNico)[0] = 'N';
	pJutta->replace(0, 1, "J");

	std::vector<std::shared_ptr<std::string>> whoMageCoffe;
	whoMageCoffe.push_back(pJutta);
	whoMageCoffe.push_back(pJutta);
	whoMageCoffe.push_back(pNico);
	whoMageCoffe.push_back(pJutta);
	whoMageCoffe.push_back(pNico);

	// 输出还是5次
	for (auto ptr : whoMageCoffe)
		std::cout << *ptr << "  ";
	std::cout << std::endl;

	// 对应的所有元素都会改变
	*pNico = "NIcolai";
	for (auto ptr : whoMageCoffe)
		std::cout << *ptr << "  ";
	std::cout << std::endl;

	pNico = nullptr;			// 不会马上清理，再主函数退出后清理
	//whoMageCoffe.resize(2);	

	std::cout << "use_count: " << whoMageCoffe[0].use_count() << std::endl;

	std::shared_ptr<int> p(new int[10], [](int* p) {delete[] p; });
	std::shared_ptr<int> p2(new int[10], std::default_delete<int[]>());
	//auto sp3 = std::make_shared<int[]>();



	return 0;
}














