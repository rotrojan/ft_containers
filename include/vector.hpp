/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:00:27 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/15 22:44:01 by rotrojan         ###   ########.fr       */
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
			typedef T * const const_iterator;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef Allocator allocator_type;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			// construct/alloc/copy/destroy:

			explicit vector(
			allocator_type const &alloc = allocator_type()):
			_start(NULL), _finish(NULL), _end_of_storage(NULL), _alloc(alloc) {
			}

			explicit vector(
			size_type n, T const &value = value_type(),
			allocator_type const &alloc = allocator_type()):
			_alloc(alloc) {
				this->reserve(n);
				this->_finish = this->_start + n;
				std::uninitialized_fill(this->_start, this->_finish, value);
				this->_end_of_storage = this->_finish;
			}

			template <class InputIterator>
			vector(
			InputIterator first, InputIterator last,
			allocator_type const &alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = NULL):
			_alloc(alloc) {
				difference_type size = last - first;
				this->_start = this->_alloc.allocate(size);
				this->_finish = this->_start + size;
				std::uninitialized_copy(first, last, this->_start);
				this->_end_of_storage = this->_finish;
			}

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

			// void assign(size_type n, const T& u);

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

			// void resize(size_type sz, T c = T());

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
					this->_destroy_range(this->_start, this->_finish);
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

			// void pop_back(void) {
				// this->erase(this->_finish - 1);
			// }

			iterator	insert(iterator position, const T &x) {
				std::cout << "capacity = " << this->capacity() << std::endl;
				std::cout << "size = " << this->size() << std::endl;
				if (this->_finish == this->_end_of_storage)
				{
					this->reserve(this->capacity() + 1);
					std::cout << "pouet" << std::endl;
				}
				this->_vector_shift(position, this->_finish, 1);
				// position = this->_alloc.allocate(1);
				this->_alloc.construct(position, x);
				++this->_finish;
				return (position);
			}

			void	insert(iterator position, size_type n, T const &x) {
				if (this->_start == this->_end_of_storage)
					this->reserve(this->capacity() + 1);
				this->_vector_shift(position, this->_finish, n);
				std::uninitialized_fill(position, position + n, x);
				this->_finish += n;
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last) {
				difference_type size = last - first;
				this->_vector_shift(position, this->_finish, size);
				std::uninitialized_copy(first, last, position);
				this->_finish += size;
			}

			iterator	erase(iterator position) {
				std::uninitialized_copy(position + 1, this->_finish, position);
				allocator_type::destroy(this->_finish);
				--this->_finish;
				return (position + 1);
			}

			// iterator	erase(iterator first, iterecursifrator last) {
				// std::uninitialized_copy(last + 1, this->_finish, first);
				// difference_type size = last - first; 
				// for (iterator it = this->_finish - size; it != this->_finish; ++it)
					// allocator_type::destroy(this->_finish);
				// this->_finish -= size;
				// return (first + size);
			// }

			// void	swap(vector<T, Allocator>&v) {
				// swap(this->_start, v._start);
				// swap(this->_finish, v._finish);
				// swap(this->_end_of_storage, v._end_of_storage);
			// }

			// void	clear(void) {
				// this->erase(this->_start, this->_finish);
			// }

		private:
			pointer _start;
			pointer _finish;
			pointer _end_of_storage;
			allocator_type _alloc;

			// utils

			void	_vector_shift(iterator position, iterator finish, size_type offset) {
				if (this->empty() == false) {
					for (--finish; finish >= position; --finish) {
						this->_alloc.construct(finish + offset, *finish);
						this->_alloc.destroy(finish);
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
