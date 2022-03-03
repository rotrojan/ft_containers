/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:42:08 by rotrojan          #+#    #+#             */
/*   Updated: 2022/03/02 21:50:48 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vector.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "rb_tree.hpp"

#include <iostream>
#include <vector>
// #include <functional>
// using namespace ft;

int main(void) {

	
	// ft::rb_tree<int> tree;
	// for (int i = 2; i < 20; i++) {
		// tree.insert(i);
	// }
	// tree.print();
	// ft::rb_tree<int>::reverse_iterator it = tree.rbegin();
	// ft::rb_tree<int>::reverse_iterator ite = tree.rend();
	// for (; it != ite; it++) {
		// std::cout << *it << std::endl;
	// }
	ft::map<int, int> map;
	ft::pair<int, int> p = ft::make_pair<int, int>(1, 42);
	(void)p;
	// std::cout << p << std::endl;
	// map.insert(p);
	return (0);
}
