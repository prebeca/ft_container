/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:45:12 by user42            #+#    #+#             */
/*   Updated: 2022/01/11 15:11:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	template<typename _Tp, _Tp __v>
	struct integral_constant
	{
		static const _Tp value = __v;
		typedef _Tp							value_type;
		typedef integral_constant<_Tp, __v>	type;
		operator value_type() const { return value; }
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template<bool Cond, class T = void>
	struct enable_if
	{};

	template<class T>
	struct enable_if<true, T>
	{ typedef T type; };

// is_integral

	template<typename>
	struct __is_integral_helper
	: public false_type
	{};

	template<>
	struct __is_integral_helper<bool>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<char>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<signed char>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<unsigned char>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<short>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<unsigned short>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<int>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<unsigned int>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<long>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<unsigned long>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<long long>
	: public true_type
	{};

	template<>
	struct __is_integral_helper<unsigned long long>
	: public true_type
	{};

	template<typename _Tp>
	struct is_integral
	: public __is_integral_helper<_Tp>::type
	{};

// 

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2,
									Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

}

#endif // UTILS_HPP