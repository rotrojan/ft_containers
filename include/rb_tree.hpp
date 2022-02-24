/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:00:00 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/24 22:49:37 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP
# include <sstream>
# include <iostream>
# include <string>

namespace ft {

	typedef enum e_color {
		RED = false,
		BLACK = true
	} t_color;

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

	/*
	** red-black tree structure
	*/

	template <typename T, typename Allocator = std::allocator<rb_node<T> > >
	class rb_tree {

		public:
			typedef rb_node<T> node;
			typedef rb_node<T> *node_ptr;
			typedef Allocator allocator_type;
			typedef T value_type;

		// private:
		public:
			node_ptr root;
			node_ptr nil;
			allocator_type _alloc;

		public:
			rb_tree(allocator_type const &alloc = allocator_type())
			: _alloc(alloc) {
				this->nil = this->_alloc.allocate(1);
				this->_alloc.construct(this->nil, node(BLACK, this->nil, this->nil, this->nil));
				this->root = this->nil;
			}

			~rb_tree(void) {
				while (this->root != this->nil) {
					node_ptr root = this->root;
					this->erase(root);
				}
				delete_node(this->nil);
			}

			void	insert(value_type val) {
				node_ptr new_node = _new_node(val);
				node_ptr prev = this->nil;
				node_ptr current = this->root;
				while (current != this->nil) {
					prev = current;
					if (new_node->data < current->data)
						current = current->left;
					else
						current = current->right;
				}
				new_node->parent = prev;
				if (prev == this->nil)
					this->root = new_node;
				else if (new_node->data < prev->data)
					prev->left = new_node;
				else
					prev->right = new_node;
				this->_fix_insert(new_node);
			}

			void	transplant(node_ptr to_cut, node_ptr to_connect) {
				if (to_cut->parent == this->nil)
					this->root = to_connect;
				else if (to_cut == to_cut->parent->left)
					to_cut->parent->left = to_connect;
				else
					to_cut->parent->right = to_connect;
				to_connect->parent = to_cut->parent;
			}

			void erase(value_type val) {
				node_ptr node;
				node = this->search(val);
				if (node != this->nil)
					this->erase(node);
			}

			void	erase(node_ptr node) {
				node_ptr tmp = node;
				node_ptr x;
				t_color tmp_color = tmp->color;
				if (node->left == this->nil) {
					x = node->right;
					transplant(node, node->right);
				} else if (node->right == this->nil) {
					x = node->left;
					transplant(node, node->left);
				} else {
					tmp = _min(node->right);
					tmp_color = tmp->color;
					x = tmp->right;
					if (tmp->parent == node)
						x->parent = tmp;
					else {
						transplant(tmp, tmp->right);
						tmp->right = node->right;
						tmp->right->parent = tmp;
					}
					transplant(node, tmp);
					tmp->left = node->left;
					tmp->left->parent = tmp;
				}
				this->delete_node(node);
				if (tmp_color == BLACK)
					this->_fix_erase(x);
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

			node_ptr	prev(node_ptr node) {
				if (node->left != this->nil)
					return (this->_max(node->right));
				node_ptr current = node->parent;
				while (current != this->nil && node != current->left) {
					node = current;
					current = current->parent;
				}
				return (current);
			}

			node_ptr	next(node_ptr node) {
				if (node->right != this->nil)
					return (this->_min(node->right));
				node_ptr current = node->parent;
				while (current != this->nil && node != current->right) {
					node = current;
					current = current->parent;
				}
				return (current);
			}

			node_ptr	search(value_type value) {
				node_ptr current = this->root;
				while (current != this->nil) {
					if (value < current->data)
						current = current->left;
					else if (value > current->data)
						current = current->right;
					else
						break ;
				}
				return (current);
			}

			value_type	max(void) {
				return (this->_max(this->root)->data);
			}

			node_ptr	_max(node_ptr current) {
				while (current->left != this->nil)
					current = current->left;
				return (current);
			}

			value_type	min(void) {
				return (this->_min(this->root)->data);
			}

			node_ptr	_min(node_ptr current) {
				while (current->left != this->nil)
					current = current->left;
				return (current);
			}

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
				if (tmp->right != this->nil)
					tmp->right->parent = node;
				tmp->parent = node->parent;
				if (node->parent == this->nil)
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
				if (tmp->left != this->nil)
					tmp->left->parent = node;
				tmp->parent = node->parent;
				if (node->parent == this->nil)
					this->root = tmp;
				else if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
				tmp->left = node;
				node->parent = tmp;
			}

			// new_node

			node_ptr	_new_node(value_type val = value_type()) {
				node_ptr new_node = this->_alloc.allocate(1);
				this->_alloc.construct(new_node, node());
				new_node->data = val;
				new_node->right = this->nil;
				new_node->left = this->nil;
				return (new_node);
			}

			void	delete_node(node_ptr node) {
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
				// (void)node;
			}

			// debug utils

			void	print(void) {
				std::stringstream buffer;
				this->_print(this->root, buffer, true, "");
				std::cout << buffer.str();
			}

			void	_print(rb_node<T> *node, std::stringstream &buffer,
			bool is_tail, std::string prefix) {
				if (node->right != this->nil)
					this->_print(node->right, buffer, false,
						std::string(prefix).append(is_tail != 0 ? "│   " : "    "));
				buffer << prefix << (is_tail != 0 ? "└── " : "┌── ");
				if (node->color == RED)
					buffer << "\033[31m";
				buffer << node->data << "\033[0m" << std::endl;
				if (node->left != this->nil)
					this->_print(node->left, buffer, true,
							std::string(prefix).append(is_tail != 0 ? "    " : "│   "));
			}
	};
}

#endif
