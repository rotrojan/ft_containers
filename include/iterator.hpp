/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:16:48 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/20 14:12:47 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include <iterator>

namespace ft {

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
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	// NormalIterators can be used for vectors
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

			template <typename Iter>
			reverse_iterator(reverse_iterator<Iter> const &rit): _current(rit.base()) {
			}

			// template <typename Iter>
			// reverse_iterator	&operator=(reverse_iterator<Iter> const &rit) {
				// if (this != &rit)
					// this->_current = rit.base();
				// return (*this);
			// }

			Iterator	base(void) const {
				return (this->_current);
			}

			reference	operator*(void) const {
				iterator_type tmp = this->_current - 1;
				return (*tmp);
			}

			pointer	operator->(void) const {
				iterator_type tmp = this->_current - 1;
				return (&*tmp);
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

			difference_type	operator+(reverse_iterator<Iterator> const &iter) const {
				return (this->_current + iter._current);
			}

			reverse_iterator	&operator+=(difference_type n) {
				this->_current -= n;
				return (*this);
			}

			reverse_iterator	operator-(difference_type n) const {
				return (reverse_iterator(this->_current + n));
			}

			difference_type	operator-(reverse_iterator<Iterator> const &iter) const {
				return (iter._current - this->_current);
			}

			reverse_iterator	&operator-=(difference_type n) {
				this->_current += n;
				return (*this);
			}

			reference	operator[](difference_type n) const {
				return *(this->_current - n - 1);
			}

			operator	reverse_iterator<Iterator const>(void) const {
				return (reverse_iterator<Iterator const>(this->_current));
			}

		private:
			iterator_type _current;
	 };

	template <typename Iter1, typename Iter2>
	bool	operator==(
	reverse_iterator<Iter1> const &lhs,
	reverse_iterator<Iter2> const &rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool	operator<(
	reverse_iterator<Iter1> const &lhs,
	reverse_iterator<Iter2> const &rhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool	operator!=(
	reverse_iterator<Iter1> const &lhs,
	reverse_iterator<Iter2> const &rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool	operator>(
	reverse_iterator<Iter1> const &lhs,
	reverse_iterator<Iter2> const &rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool	operator>=(
	reverse_iterator<Iter1> const &lhs,
	reverse_iterator<Iter2> const &rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool	operator<=(
	reverse_iterator<Iter1> const &lhs,
	reverse_iterator<Iter2> const &rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator>
	reverse_iterator<Iterator>	operator+(
	typename reverse_iterator<Iterator>::difference_type n,
	reverse_iterator<Iterator> const &iter) {
		return (iter + n);
	}

	template <typename Iterator>
	typename reverse_iterator<Iterator>::difference_type	operator+(
	reverse_iterator<Iterator> const &lhs,
	reverse_iterator<Iterator> const &rhs) {
		return (lhs.base() + rhs.base());
	}
}

#endif
