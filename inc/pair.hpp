/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:24:17 by user42            #+#    #+#             */
/*   Updated: 2022/01/10 16:51:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	/**
	 * @brief  This class couples together a pair of values, which may be of different types (T1 and T2).
	 * The individual values can be accessed through its public members first and second.
	 * @note
	 * @retval None
	 * */
	template<class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair() {}
		template<class U, class V>
		pair(const pair<U,V>& p): first(p.first), second(p.second) {}
		pair(const first_type& a, const second_type& b): first(a), second(b) {}
		~pair() {}
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	/**
	 * @brief  Constructs a pair object with its first element set to x and its second element set to y.
	 * @note   
	 * @param  x,y  Values for the members first and second, respectively, of the pair object being constructed.
	 * @retval A pair object whose elements first and second are set to x and y respectivelly.
	 */
	template <class T1,class T2>
	pair<T1,T2> make_pair(T1 x, T2 y)
	{ return ( pair<T1,T2>(x,y) ); }

}

#endif // PAIR_HPP