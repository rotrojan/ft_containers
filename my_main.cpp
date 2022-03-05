/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:42:08 by rotrojan          #+#    #+#             */
/*   Updated: 2022/03/04 21:33:20 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vector.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "rb_tree.hpp"

#include <iostream>
#include <vector>
#include <map>
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
	ft::map<int, int> ref_map;
	for (int i = 0; i < 10; ++i)
		ref_map.insert(ft::make_pair<int, int>(i, i * 2));
	ref_map.print();
	ft::map<int, int> map(ref_map.begin(), ref_map.end());
	// ft::pair<int, int> p1 = ft::make_pair<int, int>(1, 42);
	// ft::pair<int, int> p2 = ft::make_pair<int, int>(54, 42);
	// ft::pair<int, int> p3 = ft::make_pair<int, int>(23, 42);
	// ft::pair<int, int> p4 = ft::make_pair<int, int>(54, 42);
	// ft::pair<int, int> p5 = ft::make_pair<int, int>(34, 42);
	// ft::pair<int, int> p6 = ft::make_pair<int, int>(6, 42);
	// ft::pair<int, int> p7 = ft::make_pair<int, int>(42, 42);
	// map.insert(ft::make_pair<int, int>(1, 42));
	// map.insert(p2);
	// map.insert(p3);
	// map.insert(p4);
	// map.insert(p5);
	// map.insert(p6);
	// map.insert(p7);
	// ft::map<int, int>::const_iterator it = map.begin();
	// std::cout << *it << std::endl;
	// (void)it;
	// map.clear();
	map.print();
	// std::cout << p << std::endl;
	return (0);
}
