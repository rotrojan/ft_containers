/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:06:40 by rotrojan          #+#    #+#             */
/*   Updated: 2022/03/10 02:25:22 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP
# include "rb_tree.hpp"
# include "pair.hpp"
# include "algorithm.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
// set container
////////////////////////////////////////////////////////////////////////////////

	template <typename Key, typename Compare = std::less<Key>,
	typename Allocator = std::allocator<Key> >
	class set {

		public:
			typedef Key key_type;
			typedef Key value_type;
			typedef Compare key_compare;
			typedef Compare value_compare;
			typedef Allocator allocator_type;

		private:
			typedef rb_tree<value_type, allocator_type, value_compare> tree_type;

		public:
			typedef typename tree_type::const_iterator iterator;
			typedef typename tree_type::const_iterator const_iterator;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename tree_type::const_reverse_iterator reverse_iterator;
			typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

		private:
			allocator_type _alloc;
			key_compare _key_comp;
			tree_type _tree;

		public:
			explicit set(key_compare const &comp = key_compare(), allocator_type const alloc = allocator_type())
			: _alloc(alloc), _key_comp(comp), _tree(_alloc, _key_comp) {
			}

			template <typename InputIterator>
			set(InputIterator first, InputIterator last,
			key_compare const &comp = key_compare(), allocator_type const alloc = allocator_type())
			: _alloc(alloc), _key_comp(comp), _tree(_alloc, _key_comp) {
				this->insert(first, last);
			}

			set(set<key_type, key_compare, allocator_type> const &s)
			: _alloc(s._alloc), _key_comp(s._key_comp), _tree(_alloc, _key_comp) {
				this->insert(s.begin(), s.end());
			}

			~set() {
			}

			set<key_type, key_compare, allocator_type>
			&operator=(set<key_type, key_compare, allocator_type> const &rhs) {
				if (this != &rhs) {
					this->_tree = rhs._tree;
					this->_alloc = rhs._alloc;
					this->_key_comp = rhs._key_comp;
				}
				return (*this);
			}

// iterators

			iterator	begin(void) {
				return (this->_tree.begin());
			}

			const_iterator	begin(void) const {
				return (this->_tree.begin());
			}

			iterator	end(void) {
				return (this->_tree.end());
			}

			const_iterator	end() const {
				return (this->_tree.end());
			}

			reverse_iterator	rbegin(void) {
				return (this->_tree.rbegin());
			}

			const_reverse_iterator	rbegin(void) const {
				return (this->_tree.rbegin());
			}

			reverse_iterator	rend(void) {
				return (this->_tree.rend());
			}

			const_reverse_iterator	rend(void) const {
				return (this->_tree.rend());
			}

// capacity

			bool	empty(void) const {
				return (this->size() == 0);
			}

			size_type	size(void) const {
				return (this->_tree.size());
			}

			size_type	max_size(void) const {
				return (this->_tree.max_size());
			}

// modifiers

			ft::pair<iterator, bool>	insert(value_type const &p) {
				return (this->_tree.insert(p, this->_tree.end()));
			}

			iterator	insert(iterator position, value_type const &p) {
				return (this->_tree.insert(p, position).first);
			}

			template <typename InputIterator>
			void	insert(InputIterator first, InputIterator last) {
				for (; first != last; ++first)
					this->_tree.insert(*first, this->_tree.end());
			}

			void	erase(iterator position) {
				this->_tree.erase(*position);
			}

			size_type	erase(key_type const &key) {
				size_type ret = this->count(key);
				this->_tree.erase(key);
				return (ret);
			}

			void	erase(iterator first, iterator last) {
				iterator it;
				while (first != last) {
					it = first;
					++first;
					this->_tree.erase(*it);
				}
			}

			void swap(set<Key, Compare, Allocator> &m) {
				this->_tree.swap(m._tree);
			}

			void	clear(void) {
				this->_tree.clear();
			}

// observers

			key_compare	key_comp(void) const {
				return (this->_key_comp);
			}

			value_compare	value_comp(void) const {
				return (this->_key_comp);
			}

// map operations

			iterator	find(key_type const &key) {
				return (this->_tree.find(key));
			}

			const_iterator	find(key_type const &key) const {
				return (this->_tree.find(key));
			}

			size_type	count(key_type const &key) const {
				return (this->find(key) != this->end());
			}

			iterator	lower_bound(key_type const &key) {
				return (this->_tree.lower_bound(key));
			}

			const_iterator	lower_bound(key_type const &key) const {
				return (this->_tree.lower_bound(key));
			}

			iterator	upper_bound(key_type const &key) {
				return (this->_tree.upper_bound(key));
			}

			const_iterator	upper_bound(key_type const &key) const {
				return (this->_tree.lower_bound(key));
			}

			pair<iterator, iterator>	equal_range(key_type const &key) {
				iterator it = upper_bound(key);
				iterator ite = lower_bound(key);
				return (ft::make_pair<iterator, iterator>(ite, it));
			}

			pair<const_iterator, const_iterator>	equal_range(key_type const &key) const {
				const_iterator it = lower_bound(key);
				const_iterator ite = lower_bound(key);
				return (ft::make_pair<const_iterator, const_iterator>(ite, it));
			}

			void	print(void) {
				this->_tree.print();
			}
	};

	template <typename Key, typename Compare, typename Allocator>
	bool	operator==(set<Key, Compare, Allocator> const &lhs,
	set<Key, Compare, Allocator> const &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <typename Key, typename Compare, typename Allocator>
	bool	operator<(set<Key, Compare, Allocator> const &lhs,
	set<Key, Compare, Allocator> const &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <typename Key, typename Compare, typename Allocator>
	bool	operator!=(set<Key, Compare, Allocator> const &lhs,
	set<Key, Compare, Allocator> const &rhs) {
		return (!(lhs == rhs));
	}

	template <typename Key, typename Compare, typename Allocator>
	bool	operator>(set<Key, Compare, Allocator> const &lhs,
	set<Key, Compare, Allocator> const &rhs) {
		return (rhs < lhs);
	}

	template <typename Key, typename Compare, typename Allocator>
	bool	operator<=(set<Key, Compare, Allocator> const &lhs,
	set<Key, Compare, Allocator> const &rhs) {
		return (!(rhs < lhs));
	}

	template <typename Key, typename Compare, typename Allocator>
	bool	operator>=(set<Key, Compare, Allocator> const &lhs,
	set<Key, Compare, Allocator> const &rhs) {
		return (!(lhs < rhs));
	}

// specialized algorithm

	template <typename Key, typename Compare, typename Allocator>
	void swap(set<Key, Compare, Allocator> &lhs, set<Key, Compare, Allocator> &rhs) {
		lhs.swap(rhs);
	}
}

#endif
