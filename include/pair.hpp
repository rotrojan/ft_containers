/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:05:33 by rotrojan          #+#    #+#             */
/*   Updated: 2022/03/05 02:08:29 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP
# include <ostream>

namespace ft {

////////////////////////////////////////////////////////////////////////////////
// pair structure
////////////////////////////////////////////////////////////////////////////////

	template <typename T, typename U>
	struct pair {
		typedef T first_type;
		typedef U second_type;

		first_type first;
		second_type second;

		pair(void): first(first_type()), second(second_type()) {
		}

		template <typename First, typename Second>
		pair(pair<First, Second> const &p)
		: first(p.first), second(p.second) {
		}

		pair(first_type const &first, second_type const &second)
		: first(first), second(second) {
		}

		pair	&operator=(pair const &rhs) {
			if (this != &rhs) {
				this->first = rhs.first;
				this->second = rhs.second;
			}
			return (*this);
		}

		operator pair<T const, U const>(void) const {
			return (pair<T const, U const>(this->first, this->second));
		}
	};

	template <typename T, typename U>
	bool	operator==(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <typename T, typename U>
	bool	operator!=(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (!(lhs == rhs));
	}

	template <typename T, typename U>
	bool	operator<(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <typename T, typename U>
	bool	operator<=(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (!(rhs < lhs));
	}

	template <typename T, typename U>
	bool	operator>(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (rhs < lhs);
	}

	template <typename T, typename U>
	bool	operator>=(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (!(lhs < rhs));
	}

// debug
	template <typename T, typename U>
	std::ostream	&operator<<(std::ostream &ostream, pair<T, U> const &rhs) {
		ostream << "first: " << rhs.first << ", second: " << rhs.second;
		return (ostream);
	}

////////////////////////////////////////////////////////////////////////////////
// make_pair function
////////////////////////////////////////////////////////////////////////////////

	template <typename T, typename U>
	pair<T, U> make_pair(T first, U second) {
		return (pair<T, U>(first, second));
	}

};

#endif
