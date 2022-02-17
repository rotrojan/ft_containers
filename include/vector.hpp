/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:00:27 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/17 23:47:55 by rotrojan         ###   ########.fr       */
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
// # include "NormalIterator.hpp"
// # include <iostream>

namespace ft {

	template <typename T, typename Allocator = std::allocator<T> > class vector {
		public:

// types:

			typedef T value_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			// typedef NormalIterator<pointer, vector> iterator;
			// typedef NormalIterator<const_pointer, vector> const_iterator;
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

			// capacity:

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

			// element access:

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
				this->_vector_shift_right(this->_start + index, this->_finish, 1);
				this->_alloc.construct(this->_start + index, val);
				++this->_finish;
				return (this->_start + index);
			}

			void	insert(iterator position, size_type n, T const &val) {
				difference_type index = std::distance(this->_start, position);
				if (this->size() + n > this->capacity())
					this->reserve(this->capacity() + n);
				this->_vector_shift_right(this->_start + index, this->_finish, n);
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
				this->_vector_shift_right(this->_start + index, this->_finish, additional_size);
				std::uninitialized_copy(first, last, this->_start + index);
				this->_finish += additional_size;
			}

			iterator	erase(iterator position) {
				this->_vector_shift_left(position, this->_finish, 1);
				// this->_alloc.destroy(this->_finish);
				--this->_finish;
				return (position);
			}

			iterator	erase(iterator first, iterator last) {
				difference_type size = std::distance(first, last); 
				this->_vector_shift_left(first, this->_finish, size);
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
			pointer _start;
			pointer _finish;
			pointer _end_of_storage;
			allocator_type _alloc;

			// utils

			void	_vector_shift_right(iterator position, iterator finish, difference_type offset) {
				if (this->empty() == false) {
					for (--finish; finish >= position; --finish) {
						this->_alloc.construct(finish + offset, *finish);
						// this->_alloc.destroy(finish);
					}
				}
			}

			void	_vector_shift_left(iterator position, iterator finish, difference_type offset) {
				if (this->empty() == false) {
					for (; position + offset < finish; ++position) {
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
