/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:49:48 by rotrojan          #+#    #+#             */
/*   Updated: 2022/03/05 17:38:07 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft {

	template <typename InputIterator1, typename InputIterator2>
	bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {
		while (first1 != last1) {
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	bool	equal(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, BinaryPredicate pred) {
		while (first1 != last1) {
			if (pred(*first1, *first2) == false)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <typename InputIterator1, typename InputIterator2>
	bool	lexicographical_compare(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first1 > *first2)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <typename InputIterator1, typename InputIterator2, typename Compare>
	bool	lexicographical_compare(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || comp(*first2, *first1) == true)
				return (false);
			else if (comp(*first1, *first2) == true)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

}

#endif

