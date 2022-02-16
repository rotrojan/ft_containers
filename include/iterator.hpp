/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:16:48 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/15 23:33:18 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include <iterator>

namespace ft {

	// iterator_traits: template struct defining several typedefs to ease type
	// manipulations throughout iterators, containers and algorithms

	template <typename Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <typename T>
	struct iterator_traits<T *> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T * pointer;
		typedef T & reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <typename T>
	struct iterator_traits<T * const> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T const * pointer;
		typedef T const & reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	// reverse_iterator class

	template <typename Iterator>
	class reverse_iterator {

		private:
			typedef iterator_traits<Iterator> _traits;

		public:
			typedef typename _traits::difference_type difference_type;
			typedef typename _traits::value_type value_type;
			typedef typename _traits::pointer pointer;
			typedef typename _traits::reference reference;
			typedef typename _traits::iterator_category iterator_category;
			typedef Iterator iterator_type;

			reverse_iterator(void): _current() {
			}

			explicit reverse_iterator(iterator_type it): _current(it) {
			}

			template <typename It>
			reverse_iterator(reverse_iterator<It> const &rit): _current(rit._current) {
			}

			Iterator base(void) const {
				return (this->_current);
			}

			reference	operator*(void) const {
				iterator_type tmp = this->_current - 1;
				return (*tmp);
			}

			pointer	operator->(void) const {
				iterator_type tmp = this->_current - 1;
				return (tmp);
			}

			reverse_iterator	&operator++(void) {
				--this->_current;
				return (*this);
			}

			reverse_iterator	operator++(int) {
				reverse_iterator tmp = *this;
				--this->_current;
				return (tmp);
			}

			reverse_iterator	&operator--(void) {
				++this->_current;
				return (*this);
			}

			reverse_iterator	operator--(int) {
				reverse_iterator tmp = *this;
				++this->_current;
				return (tmp);
			}

			reverse_iterator	operator+(difference_type n) const {
				return (reverse_iterator(this->_current - n));
			}

			reverse_iterator	&operator+=(difference_type n) {
				this->_current -= n;
				return (*this);
			}

			reverse_iterator	operator-(difference_type n) const {
				return (reverse_iterator(this->_current + n));
			}

			reverse_iterator	&operator-=(difference_type n) {
				this->current += n;
				return (*this);
			}

			reference operator[](difference_type n) const {
				return *(*this + n);
			}

		private:
			iterator_type _current;
	 };

	template <class Iterator>
	bool	operator==(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool	operator<(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool	operator!=(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool	operator>(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool	operator>=(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool	operator<=(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type	operator-(
	const reverse_iterator<Iterator> &lhs,
	const reverse_iterator<Iterator> &rhs) {
		return (rhs.base() - lhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator>	operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator> &rhs) {
		return (rhs.base() - n);
	}

}

#endif