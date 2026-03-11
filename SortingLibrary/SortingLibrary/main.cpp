#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <forward_list>
#include <chrono>

#include <cebulka_sort/all_algorithms.hpp>
#include "GnomeSort.hpp"

int main()
{
	std::vector<float> v1{ 4, 17, 5, 29, 6, 11, 38, 22, 9, 31, 14, 27, 2, 35, 19, 8, 41, 24, 13, 30, 5 };
	std::vector<float> v2{ 4, 17, 29, 6, 11, 38, 22, 9, 31, 14, 27, 2, 35, 19, 8, 41, 24, 13, 30, 5 };
	std::deque<unsigned short> v3{ 4, 17, 29, 6, 11, 38, 22, 9, 31, 14, 27, 2, 35, 19, 8, 41, 24, 13, 30, 5 };
	std::forward_list<long> v4{ 4, 17, 29, 6, 11, 38, 22, 9, 31, 14, 27, 2, 35, 19, 8, 41, 24, 13, 30, 5 };

	auto start1 = std::chrono::high_resolution_clock::now();
	ceb::bubble_sort(v1.begin(), v1.end());
	auto end1 = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);

	auto start2 = std::chrono::high_resolution_clock::now();
	ceb::bubble_sort(v2.begin(), v2.end(), ceb::decreasingly);
	auto end2 = std::chrono::high_resolution_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);

	auto start3 = std::chrono::high_resolution_clock::now();
	ceb::gnome_sort(v3.begin(), v3.end());
	auto end3 = std::chrono::high_resolution_clock::now();
	auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3);

	auto start4 = std::chrono::high_resolution_clock::now();
	ceb::gnome_sort(v4.begin(), v4.end());
	auto end4 = std::chrono::high_resolution_clock::now();
	auto duration4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end4 - start4);
	
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
	std::cout << "\nTime1: " << duration1.count() << " ns";
	std::cout << "\nTime2: " << duration2.count() << " ns";
	std::cout << "\nTime3: " << duration3.count() << " ns";
	std::cout << "\nTime4: " << duration4.count() << " ns";
}