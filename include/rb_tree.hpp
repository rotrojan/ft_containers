/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:00:00 by rotrojan          #+#    #+#             */
/*   Updated: 2022/03/01 21:45:50 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP
# include <sstream>
# include <iostream>
# include <string>
# include "iterator.hpp"

namespace ft {

	typedef enum e_color {
		RED = false,
		BLACK = true
	} t_color;

////////////////////////////////////////////////////////////////////////////////
// rb_node class
////////////////////////////////////////////////////////////////////////////////

	template <typename T>
	struct rb_node {

		enum e_color color;
		rb_node *parent;
		rb_node *left;
		rb_node *right;
		T data;

		rb_node(t_color color = RED, rb_node *parent = NULL,
		rb_node *left = NULL, rb_node *right = NULL)
		: color(color), parent(parent), left(left), right(right) {
		}

		rb_node(rb_node const &node) {
			*this = node;
		}

		~rb_node(void) {
		}

		rb_node	&operator=(rb_node const &rhs) {
			if (this != &rhs) {
				this->color = rhs.color;
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->right = rhs.right;
			}
			return (*this);
		}
	};

////////////////////////////////////////////////////////////////////////////////
// rb_treeIterator class
////////////////////////////////////////////////////////////////////////////////

	template <typename T>
	class rb_treeIterator {

		public:
			typedef T value_type;
			typedef T * pointer;
			typedef T & reference;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef std::ptrdiff_t difference_type;
			typedef rb_node<T> * node_ptr;

		private:
			node_ptr _current;
			node_ptr _root;
			node_ptr _nil;

		public:
			rb_treeIterator(void)
			: _current(NULL), _root(NULL), _nil(NULL) {
			}

			rb_treeIterator(node_ptr node, node_ptr root, node_ptr nil)
			: _current(node), _root(root), _nil(nil) {
			}

			rb_treeIterator(rb_treeIterator const &rbtit)
			: _current(rbtit._current), _root(rbtit._root), _nil(rbtit._nil) {
			}

			~rb_treeIterator(void) {
			}

			rb_treeIterator	&operator=(rb_treeIterator const &rhs) {
				if (this != &rhs) {
					this->_current = rhs.current;
					this->_root = rhs.root;
					this->_nil = rhs.nil;
				}
				return (*this);
			}

// forward iterator requirements

			rb_treeIterator	&operator++(void) {
				this->_current = this->_next(this->_current);
					return (*this);
			}

			rb_treeIterator	operator++(int) {
				rb_treeIterator tmp(this->_current, this->_root, this->_nil);
				this->_current = this->_next(this->_current);
				return (tmp);
			}

			pointer	operator->(void) {
				return (this->_current->data);
			}

			reference	operator*(void) {
				return (this->_current->data);
			}

			bool	operator==(rb_treeIterator const &rhs) {
				return (this->_current == rhs._current);
			}

			bool	operator!=(rb_treeIterator const &rhs) {
				return (this->_current != rhs._current);
			}

// bidirectional iterator requirements

			rb_treeIterator	&operator--(void) {
				if (this->_current == this->_nil)
					this->_current = this->_max(this->_root);
				else
					this->_current = this->_prev(this->_current);
				return (*this);
			}

			rb_treeIterator	operator--(int) {
				rb_treeIterator tmp(this->_current, this->_root, this->_nil);
				if (this->_current == this->_nil)
					this->_current = this->_max(this->_root);
				else
					this->_current = this->_prev(this->_current);
				return (tmp);
			}

// utils

		private:
			node_ptr	_max(node_ptr node) {
				while (node->right != this->_nil)
					node = node->right;
				return (node);
			}

			node_ptr	_min(node_ptr node) {
				while (node->left != this->_nil)
					node = node->left;
				return (node);
			}

			node_ptr	_next(node_ptr node) {
				if (node->right != this->_nil)
					return (this->_min(node->right));
				node_ptr parent = node->parent;
				while (parent != this->_nil && node == parent->right) {
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}

			node_ptr	_prev(node_ptr node) {
				if (node->left != this->_nil)
					return (this->_max(node->left));
				node_ptr parent = node->parent;
				while (parent != this->_nil && node == parent->left) {
					node = parent;
					parent = parent->parent;
				}
				return (parent);
			}

	};

////////////////////////////////////////////////////////////////////////////////
// red-black tree structure
////////////////////////////////////////////////////////////////////////////////

	template <typename T, typename Allocator = std::allocator<rb_node<T> >, typename Compare = std::less<T> >
	class rb_tree {

		public:
			typedef rb_node<T> node;
			typedef rb_node<T> *node_ptr;
			typedef Allocator allocator_type;
			typedef T value_type;
			typedef Compare compare_type;
			typedef rb_treeIterator<T> iterator;
			typedef rb_treeIterator<T const> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		private:
			node_ptr root;
			node_ptr _nil;
			allocator_type _alloc;
			compare_type _compare;

		public:
			rb_tree(allocator_type const &alloc = allocator_type(), compare_type const &compare = compare_type())
			: _alloc(alloc), _compare(compare) {
				this->_nil = this->_alloc.allocate(1);
				this->_alloc.construct(this->_nil, node(BLACK, this->_nil, this->_nil, this->_nil));
				this->root = this->_nil;
			}

			~rb_tree(void) {
				this->_clean(this->root);
				delete_node(this->_nil);
			}

			void	_clean(node_ptr node) {
				if (node == this->_nil)
					return ;
				this->_clean(node->left);
				this->_clean(node->right);
				delete_node(node);
			}

			iterator	begin(void) {
				return (iterator(this->min(), this->root, this->_nil));
			}

			const_iterator	begin(void) const {
				return (iterator(this->min(), this->root, this->_nil));
			}

			iterator	end(void) {
				return (iterator(this->_nil, this->root, this->_nil));
			}

			const_iterator	end(void) const {
				return (iterator(this->_nil, this->root, this->_nil));
			}

			reverse_iterator	rbegin(void) {
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator	rbegin(void) const {
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator	rend(void) {
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator	rend(void) const {
				return (const_reverse_iterator(this->begin()));
			}

			node_ptr	search(value_type value) {
				node_ptr current = this->root;
				while (current != this->_nil) {
					if (this->_compare(value, current->data))
						current = current->left;
					else if (this->_compare(current->data, this->value))
						current = current->right;
					else
						break ;
				}
				return (current);
			}

			node_ptr	max(void) {
				return (this->_max(this->root));
			}

			node_ptr	_max(node_ptr current) {
				while (current->right != this->_nil)
					current = current->right;
				return (current);
			}

			node_ptr	min(void) {
				return (this->_min(this->root));
			}

			node_ptr	_min(node_ptr current) {
				while (current->left != this->_nil)
					current = current->left;
				return (current);
			}

			void	insert(value_type val) {
				node_ptr new_node = this->_new_node(val);
				node_ptr prev = this->_nil;
				node_ptr current = this->root;
				while (current != this->_nil) {
					prev = current;
					if (this->_compare(new_node->data, current->data))
						current = current->left;
					else
						current = current->right;
				}
				new_node->parent = prev;
				if (prev == this->_nil)
					this->root = new_node;
				else if (this->_compare(new_node->data, prev->data))
					prev->left = new_node;
				else
					prev->right = new_node;
				this->_fix_insert(new_node);
			}

			void erase(value_type val) {
				node_ptr node;
				node = this->search(val);
				if (node != this->_nil)
					this->erase(node);
			}

			void	erase(node_ptr node) {
				node_ptr tmp = node;
				node_ptr x;
				t_color tmp_color = tmp->color;
				if (node->left == this->_nil) {
					x = node->right;
					_transplant(node, node->right);
				} else if (node->right == this->_nil) {
					x = node->left;
					_transplant(node, node->left);
				} else {
					tmp = _min(node->right);
					tmp_color = tmp->color;
					x = tmp->right;
					if (tmp->parent == node)
						x->parent = tmp;
					else {
						_transplant(tmp, tmp->right);
						tmp->right = node->right;
						tmp->right->parent = tmp;
					}
					_transplant(node, tmp);
					tmp->left = node->left;
					tmp->left->parent = tmp;
				}
				this->delete_node(node);
				if (tmp_color == BLACK)
					this->_fix_erase(x);
			}

// tree_rotations

			// _right_rotate(y)                      //
			//          y                x           //
			//         / \              / \          //
			//        x   c     =>     a   y         //
			//       / \                  / \        //
			//      a   b                b   c       //

			void	_right_rotate(node_ptr node) {
				node_ptr tmp = node->left;
				node->left = tmp->right;
				if (tmp->right != this->_nil)
					tmp->right->parent = node;
				tmp->parent = node->parent;
				if (node->parent == this->_nil)
					this->root = tmp;
				else if (node == node->parent->right)
					node->parent->right = tmp;
				else
					node->parent->left = tmp;
				tmp->right = node;
				node->parent = tmp;
			}

			// _left_rotate(x)                       //
			//         x                 y           //
			//        / \               / \          //
			//       a   y      =>     x   c         //
			//          / \           / \            //
			//         b   c         a   b           //

			void	_left_rotate(node_ptr node) {
				node_ptr tmp = node->right;
				node->right = tmp->left;
				if (tmp->left != this->_nil)
					tmp->left->parent = node;
				tmp->parent = node->parent;
				if (node->parent == this->_nil)
					this->root = tmp;
				else if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
				tmp->left = node;
				node->parent = tmp;
			}

			// new_node

			void	_fix_insert(node_ptr node) {
				node_ptr uncle;
				while (node->parent->color == RED) {
					if (node->parent == node->parent->parent->left) {
						uncle = node->parent->parent->right;
						if (uncle->color == RED) {
							node->parent->color = BLACK;
							uncle->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						} else {
							if (node == node->parent->right) {
								node = node->parent;
								this->_left_rotate(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							this->_right_rotate(node->parent->parent);
						}
					} else {
						uncle = node->parent->parent->left;
						if (uncle->color == RED) {
							node->parent->color = BLACK;
							uncle->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						} else {
							if (node == node->parent->left) {
								node = node->parent;
								this->_right_rotate(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							this->_left_rotate(node->parent->parent);
						}
					}
				}
				this->root->color = BLACK;
			}

			void	_transplant(node_ptr to_cut, node_ptr to_connect) {
				if (to_cut->parent == this->_nil)
					this->root = to_connect;
				else if (to_cut == to_cut->parent->left)
					to_cut->parent->left = to_connect;
				else
					to_cut->parent->right = to_connect;
				to_connect->parent = to_cut->parent;
			}

			void	_fix_erase(node_ptr x) {
				node_ptr w;
				while (x != this->root && x->color == BLACK) {
					if (x == x->parent->left) {
						w = x->parent->right;
						if (w->color == RED) {
							w->color = BLACK;
							x->parent->color = RED;
							this->_left_rotate(x->parent);
							w = x->parent->right;
						}
						if (w->left->color == BLACK && w->right->color == BLACK) {
							w->color = RED;
							x = x->parent;
						} else {
							if (w->right->color == BLACK) {
								w->left->color = BLACK;
								w->color = RED;
								this->_right_rotate(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right->color = BLACK;
							this->_left_rotate(x->parent);
							x = this->root;
						}
					} else {
						w = x->parent->left;
						if (w->color == RED) {
							w->color = BLACK;
							x->parent->color = RED;
							this->_right_rotate(x->parent);
							w = x->parent->left;
						}
						if (w->right->color == BLACK && w->left->color == BLACK) {
							w->color = RED;
							x = x->parent;
						} else {
							if (w->left->color == BLACK) {
								w->right->color = BLACK;
								w->color = RED;
								this->_left_rotate(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left->color = BLACK;
							this->_right_rotate(x->parent);
							x = this->root;
						}
					}
				}
				x->color = BLACK;
			}

			node_ptr	_new_node(value_type val = value_type()) {
				node_ptr new_node = this->_alloc.allocate(1);
				this->_alloc.construct(new_node, node());
				new_node->color = RED;
				new_node->data = val;
				new_node->parent = this->_nil;
				new_node->right = this->_nil;
				new_node->left = this->_nil;
				return (new_node);
			}

			void	delete_node(node_ptr node) {
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
			}

			// debug utils

			void	print(void) {
				std::stringstream buffer;
				this->_print(this->root, buffer, true, "");
				std::cout << buffer.str();
			}

		private:
			void	_print(rb_node<T> *node, std::stringstream &buffer,
			bool is_tail, std::string prefix) {
				if (node->right != this->_nil)
					this->_print(node->right, buffer, false,
						std::string(prefix).append(is_tail != 0 ? "│   " : "    "));
				buffer << prefix << (is_tail != 0 ? "└── " : "┌── ");
				if (node->color == RED)
					buffer << "\033[31m";
				buffer << node->data << "\033[0m" << std::endl;
				if (node->left != this->_nil)
					this->_print(node->left, buffer, true,
							std::string(prefix).append(is_tail != 0 ? "    " : "│   "));
			}
	};
}

#endif
