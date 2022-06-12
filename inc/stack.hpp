/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:58:26 by user42            #+#    #+#             */
/*   Updated: 2021/12/24 12:06:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template<class T, class Container = vector<T> >
	class stack
	{

	public:
		typedef T									value_type;
		typedef Container							container_type;
		typedef typename container_type::size_type	size_type;

		explicit stack(const container_type & ctnr = container_type()): c(ctnr) {}
		~stack() {}

		bool				empty(void) const { return (c.empty()); }
		size_type			size(void) const { return (c.size()); }

		value_type &		top(void) { return (c.back()); };
		const value_type &	top(void) const { return (c.back()); }

		void	push(const value_type& val) { c.push_back(val); }
		void	pop(void) { c.pop_back(); }

	protected:
	
		container_type c;

		template <class TN, class ContainerN>
		friend bool operator== (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);
		template <class TN, class ContainerN>
		friend bool operator!= (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);
		template <class TN, class ContainerN>
		friend bool operator<  (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);
		template <class TN, class ContainerN>
		friend bool operator<= (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);
		template <class TN, class ContainerN>
		friend bool operator>  (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);
		template <class TN, class ContainerN>
		friend bool operator>= (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);
	};
	
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs.c == rhs.c); }

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs.c != rhs.c); }

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs.c < rhs.c); }

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs.c <= rhs.c); }

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs.c > rhs.c); }

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs.c >= rhs.c); }
}


#endif // STACK_HPP