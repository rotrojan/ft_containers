/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:00:27 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/19 20:11:19 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <stdexcept> 
# include <memory> 
# include "iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include "algorithm.hpp"
// # include "VectorIterator.hpp"
# include <iostream>

namespace ft {

	/*
	** VectorIterator class
	*/

	template <typename T>
	class VectorIterator {

		private:

			T *_current;

		public:

			typedef T value_type;
			typedef T *pointer;
			typedef T &reference;
			typedef std::random_access_iterator_tag iterator_category;
			typedef ptrdiff_t difference_type;

			VectorIterator(void): _current(NULL) {
			}

			VectorIterator(pointer ptr): _current(ptr) {
			}

			VectorIterator(VectorIterator const &vit): _current(vit._current) {
			}

			~VectorIterator(void) {
			}

			VectorIterator<T>	&operator=(VectorIterator<T> const &rhs) {
				if (this != &rhs)
					this->_current = rhs._current;
				return (*this);
			}

			// Forward iterator requirements

			VectorIterator	&operator++(void) {
				++this->_current;
				return (*this);
			}

			VectorIterator	operator++(int) {
				VectorIterator tmp = this->_current;
				++this->_current;
				return (tmp);
			}

			pointer	operator->(void) const {
				return (this->_current);
			}

			reference	operator*(void) const {
				return (*this->_current);
			}

			// Bidirectional iterator requirements

			VectorIterator	&operator--(void) {
				--this->_current;
				return (*this);
			}
			VectorIterator	operator--(int) {
				VectorIterator tmp = this->_current;
				--this->_current;
				return (tmp);
			}

			// Random access iterator requirements

			difference_type	operator+(VectorIterator<T> const &iter) const {
				return (this->_current + iter._current);
			}

			VectorIterator<T>	operator+(difference_type const &n) const {
				return (VectorIterator(this->_current + n));
			}

			difference_type	operator-(VectorIterator<T> const &iter) const {
				return (this->_current - iter._current);
			}

			VectorIterator<T>	operator-(difference_type const &n) const {
				return (VectorIterator(this->_current - n));
			}

			VectorIterator	&operator+=(difference_type const &n) {
				this->_current += n;
				return (*this);
			}

			VectorIterator	&operator-=(difference_type const &n) {
				this->_current -= n;
				return (*this);
			}

			reference	operator[](difference_type const &n) const {
				return (this->_current[n]);
			}

			pointer const	&base(void) const {
				return (this->_current);
			}

			operator	pointer(void) {
				return (this->_current);
			}

			operator	VectorIterator<const T>(void) const {
				return (VectorIterator<const T>(this->_current));
			}

	};

	// Forward iterator requirements

	template <typename T>
	bool	operator==(VectorIterator<T> const &lhs,
	VectorIterator<T> const &rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	bool	operator!=(VectorIterator<T> const &lhs,
	VectorIterator<T> const &rhs) {
		return (lhs.base() != rhs.base());
	}

	// Random access Iterator
	template <typename T>
	bool	operator<=(VectorIterator<T> const &lhs,
	VectorIterator<T> const &rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	bool	operator>=(VectorIterator<T> const &lhs,
	VectorIterator<T> const &rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename T>
	bool	operator<(VectorIterator<T> const &lhs,
	VectorIterator<T> const &rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	bool	operator>(VectorIterator<T> const &lhs,
	VectorIterator<T> const &rhs) {
		return (lhs.base() > rhs.base());
	}

	// Operators '-' and '+' must also work with different types

	template <typename T>
	VectorIterator<T>	operator+(
	typename VectorIterator<T>::difference_type n,
	const VectorIterator<T>&iter) {
		return (VectorIterator<T>(iter.base() + n));
	}

	template <typename T>
	VectorIterator<T>	operator-(
	typename VectorIterator<T>::difference_type n,
	const VectorIterator<T>&iter) {
		return (VectorIterator<T>(iter.base() - n));
	}

	/*
	** vector container
	*/

	template <typename T, typename Allocator = std::allocator<T> >
	class vector {

		public:

// types:

			typedef T value_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef VectorIterator<T> iterator;
			typedef VectorIterator<T const> const_iterator;
			// Since pointers are perfectly valid random access iterator, they
			// can be used as normal iterators
			// typedef T * iterator;
			// typedef T const * const_iterator;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef Allocator allocator_type;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			// ctors / allocators / copy-ctors / dtor

			explicit vector(
			allocator_type const &alloc = allocator_type()) :
			_start(NULL), _finish(NULL), _end_of_storage(NULL), _alloc(alloc) {
			}

			explicit vector(
			size_type n, T const &val = value_type(),
			allocator_type const &alloc = allocator_type()):
			_start(NULL), _finish(NULL), _end_of_storage(NULL), _alloc(alloc) {
				this->assign(n, val);
			}

			template <typename InputIterator>
			vector(
			InputIterator first, InputIterator last,
			allocator_type const &alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL):
			_start(NULL), _finish(NULL), _end_of_storage(NULL), _alloc(alloc) {
				this->assign(first, last);
			}

			vector(vector<T, Allocator> const &vct):
			_start(NULL), _finish(NULL), _end_of_storage(NULL), _alloc(vct._alloc) {
				this->assign(vct._start, vct._finish);
			}

			~vector(void) {
				// clear();
				this->_alloc.deallocate(this->_start, std::distance(this->_start, this->_end_of_storage));
			}

			vector<T, Allocator>	&operator=(vector<T,Allocator> const &vct) {
				if (this != &vct)
					this->assign(vct._start, vct._finish);
				return (*this);
			}

			template <typename InputIterator>
			void	assign(InputIterator first, InputIterator last) {
				this->clear();
				this->insert(this->_start, first, last);
			}

			void	assign(size_type n, T const &val) {
				this->clear();
				this->insert(this->_start, n, val);
			}

			allocator_type	get_allocator(void) const {
				return (this->_alloc);
			}

			// iterators

			iterator	begin(void) {
				return (iterator(this->_start));
			}

			const_iterator	begin(void) const {
				return (const_iterator(this->_start));
			}

			iterator	end(void) {
				return (iterator(this->_finish));
			}

			const_iterator	end(void) const {
				return (const_iterator(this->_finish));
			}

			reverse_iterator	rbegin(void) {
				return (reverse_iterator(this->_finish));
			}
			const_reverse_iterator	rbegin(void) const {
				return (const_reverse_iterator(this->_finsh));
			}

			reverse_iterator	rend(void) {
				return (reverse_iterator(this->_start));
			}

			const_reverse_iterator	rend(void) const {
				return (const_reverse_iterator(this->_start));
			}

			// capacity

			size_type size(void) const {
				return (std::distance(this->_start, this->_finish));
			}

			size_type max_size(void) const {
				return (this->_alloc.max_size());
			}

			void	resize(size_type new_size, value_type val = value_type()) {
				size_type old_size = this->size();
				if (new_size < old_size) {
					iterator new_finish = this->_start + new_size;
					// this->_destroy_range(new_finish, this->_finish);
					this->_finish = new_finish;
				} else {
					size_type additional_size = new_size - old_size;
					if (new_size > this->capacity()) 
						this->reserve(new_size + additional_size);
					std::uninitialized_fill_n(this->_finish, additional_size, val);
					this->_finish += additional_size;
				}
			}

			size_type	capacity(void) const {
				return (std::distance(this->_start, this->_end_of_storage));
			}

			bool	empty(void) const {
				return (this->_start == this->_finish);
			}

			void	reserve(size_type n) {
				if (n > this->max_size())
					throw std::length_error("vector::reserve");
				size_type capacity = this->capacity();
				if (n > capacity) {
					size_type old_size = this->size();
					pointer tmp = this->_alloc.allocate(n);
					// this->_destroy_range(this->_start, this->_finish);
					std::uninitialized_copy(this->_start, this->_finish, tmp);
					this->_alloc.deallocate(this->_start, capacity);
					this->_start = tmp;
					this->_finish = this->_start + old_size;
					this->_end_of_storage = this->_start + n;
				}
			}

			// element access

			reference	operator[](size_type n) {
				return (this->_start[n]);
			}

			const_reference	operator[](size_type n) const {
				return (this->_start[n]);
			}

			reference at(size_type n) {
				if (n >= this->size())
					throw std::out_of_range("vector::at");
				return (this->_start[n]);
			}

			const_reference at(size_type n) const {
				if (n >= this->size())
					throw std::out_of_range("veector::at");
				return (this->_start[n]);
			}

			reference	front(void) {
				return (*this->_start);
			}

			const_reference	front(void) const {
				return (*this->_start);
			}

			reference	back(void) {
				return (*(this->_finish - 1));
			}

			const_reference	back(void) const {
				return (*(this->_finish - 1));
			}

			// modifiers:

			void push_back(const T& x) {
				this->insert(this->_finish, x);
			}

			void pop_back(void) {
				this->erase(this->_finish);
			}

			iterator	insert(iterator position, T const &val) {
				difference_type index = std::distance(this->_start, position);
				if (this->_finish == this->_end_of_storage)
					this->reserve(this->capacity() + 1);
				this->_vector_shift_right(this->_start + index, 1);
				this->_alloc.construct(this->_start + index, val);
				++this->_finish;
				return (this->_start + index);
			}

			void	insert(iterator position, size_type n, T const &val) {
				difference_type index = std::distance(this->_start, position);
				if (this->size() + n > this->capacity())
					this->reserve(this->capacity() + n);
				this->_vector_shift_right(this->_start + index, n);
				std::uninitialized_fill_n(this->_start + index, n, val);
				this->_finish += n;
			}

			template <typename InputIterator>
			typename enable_if<!is_integral<InputIterator>::value, void>::type
			insert(iterator position, InputIterator first, InputIterator last) {
				difference_type index = std::distance(this->_start, position);
				difference_type additional_size = std::distance(first, last);
				if (this->size() + additional_size > this->capacity())
					this->reserve(this->capacity() + additional_size);
				this->_vector_shift_right(this->_start + index, additional_size);
				std::uninitialized_copy(first, last, this->_start + index);
				this->_finish += additional_size;
			}

			iterator	erase(iterator position) {
				this->_vector_shift_left(position, 1);
				// this->_alloc.destroy(this->_finish);
				--this->_finish;
				return (position);
			}

			iterator	erase(iterator first, iterator last) {
				difference_type size = std::distance(first, last); 
				this->_vector_shift_left(first, size);
				// this->_destroy_range(first, this->_finish);
				this->_finish -= size;
				return (first);
			}

			void	swap(vector<T, Allocator> &vct) {
				std::swap(this->_start, vct._start);
				std::swap(this->_finish, vct._finish);
				std::swap(this->_end_of_storage, vct._end_of_storage);
			}

			void	clear(void) {
				this->erase(this->_start, this->_finish);
			}

		private:
			iterator _start;
			iterator _finish;
			iterator _end_of_storage;
			allocator_type _alloc;

			// utils

			void	_vector_shift_right(iterator position, difference_type offset) {
				if (this->empty() == false) {
					for (iterator ite = this->_finish - 1; ite >= position; --ite) {
						this->_alloc.construct(ite + offset, *ite);
						// this->_alloc.destroy(finish);
					}
				}
			}

			void	_vector_shift_left(iterator position, difference_type offset) {
				if (this->empty() == false) {
					for (; position + offset < this->_finish; ++position) {
						this->_alloc.construct(position, *(position + offset));
						// this->_alloc.destroy(position + offset);
					}
				}
			}

			// void	_destroy_range(iterator first, iterator last) {
				// for (; first != last; ++first)
					// this->_alloc.destroy(first);
			// }
	};

	template <typename T, typename Allocator>
	bool	operator==(vector<T,Allocator> const &lhs, vector<T,Allocator> const &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <typename T, typename Allocator>
	bool	operator!=(vector<T,Allocator> const &lhs, vector<T,Allocator> const &rhs) {
		return (!(lhs == rhs));
	}

	template <typename T, typename Allocator>
	bool	operator<(vector<T,Allocator> const &lhs, vector<T,Allocator> const &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <typename T, typename Allocator>
	bool	operator>(vector<T,Allocator> const &lhs, vector<T,Allocator> const &rhs) {
		return (rhs < lhs);
	}

	template <typename T, typename Allocator>
	bool	operator<=(vector<T,Allocator> const &lhs, vector<T,Allocator> const &rhs) {
		return (lhs < rhs || lhs == rhs);
	}

	template <typename T, typename Allocator>
	bool	operator>=(vector<T,Allocator> const &lhs, vector<T,Allocator> const &rhs) {
		return (lhs > rhs || lhs == rhs);
	}

	// specialized algorithms:

	template <typename T, typename Allocator>
	void swap(vector<T,Allocator> &lhs, vector<T,Allocator> &rhs) {
		lhs.swap(rhs);
	}
}

#endif
