/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:42:08 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/13 19:00:09 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vector.hpp"
#include "vector.hpp"
#include <iostream>

// using namespace ft;
int main(void) {

	ft::vector<int> vec(10, 42);
	ft::vector<int>::iterator it = vec.begin();
	ft::vector<int>::iterator ite = vec.end();
	for (; it != ite; ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	vec.push_back(1);
	// ft::vector<int>::iterator it = vec.begin();
	// std::cout << it.base() << std::endl;
	// std::cout << *it.base() << std::endl;
	return (0);
}
