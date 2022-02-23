/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:00:00 by rotrojan          #+#    #+#             */
/*   Updated: 2022/02/23 21:46:04 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP
#include <sstream>
#include <iostream>

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

		rb_node(
		t_color color = RED, rb_node *parent = NULL,
		rb_node *left = NULL, rb_node *right = NULL):
		color(color), parent(parent), left(left), right(right) {
		}

		rb_node(rb_node const &node) {
			*this = node;
		}

		~rb_node(void) {
		}

		rb_node	&operator=(rb_node const &rhs) {
			if (this != rhs) {
				this->color = rhs.color;
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->right = rhs.right;
			}
			return (this);
		}

	};

	/*
	** red-black tree structure
	*/

	template <typename T>
	class rb_tree {
		public:

			typedef T *pointer;

			rb_node<T> *root;
			rb_node<T> *nil;

			tree(void): nil() {
				root->color = RED;
				root->parent = this->nil;
				root->left = this->nil;
				root->right = this->nil;
			}

			void	insert(T val) {
				// rb_node *current = this->root;
				// while (current != )
				root->data = val;
			}

			void	print(void)
			{
				std::stringstream buffer;

				this->_print(this->root(), buffer, true, "");
				std::cout << buffer.str();
			}

			void	_print(pointer node, std::stringstream &buffer, bool isTail, std::string prefix)
			{
				if (node->right != this->sentry()) // sentry = leaf NULL
					this->_print(node->right, buffer, false, std::string(prefix).append(isTail ? "│   " : "    "));
				buffer << prefix << (isTail ? "└── " : "┌── ");
				if (node->color == RED)
					buffer << "\033[31m";
				buffer << node->data << "\033[0m" << std::endl;
				if (node->left != this->sentry())
					this->_print(node->left, buffer, true, std::string(prefix).append(isTail ? "    " : "│   "));
			}
	};
}

#endif
