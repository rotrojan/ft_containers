/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:16:48 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/07 17:57:08 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {

// iterator_traits: template struct defining several typedefs to ease type
// manipulations throughout iterators

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
		typedef random_access_iterator_tag iterator_category;
	};
	template <typename T>
	struct iterator_traits<T const *> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T * pointer;
		typedef T & reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <typename Iterator, typename Container>
	class NormalIterator {
		private:
			Iterator _current;
			typedef iterator_traits<Iterator> _traits;
		public:
			typedef Iterator iterator_type;
			typedef typename _traits::iterator_category iterator_category;
			typedef typename _traits::value_type value_type;
			typedef typename _traits::diference_type difference_type;
			typedef typename _traits::reference reference;
			typedef typename _traits::pointer pointer;

			NormalIterator(void): _current(nullptr) {
			}
			NormalIterator(Iterator const &it): _current(it) {
			}

			// Forward iterator requirements
			NormalIterator	&operator++(void) {
				++this->_current;
				return (*this);
			}
			NormalIterator	operator++(int) {
				NormalIterator tmp = this->_current;
				++this->_current;
				return (tmp);
			}
			pointer	operator->(void) const {
				return (this->_ptr);
			}
			reference	operator*(void) const {
				return (*this->_ptr);
			}

			// Bidirectional iterator requirements
			NormalIterator	&operator--(void) {
				--this->_ptr;
				return (*this);
			}
			NormalIterator	operator--(int) {
				NormalIterator tmp = this->_ptr;
				--this->_ptr;
				return (tmp);
			}

			// Random access iterator requirements
			NormalIterator	operator+(difference_type const &n) const {
				NormalIterator tmp(*this);
				tmp->_current += n;
				return (tmp);
			}
			NormalIterator	operator-(difference_type const &n) const {
				NormalIterator tmp(*this);
				tmp->_ptr -= rhs;
				return (tmp);
			}
			NormalIterator	&operator+=(difference_type const &n) {
				this->_current += n;
				return (*this);
			}
			NormalIterator	&operator-=(int const rhs) {
				this->_current -= n;
				return (*this);
			}
			reference	operator[](difference_type const &n) const {
				return (this->_ptr[n]);
			}
			Iterator const	&base(void) const {
				return (this->_current);
			}

			operator NormalIterator<const T>(void) {
				return (NormalIterator<const T>(*this));
			}
	}
	// Forward iterator requirements
	template <typename IterL, typename IterR>
	bool	operator==(NormalIterator<const IterL>(&lhs), NormalIterator<const IterR>(&rhs)) {
		return (lhs.base() == rhs.base());
	}

	template <typename IterL, typename IterR>
	bool	operator!=(NormalIterator<const IterL>(&lhs), NormalIterator<const IterR>(&rhs)) {
		return (lhs.base() != rhs.base());
	}

	// Random access Iterator
	template <typename IterL, typename IterR>
	bool	operator<=(NormalIterator<const IterL>(&lhs), NormalIterator<const IterR>(&rhs)) {
		return (lhs.base() <= rhs.base());
	}

	template <typename IterL, typename IterR>
	bool	operator>=(NormalIterator<const IterL>(&lhs), NormalIterator<const IterR>(&rhs)) {
		return (lhs.base() >= rhs.base());
	}

	template <typename IterL, typename IterR>
	bool	operator<(NormalIterator<const IterL>(&lhs), NormalIterator<const IterR>(&rhs)) {
		return (lhs.base() < rhs.base());
	}

	template <typename IterL, typename IterR>
	bool	operator>(NormalIterator<const IterL>(&lhs), NormalIterator<const IterR>(&rhs)) {
		return (lhs.base() > rhs.base());
	}

	// Operators '-' and '+' must also work with different types
	template <typename IterL, typename IterR, typename Container>
	NormalIterator	operator+(NormalIterator const &rhs) {
		NormalIterator tmp(*this);
		tmp->_ptr += rhs._ptr;
		return (tmp);
	}
	template <typename Iter, typename Container>
	NormalIterator<Iter, Container>	operator++(
			typename NormalIterator<Iter, Container>::difference_type n,
			NormalIterator const<Iter, Container>&iter) {
		return (NormalIterator<Iter, Container>(it.base() + n));
	}
#endif
