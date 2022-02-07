/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:31:52 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/07 15:39:51 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# define IS_INTEGRAL(x) template <>\
	struct is_integral<x> {\
	static bool const value = true;\
}

struct is_integral <typename T> {
	static bool const value = false;
}

IS_INTEGRAL(bool);
IS_INTEGRAL(char);
IS_INTEGRAL(char16_t);
IS_INTEGRAL(char32_t);
IS_INTEGRAL(wchar_t);
IS_INTEGRAL(signed char);
IS_INTEGRAL(short int);
IS_INTEGRAL(int);
IS_INTEGRAL(long int);
IS_INTEGRAL(long long int);
IS_INTEGRAL(unsigned char);
IS_INTEGRAL(unsigned short int);
IS_INTEGRAL(unsigned int);
IS_INTEGRAL(unsigned long int);
IS_INTEGRAL(unsigned long long int);

# undef IS_INTEGRAL(x)

#endif
