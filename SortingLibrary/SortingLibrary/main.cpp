#include <cebulka_sort/all_algorithms.hpp>

#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <forward_list>


int main()
{
	std::vector<float> v1{12,8,10,3, 1,4,2,2,1,5,0,7,8,3,2,9,0,3,12,1,4 };
	std::list<int> v2{ 4,2,2,1,5,0,7,8,3,2,9,0,3,12,2,4 };
	std::deque<unsigned short> v3{ 1,4,2,2,1,5,0,7,8,3,2,9,0,3,12,3,4 };
	std::forward_list<long> v4{ 1,4,2,2,1,5,0,7,8,3,2,9,0,3,12 };

	ceb::stalin_sort(v1, ceb::decreasingly);

	auto condition = [](int a, int b)
	{
		return b == 0 ? true : a % b == 0;
	};

	ceb::stalin_sort(v2, condition);
	ceb::stalin_sort(v3);
	ceb::stalin_sort(v4);
	
	std::cout << "vector: ";

	for (int el : v1)
		std::cout << el << ' ';
	
	std::cout << "\nlist: ";

	for (int el : v2)
		std::cout << el << ' ';

	std::cout << "\ndeque: ";

	for (int el : v3)
		std::cout << el << ' ';

	std::cout << "\nforward_list: ";

	for (int el : v4)
		std::cout << el << ' ';

	std::cout << "\n";
}