/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:16:48 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/14 15:25:15 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include <iterator>

namespace ft {

// iterator_traits: template struct defining several typedefs to ease type
// manipulations throughout iterators

	template <typename Iterator> struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
	template <typename T> struct iterator_traits<T *> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T * pointer;
		typedef T & reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
	template <typename T> struct iterator_traits<T * const> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T const * pointer;
		typedef T const & reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	// template <typename Iterator, typename Container>
	// class NormalIterator {
		// private:
			// Iterator _current;
			// typedef iterator_traits<Iterator> _traits;
		// public:
			// typedef Iterator iterator_type;
			// typedef std::random_access_iterator_tag iterator_category;
			// typedef typename _traits::value_type value_type;
			// typedef typename _traits::difference_type difference_type;
			// typedef typename _traits::reference reference;
			// typedef typename _traits::pointer pointer;

			// NormalIterator(void): _current(NULL) {
			// }
			// NormalIterator(Iterator const &it): _current(it) {
			// }

			// // Forward iterator requirements
			// NormalIterator	&operator++(void) {
				// ++this->_current;
				// return (*this);
			// }
			// NormalIterator	operator++(int) {
				// NormalIterator tmp = this->_current;
				// ++this->_current;
				// return (tmp);
			// }
			// pointer	operator->(void) const {
				// return (this->_current);
			// }
			// reference	operator*(void) const {
				// return (*this->_current);
			// }

			// // Bidirectional iterator requirements
			// NormalIterator	&operator--(void) {
				// --this->_current;
				// return (*this);
			// }
			// NormalIterator	operator--(int) {
				// NormalIterator tmp = this->_current;
				// --this->_current;
				// return (tmp);
			// }

			// // Random access iterator requirements
			// NormalIterator	operator+(difference_type const &n) const {
				// NormalIterator tmp(*this);
				// tmp->_current += n;
				// return (tmp);
			// }
			// NormalIterator	operator-(difference_type const &n) const {
				// NormalIterator tmp(*this);
				// tmp._current -= n;
				// return (tmp);
			// }
			// NormalIterator	&operator+=(difference_type const &n) {
				// this->_current += n;
				// return (*this);
			// }
			// NormalIterator	&operator-=(difference_type const &n) {
				// this->_current -= n;
				// return (*this);
			// }
			// reference	operator[](difference_type const &n) const {
				// return (this->_current[n]);
			// }
			// Iterator const	&base(void) const {
				// return (this->_current);
			// }

			// operator NormalIterator<const Iterator, Container>(void) {
				// return (NormalIterator<const Iterator, Container>(*this));
			// }
	// };

	// // Forward iterator requirements

	// template <typename T, typename U, typename Container>
	// bool	operator==(NormalIterator<T, Container> const &lhs,
	// NormalIterator<U, Container> const &rhs) {
		// return (lhs.base() == rhs.base());
	// }

	// template <typename T, typename U, typename Container>
	// bool	operator!=(NormalIterator<T, Container> const &lhs,
	// NormalIterator<U, Container> const &rhs) {
		// return (lhs.base() != rhs.base());
	// }

	// // Random access Iterator
	// template <typename T, typename U, typename Container>
	// bool	operator<=(NormalIterator<T, Container> const &lhs,
	// NormalIterator<U, Container> const &rhs) {
		// return (lhs.base() <= rhs.base());
	// }

	// template <typename T, typename U, typename Container>
	// bool	operator>=(NormalIterator<T, Container> const &lhs,
	// NormalIterator<U, Container> const &rhs) {
		// return (lhs.base() >= rhs.base());
	// }

	// template <typename T, typename U, typename Container>
	// bool	operator<(NormalIterator<T, Container> const &lhs,
	// NormalIterator<U, Container> const &rhs) {
		// return (lhs.base() < rhs.base());
	// }

	// template <typename T, typename U, typename Container>
	// bool	operator>(NormalIterator<T, Container> const &lhs,
	// NormalIterator<U, Container> const &rhs) {
		// return (lhs.base() > rhs.base());
	// }

	// // Operators '-' and '+' must also work with different types
	// template <typename Iter, typename Container>
	// NormalIterator<Iter, Container>	operator+(
	// typename NormalIterator<Iter, Container>::difference_type n,
	// const NormalIterator<Iter, Container>&iter) {
		// return (NormalIterator<Iter, Container>(iter.base() + n));
	// }

	// template <typename Iter, typename Container>
	// NormalIterator<Iter, Container>	operator-(
	// typename NormalIterator<Iter, Container>::difference_type n,
	// const NormalIterator<Iter, Container>&iter) {
		// return (NormalIterator<Iter, Container>(iter.base() - n));
	// }
}

#endif
