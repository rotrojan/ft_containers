/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:42:08 by rotrojan          #+#    #+#             */
/*   Updated: 2022/03/10 21:18:40 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#define SIZE_MAX 10000

int main(void) {
	TESTED_NAMESPACE::vector<int> first;
	TESTED_NAMESPACE::vector<int> second(1000, int(42));
	TESTED_NAMESPACE::vector<int> third(second);
	TESTED_NAMESPACE::vector<int> const fourth(third.begin(), third.end());
	first = fourth;
	second.assign(500, 21);
	third.assign(second.begin(), second.end());
	TESTED_NAMESPACE::vector<int>::allocator_type alloc;
	int *ptr = alloc.allocate(1);
	alloc.destroy(ptr);
	std::cout << first.size() << std::endl;
	std::cout << first.capacity() << std::endl;
	std::cout << first.empty() << std::endl;
	first.clear();
	std::cout << first.size() << std::endl;
	std::cout << first.capacity() << std::endl;
	std::cout << first.empty() << std::endl;
	for (int i = 0; i < SIZE_MAX; i++)
		first.push_back(i);
	std::cout << first.size() << std::endl;
	std::cout << first.capacity() << std::endl;
	std::cout << first.empty() << std::endl;
	std::cout << first[42] << std::endl;
	std::cout << fourth[42] << std::endl;
	std::cout << first.at(21) << std::endl;
	std::cout << fourth.at(12) << std::endl;
	std::cout << first.front() << std::endl;
	std::cout << fourth.front() << std::endl;
	std::cout << first.back() << std::endl;
	std::cout << fourth.back() << std::endl;
	std::cout << second.size() << std::endl;
	std::cout << second.capacity() << std::endl;
	second.reserve(42);
	std::cout << second.capacity() << std::endl;
	std::cout << third.max_size() << std::endl;
	std::cout << third.size() << std::endl;
	third.resize(750, 12);
	std::cout << third.size() << std::endl;
	for (int i = 0; i < 20; i++)
		third.pop_back();
	std::cout << third.size()<< std::endl;
	first.insert(first.begin() + 17, 65);
	second.insert(second.begin() + 14, 5, 21);
	third.insert(third.begin() + 6, first.begin(), first.end());
	second.erase(second.end() - 23);
	third.erase(third.end() - 12, third.end());
	first.swap(second);
	swap(third, second);
	for (TESTED_NAMESPACE::vector<int>::const_iterator it = first.begin(), ite = first.end(); it != ite; ++it)
		std::cout << *it << std::endl;
	for (TESTED_NAMESPACE::vector<int>::iterator it = third.begin(), ite = third.end(); it != ite; it++)
		std::cout << *it << std::endl;
	for (TESTED_NAMESPACE::vector<int>::const_reverse_iterator it = fourth.rbegin(), ite = fourth.rend(); it != ite; ++it)
		std::cout << *it << std::endl;
	for (TESTED_NAMESPACE::vector<int>::reverse_iterator it = third.rbegin(), ite = third.rend(); it != ite; it++)
		std::cout << *it << std::endl;
	std::cout << (first == second) << std::endl;
	std::cout << (third != second) << std::endl;
	std::cout << (third <= second) << std::endl;
	std::cout << (third >= second) << std::endl;
	std::cout << (third < fourth) << std::endl;
	std::cout << (third > fourth) << std::endl;
	first.clear();
	for (int i = 0; i < 100000000; ++i)
		first.push_back(i);
	while (first.empty() == false)
		first.pop_back();
	return (0);
}
