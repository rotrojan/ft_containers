/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:16:48 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/05 15:52:38 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {

// iterator_traits: template struct defining several typedefs to ease type
// manipulations throughout iterators

	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
	template <class T>
	struct iterator_traits<T *> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T * pointer;
		typedef T & reference;
		typedef random_access_iterator_tag iterator_category;
	};
	template <class T>
	struct iterator_traits<T const *> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T * pointer;
		typedef T & reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <typename Iterator>
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

			// Allow iterator to const_iterator conversion
			template <typename _Iter>
			NormalIterator(const __normal_iterator<_Iter,
						typename __enable_if<
						(std::__are_same<_Iter, typename _Container::pointer>::__value),
						_Container>::__type>& __i)
				: _M_current(__i.base()) { }

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

			// ??? what about operator= and destructor ???
			// NormalIterator const	&operator=(NormalIterator const &rhs) {
				// if (this != &rhs)
					// this->_ptr = rhs._ptr
				// return (*this);
			// }
			// ~NormalIterator(void) {
			// }
			operator NormalIterator<const T>(void) {
				return (NormalIterator<const T>(*this));
			}
	}

			NormalIterator	operator+(NormalIterator const &rhs) const {
				NormalIterator tmp(*this);
				tmp->_ptr += rhs._ptr;
				return (tmp);
			}
			NormalIterator	operator-(NormalIterator const &rhs) const {
				NormalIterator tmp(*this);
				tmp->_ptr -= rhs._ptr;
				return (tmp);
			}
	template <typename T, typename U>
	bool	operator==(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() == rhs.base());
	}

	template <typename T, typename U>
	bool	operator!=(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() != rhs.base());
	}

	template <typename T, typename U>
	bool	operator<=(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() <= rhs.base());
	}

	template <typename T, typename U>
	bool	operator>=(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() >= rhs.base());
	}

	template <typename T, typename U>
	bool	operator<(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() < rhs.base());
	}

	template <typename T, typename U>
	bool	operator<(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() > rhs.base());
	}


	template <typename T, typename U>
	bool	operator==(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() > rhs.base());
	}

	template <typename T, typename U>
	bool	operator!=(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() != rhs.base());
	}

	template <typename T, typename U>
	bool	operator<=(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() <= rhs.base());
	}

	template <typename T, typename U>
	bool	operator>=(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() >= rhs.base());
	}

	template <typename T, typename U>
	bool	operator<(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() < rhs.base());
	}

	template <typename T, typename U>
	bool	operator<(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() > rhs.base());
	}


	template <typename T, typename U>
	bool	operator==(VectorIterator<const T>(&lhs), VectorIterator<const U>(&rhs)) {
		return (lhs.base() > rhs.base());
	}
}

#endif
