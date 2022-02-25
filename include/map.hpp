/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:06:40 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/25 22:52:29 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
// # include "pair.hpp"
# include "rb_tree.hpp"

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

			template <typename First, typename Second>
			pair(pair<First, Second> const &p): first(p.first), second(p.second) {
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
	typename Allocator = std::allocator<ft::pair<Key const, T> > >
	class map {

	public:

		// typedefs:

		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<Key const, T> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		//typedef TO_DEFINE iterator;
		//typedef TO_DEFINE const_iterator;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		//typedef ft::reverse_iterator<iterator> reverse_iterator;
		//typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


		class value_compare: public std::binary_function<value_type, value_type, bool> {
			private:
				friend class map;
			protected:
				Compare comp;
				value_compare(Compare c): comp(c) {
				}
			public:
				bool	operator()(value_type const &lhs, value_type const &rhs) {
					return (comp(lhs.first, rhs.first));
				}
		};

	private:
		rb_tree<T> _tree;
		allocator_type _alloc;
		key_compare _key_comp;
		value_compare _value_comp;

	public:
		// allocation/deallocation:

		explicit map(Compare const &comp = Compare(), allocator_type const alloc = allocator_type())
		: _tree(), _alloc(alloc), _key_comp(comp), _value_comp(value_compare(comp)) {
		}

		// template <typename InputIterator>
		// map(InputIterator first, InputIterator last, Compare const &comp = Compare()) {

		// }

		map(map<Key, T, Compare, Allocator> const &x);

		~map() {
		}

		map<Key, T, Compare, Allocator>	&operator=(map<Key, T, Compare, Allocator> const &rhs) {
			if (this != &rhs) {
				this->_tree = rhs._tree;
				this->_alloc = rhs._alloc;
				this->_key_comp = rhs._key_comp;
				this->_value_comp = rhs._value_comp;
			}
			return (*this);
		}

		void	swap(map<Key, T, Compare, Allocator> &x);

		// accessors:

		key_compare	key_comp(void) const {
			return (this->_key_comp);
		}

		value_compare	value_comp(void) const {
			return (this->_value_comp);
		}

		//iterator	begin();

		//const_iterator	begin() const;

		//iterator	end();

		//const_iterator	end() const;

		//reverse_iterator	rbegin();

		//const_reverse_iterator	rbegin();

		//reverse_iterator	rend();

		//const_reverse_iterator	rend();

		bool	empty() const;

		size_type	size() const;

		size_type	max_size(void) const {
			return (this->_alloc.max_size());
		}

		reference	operator[](key_type const &key);

		// insert/erase:

		//pair<iterator, bool>	insert(value_type const &x);

		//iterator	insert(iterator position, value_type const &x);

		//template <typename InputIterator>
		//void	insert(InputIterator first, InputIterator last);

		//void	erase(iterator position);

		size_type	erase(key_type const &key);

		//void	erase(iterator first, iterator last);

		// map operations:

		//iterator	find(key_type const &key);

		//const_iterator	find(key_type const &key) const;

		size_type	count(key_type const &key) const;

		//iterator	lower_bound(key_type const &key);

		//const_iterator	lower_bound(key_type const &key) const;

		//iterator	upper_bound(key_type const &key);

		//const_iterator	upper_bound(key_type const &key) const;

		//pair<iterator, iterator>	equal_range(key_type const &key);

		//pair<const_iterator, const_iterator>	equal_range(key_type const &key) const;

};
	template <typename Key, typename T, typename Compare, typename Allocator>
	bool	operator==(map<Key, T, Compare, Allocator> const &lhs,
	map<Key, T, Compare, Allocator> const &rhs);


	template <typename Key, typename T, typename Compare, typename Allocator>
	bool	operator<(map<Key, T, Compare, Allocator> const &lhs,
	map<Key, T, Compare, Allocator> const &rhs);

}

#endif
