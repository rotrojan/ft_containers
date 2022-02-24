/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:42:08 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/24 22:50:49 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vector.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "rb_tree.hpp"
#include <iostream>
#include <vector>
// using namespace ft;

int main(void) {

	// ft::rb_node<int> node;
	ft::rb_tree<int> tree;
	for (int i = -50; i < 50; i++)
		tree.insert(i);
	// tree.insert(2);
	// tree.insert(1);
	// tree.erase(1);
	// tree.insert(4);
	// tree.insert(3);
	// tree.insert(125);
	// tree.insert(-43);
	// tree.insert(43);
	// tree.insert(-67);
	// tree.insert(54);
	// std::cout << tree.root->data << std::endl;
	tree.print();
	// tree.erase(13);
	// tree.print();
	// std::cout << std::endl;
	// tree.print();
	// tree._left_rotate(tree.root);
	// tree.print();
	// tree._right_rotate(tree.root);
	// tree.print();
	// ft::stack<int> stack;
	// ft::vector<int> vec(1, 42);
	// ft::vector<int>::const_iterator it(vec.begin());
	// std::cout << *it << std::endl;
	// ft::vector<int> vec_a;
	// vec_a.insert(vec_a.begin(), 10, 42);
	// ft::vector<int>::const_iterator it_a(vec_a.begin());
	// ft::vector<int>::const_iterator ite_a(vec_a.end());
	// std::cout << "vec_a = ";
	// for (; it_a != ite_a; ++it_a)
		// std::cout << *it_a << " ";
	// std::cout << std::endl;

	// ft::vector<int> vec_b;
	// it_a = vec_a.begin();
	// vec_b.insert(vec_b.begin(), it_a, ite_a);
	// ft::vector<int>::iterator it_b = vec_b.begin();
	// ft::vector<int>::iterator ite_b = vec_b.end();

	// std::cout << "vec_b = ";
	// for (; it_b != ite_b; ++it_b)
		// std::cout << *it_b << " ";
	// std::cout << std::endl;
	// vec_b.resize(12);

	// ft::vector<int> vec_c(vec_a.begin(), vec_a.end());
	// ft::vector<int>::iterator it_c = vec_c.begin();
	// ft::vector<int>::iterator ite_c = vec_c.end();

	// std::cout << "vec_c = ";
	// for (; it_c != ite_c; ++it_c)
		// std::cout << *it_c << " ";
	// std::cout << std::endl;
	// vec_b.resize(12);

	// ft::vector<long int> vec_d(12);

	return (0);
}
