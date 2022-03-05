/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:42:08 by rotrojan          #+#    #+#             */
/*   Updated: 2022/03/05 19:50:22 by rotrojan         ###   ########.fr       */
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

int main(void) {
	ft::map<int, int> map;
	for (int i = 0; i < 10; ++i)
		map.insert(ft::make_pair<int, int>(i, i * 2));
	// for (ft::map<int, int>::const_iterator it = map.begin(); it != map.end(); ++it)
	std::cout << *(++map.begin()) << std::endl;
	return (0);
}
