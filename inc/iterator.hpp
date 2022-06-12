/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 22:48:38 by user42            #+#    #+#             */
/*   Updated: 2022/01/11 14:16:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <iterator>

namespace ft
{
	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

/*
* Iterator Base Class
* */
	template <class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

/*
* Random Access Iterator
* */

	template <class T>
	class normal_iterator
	: public std::iterator<std::random_access_iterator_tag, T>
	{

	public:

		typedef typename std::iterator<std::random_access_iterator_tag, T>	IteratorBase;
		
		typedef typename IteratorBase::difference_type		difference_type;
		typedef typename IteratorBase::pointer				pointer;
		typedef typename IteratorBase::reference			reference;
		typedef typename IteratorBase::value_type			value_type;
		typedef typename IteratorBase::iterator_category	iterator_category;

		normal_iterator(): current() {}
		normal_iterator(pointer p): current(p) {}
		normal_iterator(const normal_iterator & it) { *this = it; }
		~normal_iterator() {}

		normal_iterator & operator=(const normal_iterator & rhs) { this->current = rhs.current ; return (*this); }

		reference operator*() const { return (*this->current); }
		pointer operator->() const { return (this->current); }
		
		
		normal_iterator operator+(difference_type n) const { return (normal_iterator(current + n)); }
		normal_iterator operator-(difference_type n) const { return (normal_iterator(current - n)); }
		difference_type operator-(const normal_iterator & rhs) const { return (this->current - rhs.current); }

		normal_iterator & operator++() { ++this->current; return (*this); }
		normal_iterator operator++(int) { return (normal_iterator(this->current++)); }

		normal_iterator & operator--() { --this->current; return (*this); }
		normal_iterator operator--(int) { return (normal_iterator(this->current--)); }

		normal_iterator & operator+=(difference_type n) { this->current += n; return (*this); }
		normal_iterator & operator-=(difference_type n) { this->current -= n; return (*this); }

		reference operator[](int n) { return (this->current[n]); }
		
		operator normal_iterator<const T>() const { return (normal_iterator<const T>(this->current)); };
		
	protected:
		pointer current;

	private:
		template<class Tp>
		friend bool operator!=(const normal_iterator< Tp> & lhs, const normal_iterator< Tp> & rhs);
		template<class Tp>
		friend bool operator==(const normal_iterator< Tp> & lhs, const normal_iterator< Tp> & rhs);
		template<class Tp>
		friend bool operator>(const normal_iterator< Tp> & lhs, const normal_iterator< Tp> & rhs);
		template<class Tp>
		friend bool operator>=(const normal_iterator< Tp> & lhs, const normal_iterator< Tp> & rhs);
		template<class Tp>
		friend bool operator<=(const normal_iterator< Tp> & lhs, const normal_iterator< Tp> & rhs);
		template<class Tp>
		friend bool operator<(const normal_iterator< Tp> & lhs, const normal_iterator< Tp> & rhs);

		template<class TL, class TR>
		friend bool operator!=(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs);
		template<class TL, class TR>
		friend bool operator==(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs);
		template<class TL, class TR>
		friend bool operator>(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs);
		template<class TL, class TR>
		friend bool operator>=(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs);
		template<class TL, class TR>
		friend bool operator<=(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs);
		template<class TL, class TR>
		friend bool operator<(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs);
	};

	template<class T>
	bool operator!=(const normal_iterator< T> & lhs, const normal_iterator< T> & rhs) { return (lhs.current != rhs.current); }
	template<class T>
	bool operator==(const normal_iterator< T> & lhs, const normal_iterator< T> & rhs) { return (lhs.current == rhs.current); }
	template<class T>
	bool operator>(const normal_iterator< T> & lhs, const normal_iterator< T> & rhs) { return (lhs.current > rhs.current); }
	template<class T>
	bool operator>=(const normal_iterator< T> & lhs, const normal_iterator< T> & rhs) { return (lhs.current >= rhs.current); }
	template<class T>
	bool operator<=(const normal_iterator< T> & lhs, const normal_iterator< T> & rhs) { return (lhs.current <= rhs.current); }
	template<class T>
	bool operator<(const normal_iterator< T> & lhs, const normal_iterator< T> & rhs) { return (lhs.current < rhs.current); }

	template<class TL, class TR>
	bool operator!=(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs) { return (lhs.current != rhs.current); }
	template<class TL, class TR>
	bool operator==(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs) { return (lhs.current == rhs.current); }
	template<class TL, class TR>
	bool operator>(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs) { return (lhs.current > rhs.current); }
	template<class TL, class TR>
	bool operator>=(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs) { return (lhs.current >= rhs.current); }
	template<class TL, class TR>
	bool operator<=(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs) { return (lhs.current <= rhs.current); }
	template<class TL, class TR>
	bool operator<(const normal_iterator< TL> & lhs, const normal_iterator< TR> & rhs) { return (lhs.current < rhs.current); }

	template<class T>
	normal_iterator<T> operator+(typename normal_iterator<T>::difference_type n, const normal_iterator<T> & it) { return (it + n); }
	template<class TL, class TR>
	typename normal_iterator<TL>::difference_type operator-(const normal_iterator<TL> & lhs, const normal_iterator<TR> & rhs) { return (&*lhs - &*rhs); }

/*
* Reverse Iterator
* */

	template <class Iterator>
	class reverse_iterator: public std::iterator<typename iterator_traits<Iterator>::iterator_category, typename iterator_traits<Iterator>::value_type>
	{
	protected:
		Iterator current;
		typedef	iterator_traits<Iterator>					__traits_type;

	public:
		typedef Iterator									iterator_type;
		typedef typename __traits_type::value_type			value_type;
		typedef typename __traits_type::difference_type		difference_type;
		typedef typename __traits_type::pointer				pointer;
		typedef typename __traits_type::reference			reference;
		typedef typename __traits_type::iterator_category	iterator_category;

		reverse_iterator(): current() {}
		reverse_iterator(iterator_type it): current(it) {}
		reverse_iterator(const reverse_iterator& rev_it): current(rev_it.current) {}
		template<class Iter>
		reverse_iterator(const reverse_iterator<Iter> & rev_it): current(rev_it.base()) {}
		~reverse_iterator() {}

		iterator_type base(void) const { return (current); }
		
		reference operator*() const
		{
			Iterator tmp = current;
			return (*--tmp);	
		}
		pointer operator->() const { return (&(operator*())); }

		reverse_iterator & operator++() { --current; return (*this); }
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--current;
			return (tmp);
		}

		reverse_iterator & operator--() { ++current; return (*this); }
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++current;
			return (tmp);
		}

		reverse_iterator operator+(difference_type n) const { return (reverse_iterator(current - n)); }
		reverse_iterator & operator+=(difference_type n)
		{
			current -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const { return (reverse_iterator(current + n)); }
		reverse_iterator & operator-=(difference_type n)
		{
			current += n;
			return (*this);
		}

		reference operator[](difference_type n) const { return (*(*this + n)); }
	};

	// comparison of reverse_iterator to reverse_iterator
	template<class Iterator>
	bool operator==(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) { return (lhs.base() == rhs.base()); }
	template<class Iterator>
	bool operator!=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) { return (lhs.base() != rhs.base()); }
	template<class Iterator>
	bool operator<(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) { return (lhs.base() > rhs.base()); }
	template<class Iterator>
	bool operator<=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) { return (lhs.base() >= rhs.base()); }
	template<class Iterator>
	bool operator>(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) { return (lhs.base() < rhs.base()); }
	template<class Iterator>
	bool operator>=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) { return (lhs.base() <= rhs.base()); }

	// comparison of reverse_iterator to const reverse_iterator
	template<class IteratorL, class IteratorR>
	bool operator==(const reverse_iterator<IteratorL> & lhs, const reverse_iterator<IteratorR> & rhs) { return (lhs.base() == rhs.base()); }
	template<class IteratorL, class IteratorR>
	bool operator!=(const reverse_iterator<IteratorL> & lhs, const reverse_iterator<IteratorR> & rhs) { return (lhs.base() != rhs.base()); }
	template<class IteratorL, class IteratorR>
	bool operator<(const reverse_iterator<IteratorL> & lhs, const reverse_iterator<IteratorR> & rhs) { return (lhs.base() > rhs.base()); }
	template<class IteratorL, class IteratorR>
	bool operator<=(const reverse_iterator<IteratorL> & lhs, const reverse_iterator<IteratorR> & rhs) { return (lhs.base() >= rhs.base()); }
	template<class IteratorL, class IteratorR>
	bool operator>(const reverse_iterator<IteratorL> & lhs, const reverse_iterator<IteratorR> & rhs) { return (lhs.base() < rhs.base()); }
	template<class IteratorL, class IteratorR>
	bool operator>=(const reverse_iterator<IteratorL> & lhs, const reverse_iterator<IteratorR> & rhs) { return (lhs.base() <= rhs.base()); }

	template<class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> & rev_it) { return (rev_it + n); }
	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) { return (rhs.base() - lhs.base()); }
	template<class IteratorL, class IteratorR>
	typename reverse_iterator<IteratorL>::difference_type operator-(const reverse_iterator<IteratorL> & lhs, const reverse_iterator<IteratorR> & rhs) { return (rhs.base() - lhs.base()); }

/*
* Map Iterator
* */

	template <class T, class contained_type>
	struct bst_iterator
	: public std::iterator<std::bidirectional_iterator_tag, T>
	{

	public:

		typedef typename std::iterator<std::bidirectional_iterator_tag, T>	IteratorBase;
		
		typedef typename IteratorBase::difference_type		difference_type;
		typedef typename IteratorBase::value_type			base_value_type;
		typedef typename IteratorBase::pointer				base_pointer;
		typedef typename IteratorBase::reference			base_reference;
		typedef typename IteratorBase::iterator_category	iterator_category;

		typedef contained_type								value_type;
		typedef value_type*									pointer;
		typedef value_type&									reference;

	public:
		bst_iterator(): current() {}
		bst_iterator(base_pointer p): current(p) {}
		bst_iterator(const bst_iterator & it): current(it.current) {}
		~bst_iterator() {}

		bst_iterator & operator=(const bst_iterator & rhs) { this->current = rhs.current ; return (*this); }

		reference	operator*() const { return (this->current->content); }
		pointer		operator->() const { return (&(operator*())); }

		bst_iterator & operator++()
		{
			this->current = this->current->next();
			return (*this);
		}
		bst_iterator operator++(int)
		{
			bst_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		bst_iterator & operator--()
		{
			this->current = this->current->previous();
			return (*this);
		}
		bst_iterator operator--(int)
		{
			bst_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		operator bst_iterator<const T, const contained_type>() const { return (bst_iterator<const T, const contained_type>(this->current)); };

		base_pointer current;
	};

	template<class N, class Np>
	bool operator==(const bst_iterator<N, Np> & lhs, const bst_iterator<N, Np> & rhs) { return (lhs.current == rhs.current); }
	template<class N, class Np>
	bool operator!=(const bst_iterator<N, Np> & lhs, const bst_iterator<N, Np> & rhs) { return (lhs.current != rhs.current); }

	template<class NR, class TR, class NL, class TL>
	bool operator==(const bst_iterator<NR, TL> & lhs, const bst_iterator<NL, TR> & rhs) { return (lhs.current == rhs.current); }
	template<class NR, class TR, class NL, class TL>
	bool operator!=(const bst_iterator<NR, TL> & lhs, const bst_iterator<NL, TR> & rhs) { return (lhs.current != rhs.current); }
}
#endif // ITERATOR_HPP