/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:42:08 by rotrojan          #+#    #+#             */
/*   Updated: 2022/01/31 16:25:16 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vector.hpp"
#include <vector>
#include <iostream>

int main(void) {
	std::vector<int> vec(5, 42);

	std::vector<int>::iterator it = vec.begin();
	std::cout << it.base() << std::endl;
	std::cout << *it.base() << std::endl;
	return (0);
}
