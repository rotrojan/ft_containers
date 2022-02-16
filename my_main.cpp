/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:42:08 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/16 21:13:24 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vector.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>
// using namespace ft;

int main(void) {

	ft::vector<int> vec_a;
	vec_a.insert(vec_a.begin(), 10, 42);
	ft::vector<int>::iterator it_a = vec_a.begin();
	ft::vector<int>::iterator ite_a = vec_a.end();
	std::cout << "vec_a = ";
	for (; it_a != ite_a; ++it_a)
		std::cout << *it_a << " ";
	std::cout << std::endl;

	ft::vector<int> vec_b;
	it_a = vec_a.begin();
	vec_b.insert(vec_b.begin(), it_a, ite_a);
	ft::vector<int>::iterator it_b = vec_b.begin();
	ft::vector<int>::iterator ite_b = vec_b.end();

	std::cout << "vec_b = ";
	for (; it_b != ite_b; ++it_b)
		std::cout << *it_b << " ";
	std::cout << std::endl;
	vec_b.resize(12);

	return (0);
}
