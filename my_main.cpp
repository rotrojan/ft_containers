/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:42:08 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/15 22:27:41 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vector.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>
// using namespace ft;
int main(void) {

	// std::cout << "wesh alors" << std::endl;
	ft::vector<int> vec;
	vec.reserve(1);
	vec[0] = 0;
	// vec[2] = 2;
	// vec[3] = 3;
	// vec[4] = 4;
	vec.push_back(12);

	ft::vector<int>::iterator it = vec.begin();
	ft::vector<int>::iterator ite = vec.end();
	for (; it != ite; ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	// ft::vector<int>::iterator it = vec.begin();
	// std::cout << it.base() << std::endl;
	// std::cout << *it.base() << std::endl;
	return (0);
}
