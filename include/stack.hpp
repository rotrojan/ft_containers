/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:46:00 by rotrojan          #+#    #+#             */
/*   Updated: 2022/03/02 17:30:59 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "vector.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
// stack container
////////////////////////////////////////////////////////////////////////////////
	template <typename T, typename Container = ft::vector<T> >
	class stack {

		public:
			typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
			typedef Container container_type;

			template <typename _T, typename _Container>
			friend bool	ft::operator==(stack<_T, _Container> const &lhs,
			stack<_T, _Container> const &rhs);

			template <typename _T, typename _Container>
			friend bool	ft::operator<(stack<_T, _Container> const &lhs,
			stack<_T, _Container> const &rhs);

		protected:
			Container c;

		public:
			explicit stack(Container const &c = Container()): c(c) {
			}

			bool	empty(void) const {
				return (c.empty());
			}

			size_type	size(void) const {
				return (c.size());
			}

			value_type	&top(void) {
				return (c.back());
			}

			value_type const	&top(void) const {
				return (c.back());
			}

			void	push(value_type const &val) {
				c.push_back(val);
			}

			void	pop(void) {
				c.pop_back();
			}
	};

	template <typename T, typename Container>
	bool	operator==(stack<T, Container> const &lhs,
	stack<T, Container> const &rhs) {
		return (lhs.c == rhs.c);
	}

	template <typename T, typename Container>
	bool	operator<(stack<T, Container>const &lhs,
	stack<T, Container> const &rhs) {
		return (lhs.c < rhs.c);
	}

	template <typename T, typename Container>
	bool	operator!=(stack<T, Container> const &lhs,
	stack<T, Container> const &rhs) {
		return (!(lhs == rhs));
	}

	template <typename T, typename Container>
	bool	operator>(stack<T, Container> const & lhs,
	stack<T, Container> const& rhs) {
		return (rhs < lhs);
	}

	template <typename T, typename Container>
	bool	operator>=(stack<T, Container> const & lhs,
	stack<T, Container> const & rhs) {
		return (rhs < lhs || lhs == rhs);
	}

	template <typename T, typename Container>
	bool	operator<=(stack<T, Container> const & lhs,
	stack<T, Container> const & rhs) {
		return (lhs < rhs || lhs == rhs);
	}

};

#endif
