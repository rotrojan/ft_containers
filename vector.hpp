/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:00:27 by rotrojan          #+#    #+#             */
/*   Updated: 2022/01/28 19:06:05 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <iterator>

namespace ft {

	template <class T>
		class VectorIterator {
			public:
				VectorIterator(void) {
				};
				VectorIterator(VectorIterator const &vectoriterator): _ptr(vectoriterator._ptr) {
				};
				VectorIterator const	&operator=(VectorIterator const &rhs) {
					if (this != &rhs)
						this->_ptr = rhs._ptr
					return (*this);
				};
				~VectorIterator(void) {
				};
				VectorIterator	operator++(void) {
					++this->_ptr;
					return (*this);
				};
				VectorIterator	operator++(int) {
					Vector tmp = this->_ptr;
					++this->_ptr;
					return (tmp);
				};
				bool operator==(VectorIterator const *rhs) {
					if (this->_ptr == rhs._ptr)
						return (True);
					return (False);
				}
				bool operator!=(VectorIterator const *rhs) {
					if (this->_ptr == rhs._ptr)
						return (True);
					return (False);
				}
				VectorIteratoroperator--(void) {
					--this->_ptr;
					return (*this);
				};
				VectorIterator	operator--(int) {
					Vector tmp = this->_ptr;
					--this->_ptr;
					return (tmp);
				};
			private:
				Vector	*_ptr;
		};


	template <class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			// types:
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			// typedef Alocator::pointer iterator;
			// typedef implementation defined const_iterator;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			// construct/copy/destroy:
			explicit vector(const allocator_type &alloc = alocator_type()) {
			};
			explicit vector(size_type n, T const &value = value_type(), allocator_type const &alloc = allocator_type());
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last, const Allocator& = Allocator());

			// vector(const vector<T,Allocator>& x);
			// ~vector();
			// vector<T,Allocator>& operator=(const vector<T,Allocator>& x);

			// template <class InputIterator>
			// void assign(InputIterator first, InputIterator last);
			// void assign(size_type n, const T& u);
			// allocator_type get_allocator() const;

			// // iterators:
			// iterator begin();
			// const_iterator begin() const;
			// iterator end();
			// const_iterator end() const;
			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

			// // capacity:
			// size_type size() const;
			// size_type max_size() const;
			// void resize(size_type sz, T c = T());
			// size_type capacity() const;
			// bool empty() const;
			// void reserve(size_type n);

			// // element access:
			// reference operator[](size_type n);
			// const_reference operator[](size_type n) const;
			// const_reference at(size_type n) const;
			// reference at(size_type n);
			// reference front();
			// const_reference front() const;
			// reference back();
			// const_reference back() const;

			// // modifiers:
			// void push_back(const T& x);
			// void pop_back();
			// iterator insert(iterator position, const T& x);
			// void insert(iterator position, size_type n, const T& x);

			// template <class InputIterator>
			// void insert(iterator position, InputIterator first, InputIterator last);
			// iterator erase(iterator position);
			// iterator erase(iterator first, iterator last);
			// void swap(vector<T,Allocator>&);
			// void clear();
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

	// // specialized algorithms:
	// template <class T, class Allocator>
	// void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}

#endif
