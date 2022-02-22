/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:06:40 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/23 00:48:28 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"

namespace ft {

	/*
	** pair structure
	*/

	template <typename T, typename U>
	struct pair {

		public:

			typedef T first_type;
			typedef U second_type;

			first_type first;
			second_type second;

			pair(void): first(first_type()), second(second_type()) {
			}

			template <typename T, template U>
			pair(pair<T, U> const *p): first(p.first), second(p.second) {
			}

			pair(first_type const &first, second_type const &second):
			first(first), second(second) {
			}

			pair	&operator=(pair const &rhs) {
				if (this != &rhs) {
					this->first = rhs.first;
					this->second = rhs.second;
				}
				return (*this);
			}
	};

	template <typename T, typename U>
	bool	operator==(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <typename T, typename U>
	bool	operator!=(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (!(lhs == rhs));
	}

	template <typename T, typename U>
	bool	operator<(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <typename T, typename U>
	bool	operator<=(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (!(rhs < lhs));
	}

	template <typename T, typename U>
	bool	operator>(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (rhs < lhs);
	}

	template <typename T, typename U>
	bool	operator>=(pair<T, U> const &lhs, pair<T, U> const &rhs) {
		return (!(lhs < rhs));
	}

	/*
	** make_pair function
	*/

	template <typename T, typename U>
	pair<T, U> make_pair(T first, U second) {
		return (pair<T, U>(first, second));
	}

	/*
	** map container
	*/

	template <typename Key, typename T, typename Compare = std::less<Key>,
	typename Allocator = allocator<ft::pair<Key const, T> > >
	class map {

	public:

		// typedefs:

		typedef Key key_type;
		typedef pair<Key const, T> value_type;
		typedef Compare key_compare;
		typedef iterator;
		typedef const_iterator;
		typedef Allocator<value_type>::pointer pointer;
		typedef Allocator<value_type>::reference reference;
		typedef Allocator<value_type>::const_reference const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef reverse_iterator;
		typedef const_reverse_iterator;


		class value_compare: public binary_function<value_type, value_type, bool> {

			private:

				friend class map;

			protected:

				Compare comp;

				value_compare(Compare c): comp(c) {
				}

			public:

				bool	operator()(value_type const &lhs, value_type const &rhs) {
					return comp(lhs.first, rhs.first);
				}

		};

		// allocation/deallocation:

		map(Compare const &comp = Compare());

		template <typename InputIterator>
		map(InputIterator first, InputIterator last, Compare const &comp = Compare());

		map(map<Key, T, Compare, Allocator> const &x);

		~map();

		map<Key, T, Compare, Allocator>	&operator=(map<Key, T, Compare, Allocator> const &x);

		void	swap(map<Key, T, Compare, Allocator> &x);

		// accessors:

		key_compare	key_comp() const;

		value_compare	value_comp() const;

		iterator	begin();

		const_iterator	begin() const;

		iterator	end();

		const_iterator	end() const;

		reverse_iterator	rbegin();

		const_reverse_iterator	rbegin();

		reverse_iterator	rend();

		const_reverse_iterator	rend();

		bool	empty() const;

		size_type	size() const;

		size_type	max_size() const;

		Allocator<T>::reference	operator[](key_type const &key);

		// insert/erase:

		pair<iterator, bool>	insert(value_type const &x);

		iterator	insert(iterator position, value_type const &x);

		template <typename InputIterator>
		void	insert(InputIterator first, InputIterator last);

		void	erase(iterator position);

		size_type	erase(key_type const &key);

		void	erase(iterator first, iterator last);

		// map operations:

		iterator	find(key_type const &key);

		const_iterator	find(key_type const &key) const;

		size_type	count(key_type const &key) const;

		iterator	lower_bound(key_type const &key);

		const_iterator	lower_bound(key_type const &key) const;

		iterator	upper_bound(key_type const &key);

		const_iterator	upper_bound(key_type const &key) const;

		pair<iterator, iterator>	equal_range(key_type const &key);

		pair<const_iterator, const_iterator>	equal_range(key_type const &key) const;

};
	template <typename Key, typename T, typename Compare, typename Allocator>
	bool	operator==(map<Key, T, Compare, Allocator> const &lhs,
	map<Key, T, Compare, Allocator> const &rhs);


	template <typename Key, typename T, typename Compare, typename Allocator>
	bool	operator<(map<Key, T, Compare, Allocator> const &lhs,
	map<Key, T, Compare, Allocator> const &rhs);

}

#endif
