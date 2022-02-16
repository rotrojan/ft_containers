/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:00:27 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/17 00:25:17 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <stdexcept> 
# include <memory> 
# include "iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

# include <iostream>
namespace ft {

	template <typename T, typename Allocator = std::allocator<T> > class vector {
		public:

// types:

			typedef T value_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef T * iterator;
			typedef T const * const_iterator;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef Allocator allocator_type;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			// construct/alloc/copy/destroy:

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

			// template <typename InputIterator>
			// vector(
			// InputIterator first, InputIterator last,
			// allocator_type const &alloc = allocator_type(),
			// typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = NULL):
			// _alloc(alloc) {
				// difference_type size = last - first;
				// this->_start = this->_alloc.allocate(size);
				// this->_finish = this->_start + size;
				// std::uninitialized_copy(first, last, this->_start);
				// this->_end_of_storage = this->_finish;
			// }

			vector(const vector<T, Allocator>&v): vector(v._start, v._finish) {
			}

			~vector(void) {
				// clear();
				allocator_type().deallocate(this->_start, this->_start - this->_finish);
			}

			vector<T, Allocator>	&operator=(const vector<T,Allocator>&v) {
				if (this != &v) {
					std::uninitialized_copy(v._start, v._finish, this->_start);
				}
			}

			// template <class InputIterator>
			// void	assign(InputIterator first, InputIterator last);

			void	assign(size_type n, T const &val) {
				this->clear();
				this->insert(this->_start, n, val);
			}

			allocator_type	get_allocator(void) const {
				return (this->_alloc);
			}

			// iterators:
			iterator	begin(void) {
				return (this->_start);
			}

			const_iterator	 begin(void) const {
				return (this->_start);
			}

			iterator	end(void) {
				return (this->_finish);
			}

			const_iterator	end(void) const {
				return (this->_finish);
			}

			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

			// capacity:

			size_type size(void) const {
				return (this->_finish - this->_start);
			}

			size_type max_size(void) const {
				return (this->_alloc.max_size());
			}

			void	resize(size_type new_size, value_type val = value_type()) {
				size_type old_size = this->size();
				if (new_size < old_size) {
					iterator new_finish = this->_start + new_size;
					this->_destroy_range(new_finish, this->_finish);
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
				return (this->_end_of_storage - this->_start);
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
					iterator tmp = this->_alloc.allocate(n);
					std::uninitialized_copy(this->_start, this->_finish, tmp);
					this->_alloc.deallocate(this->_start, capacity);
					this->_start = tmp;
					this->_finish = this->_start + old_size;
					this->_end_of_storage = this->_start + n;
				}
			}

			// element access:

			reference	operator[](size_type n) {
				return (this->_start[n]);
			}

			const_reference	operator[](size_type n) const {
				return (this->_start[n]);
			}

			reference at(size_type n) {
				return (this->_start[n]);
			}

			const_reference at(size_type n) const {
				return (this->start[n]);
			}

			reference	front(void) {
				return (*this->_start);
			}

			const_reference	front(void) const {
				return (this->_start);
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
				difference_type index = position - this->_start;
				if (this->_finish == this->_end_of_storage)
					this->reserve(this->capacity() + 1);
				this->_vector_shift_right(this->_start + index, this->_finish, 1);
				this->_alloc.construct(this->_start + index, val);
				++this->_finish;
				return (this->_start + index);
			}

			void	insert(iterator position, size_type n, T const &val) {
				difference_type index = position - this->_start;
				if (this->size() + n > this->capacity())
					this->reserve(this->capacity() + n);
				this->_vector_shift_right(this->_start + index, this->_finish, n);
				std::uninitialized_fill_n(this->_start + index, n, val);
				this->_finish += n;
			}

			template <class InputIterator>
			typename enable_if<!is_integral<InputIterator>::value, void>::type
			insert(iterator position, InputIterator first, InputIterator last) {
				difference_type index = position - this->_start;
				difference_type additional_size = last - first;
				if (this->size() + additional_size > this->capacity())
					this->reserve(this->capacity() + additional_size);
				this->_vector_shift_right(this->_start + index, this->_finish, additional_size);
				std::uninitialized_copy(first, last, this->_start + index);
				this->_finish += additional_size;
			}

			iterator	erase(iterator position) {
				this->_vector_shift_left(position, this->_finish, 1);
				this->_alloc.destroy(this->_finish);
				--this->_finish;
				return (position);
			}

			iterator	erase(iterator first, iterator last) {
				difference_type size = last - first; 
				this->_vector_shift_left(first, this->_finish, size);
				this->_destroy_range(first, this->_finish);
				this->_finish -= size;
				return (first);
			}

			// void	swap(vector<T, Allocator>&v) {
				// swap(this->_start, v._start);
				// swap(this->_finish, v._finish);
				// swap(this->_end_of_storage, v._end_of_storage);
			// }

			void	clear(void) {
				this->erase(this->_start, this->_finish);
			}

		private:
			pointer _start;
			pointer _finish;
			pointer _end_of_storage;
			allocator_type _alloc;

			// utils

			void	_vector_shift_right(iterator position, iterator finish, difference_type offset) {
				if (this->empty() == false) {
					for (--finish; finish >= position; --finish) {
						this->_alloc.construct(finish + offset, *finish);
						this->_alloc.destroy(finish);
					}
				}
			}

			void	_vector_shift_left(iterator position, iterator finish, difference_type offset) {
				if (this->empty() == false) {
					for (; position + offset < finish; ++position) {
						this->_alloc.construct(position, *(position + offset));
						this->_alloc.destroy(position + offset);
					}
				}
			}

			void	_destroy_range(iterator first, iterator last) {
				for (; first != last; ++first)
					this->_alloc.destroy(first);
			}
	};

	// template <class T, class Allocator>
	// bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// template <class T, class Allocator>
	// bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// template <class T, class Allocator>
	// bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// template <class T, class Allocator>
	// bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// template <class T, class Allocator>
	// bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// template <class T, class Allocator>
	// bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// specialized algorithms:

	// template <class T, class Allocator>
	// void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}

#endif