/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:42:08 by rotrojan          #+#    #+#             */
/*   Updated: 2022/03/09 22:37:48 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vector.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"
#include "rb_tree.hpp"

#include <iostream>
#include <vector>
#include <map>

int main(void) {
	ft::set<int> s;
	s.insert(42);
	// ft::set<int>::iterator it = s.end();
	// (void)it;
	// std::cout << *it << std::endl;

	// ft::map<int, int> map;
	// for (int i = 0; i < 10; ++i)
		// map.insert(ft::make_pair<int, int>(i, i * 2));
	// // for (ft::map<int, int>::const_iterator it = map.begin(); it != map.end(); ++it)
	// std::cout << *(++map.begin()) << std::endl;
	return (0);
}
