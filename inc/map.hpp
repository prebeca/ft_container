/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:48:37 by user42            #+#    #+#             */
/*   Updated: 2022/01/10 21:41:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <functional>

# include "iterator.hpp"
# include "pair.hpp"
# include "utils.hpp"
# include "stack.hpp"
# include "BinarySearchTree.hpp"

namespace ft
{
	/**
	 * @brief  Maps are associative containers that store elements formed
	 * by a combination of a key value and a mapped value, following a specific order.
	 * @note   
	 */
  template <typename Key, typename Tp, typename Compare = std::less<Key>,
            typename Alloc = std::allocator<ft::pair<const Key, Tp> > >
    class map
    {
	public:
		typedef Key												key_type;
		typedef Tp												mapped_type;
		typedef ft::pair<const Key, Tp>							value_type;
		typedef Compare											key_compare;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		class	value_compare;
	private:
		typedef	ft::BinarySearchTree<value_type, value_compare, allocator_type>	container_type;
	public:
		typedef typename container_type::iterator				iterator;
		typedef typename container_type::const_iterator			const_iterator;
		typedef typename container_type::reverse_iterator		reverse_iterator;
		typedef typename container_type::const_reverse_iterator	const_reverse_iterator;
		typedef ft::iterator_traits<iterator>					difference_type;
		typedef size_t											size_type;

		class value_compare
		: public std::binary_function<value_type, value_type, bool>
		{
		public:
			Compare comp;
			value_compare (Compare c) : comp(c) {}
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

	public:

	 /**
	  * @brief  Constructs an empty container, with no elements.
	  * @note   
	  * @param  comp: Binary predicate that, taking two element keys as argument, returns true if the first argument goes before the second argument in the strict weak ordering it defines, and false otherwise.
This shall be a function pointer or a function object.
Member type key_compare is the internal comparison object type used by the container, defined in map as an alias of its third template parameter (Compare).
If key_compare uses the default less (which has no state), this parameter is not relevant.
	  * @retval None
	  */
		explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
		: value_comparator(comp), key_comparator(comp), value_allocator(alloc), bst(value_comparator, value_type(key_type(), mapped_type()))
		{}

	 /**
	  * @brief  Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range.
	  * @note   
	  * @param  first,last: Input iterators to the initial and final positions in a range. The range used is [first,last), which includes all the elements between first and last, including the element pointed by first but not the element pointed by last.
The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed (in map, value_type is an alias of pair<const key_type, mapped_type>) 
	  * @param  comp: Binary predicate that, taking two element keys as argument, returns true if the first argument goes before the second argument in the strict weak ordering it defines, and false otherwise.
This shall be a function pointer or a function object.
Member type key_compare is the internal comparison object type used by the container, defined in map as an alias of its third template parameter (Compare).
If key_compare uses the default less (which has no state), this parameter is not relevant.
	  * @retval None
	  */
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		: value_comparator(comp), key_comparator(comp), value_allocator(alloc), bst(first, last, value_comparator, value_type(key_type(), mapped_type()))
		{}

	 /**
	  * @brief  Constructs a container with a copy of each of the elements in x.
	  * @note   
	  * @param  x: Another map object of the same type (with the same class template arguments Key, T, Compare and Alloc), whose contents are either copied or acquired.
	  * @retval 
	  */
		map (const map& x)
		: value_comparator(x.key_comparator), key_comparator(x.key_comparator), bst(x.bst)
		{}
	 
	 /**
	  * @brief  This destroys all container elements, and deallocates all the storage capacity allocated by the map container using its allocator.
	  * @note   
	  * @retval None
	  */
		~map ()
		{ clear(); }
	 
	 /**
	  * @brief  Assigns new contents to the container, replacing its current content.
	  * @note   
	  * @param  x: A map object of the same type (i.e., with the same template parameters, key, T, Compare and Alloc).
	  * @retval *this
	  */
		map& operator= (const map& x)
		{
			bst = x.bst;
			return (*this);
		}

	 /**
	  * @brief  Returns an iterator refering to the first element in the map container.
	  * @note   
	  * @retval An iterator to the first element in the container.
	  */
	 	iterator begin() { return (bst.begin()); }
	 	const_iterator begin() const { return (bst.begin()); }

	 	iterator end() { return (bst.end()); }
	 	const_iterator end() const { return (bst.end()); }

	 	reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
	 	const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }

	 	reverse_iterator rend() { return (reverse_iterator(this->begin())); }
	 	const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); }

	 /**
	  * @brief  Returns whether the map container is empty (i.e. whether its size is 0).
	  * @note   
	  * @retval true if the container size is 0, false otherwise.
	  */
		bool empty() const
		{ return (bst.empty()); }

	 /**
	  * @brief  Returns the number of elements in the map container.
	  * @note   
	  * @retval The number of elements in the container.
	  */
		size_type size() const
		{ return (bst.size()); }
		
	 /**
	  * @brief  Returns the maximum number of elements that the map container can hold.
	  * @note   
	  * @retval The maximum number of elements a map container can hold as content.
	  */
		size_type max_size() const
		{ return(bst.max_size()); }

	 /**
	  * @brief  If k matches the key of an element in the container, the function returns a reference to its mapped value.
If k does not match the key of any element in the container, the function inserts a new element with that key and returns a reference to its mapped value. Notice that this always increases the container size by one, even if no mapped value is assigned to the element (the element is constructed using its default constructor).
	  * @note   
	  * @param  k: Key value of the element whose mapped value is accessed.
	  * @retval A reference to the mapped value of the element with a key value equivalent to k.
	  */
		mapped_type& operator[] (const key_type& k)
		{ return ((*((bst.insert(ft::make_pair(k, mapped_type()))).first)).second); }

	 /**
	  * @brief  Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
	  * @note   
	  * @param  val: Value to be copied to (or moved as) the inserted element.
	  * @retval Return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map. The pair::second element in the pair is set to true if a new element was inserted or false if an equivalent key already existed.
	  */
		pair<iterator,bool> insert (const_reference val)
		{ return(bst.insert(val)); }

	 /**
	  * @brief  Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
	  * @note   
	  * @param  position: Hint for the position where the element can be inserted.
	  * @param  val: Value to be copied to (or moved as) the inserted element.
	  * @retval Return an iterator pointing to either the newly inserted element or to the element that already had an equivalent key in the map.
	  */
		iterator insert (iterator position, const_reference val)
		{
			(void) position;
			return (bst.insert(val).first);
		}

	 /**
	  * @brief  Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
	  * @note   
	  * @param  first,last: Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted in the container.
Notice that the range includes all the elements between first and last, including the element pointed by first but not the one pointed by last.
	  * @retval None
	  */
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{ bst.insert(first, last); }

	 /**
	  * @brief  Removes from the map container a single element.
	  * @note   
	  * @param  position: Iterator pointing to a single element to be removed from the map.
	  * @retval None
	  */
		void erase (iterator position)
		{ bst.erase(position); }

	 /**
	  * @brief  Removes from the map container a single element.
	  * @note   
	  * @param  k: Key of the element to be removed from the map.
	  * @retval 
	  */
		size_type erase (const key_type& k)
		{
			size_t nb_elem_pre_erase = bst.size();
			bst.erase(ft::make_pair(k, mapped_type()));
			return (nb_elem_pre_erase != bst.size() ? 1 : 0);
		}

	 /**
	  * @brief  Removes from the map container a range of elements ([first,last)).
	  * @note   
	  * @param  first,last: Iterators specifying a range within the map container to be removed: [first,last).
	  * @retval None
	  */
		void erase (iterator first, iterator last)
		{ bst.erase(first, last); }

	 /**
	  * @brief  Exchanges the content of the container by the content of x, which is another map of the same type. Sizes may differ.
	  * @note   
	  * @param  x: Another map container of the same type as this (i.e., with the same template parameters, Key, T, Compare and Alloc) whose content is swapped with that of this container.
	  * @retval None
	  */
		void swap (map& x)
		{ bst.swap(x.bst); }

	 /**
	  * @brief  Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
	  * @note   
	  * @retval None
	  */
		void clear()
		{ bst.clear(); }

	 /**
	  * @brief  Returns a copy of the comparison object used by the container to compare keys.
	  * @note   
	  * @retval The comparison object.
	  */
		key_compare key_comp() const
		{ return (key_compare(key_comparator)); }

	 /**
	  * @brief  Returns a comparison object that can be used to compare two elements to get whether the key of the first one goes before the second.
	  * @note   
	  * @retval The comparison object for element values.
	  */
		value_compare value_comp() const
		{ return (value_compare(value_comparator)); }

	 /**
	  * @brief  Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
	  * @note   
	  * @param  k: Key to be searched for.
	  * @retval An iterator to the element, if an element with specified key is found, or map::end otherwise.
	  */
		iterator find (const key_type& k)
		{ return (bst.find(ft::make_pair(k, mapped_type()))); }

	 /**
	  * @brief  Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
	  * @note   
	  * @param  k: Key to be searched for.
	  * @retval An const_iterator to the element, if an element with specified key is found, or map::end otherwise.
	  */
		const_iterator find (const key_type& k) const
		{ return (bst.find(ft::make_pair(k, mapped_type()))); }

	 /**
	  * @brief  Searches the container for elements with a key equivalent to k and returns the number of matches.
	  * @note   
	  * @param  k: Key to search for.
	  * @retval 1 if the container contains an element whose key is equivalent to k, or zero otherwise.
	  */
		size_type count (const key_type& k) const
		{
			if (bst.find(ft::make_pair(k, mapped_type())) != bst.end())
				return (1);
			return(0);
		}

	 /**
	  * @brief  Returns an iterator pointing to the first element in the container whose key is not considered to go before k (i.e., either it is equivalent or goes after).
	  * @note   
	  * @param  k: Key to search for.
	  * @retval An iterator to the the first element in the container whose key is not considered to go before k, or map::end if all keys are considered to go before k.
	  */
		iterator lower_bound (const key_type& k)
		{
			iterator it, ite;
			for (it = begin(), ite = end(); it != ite; ++it)
				if (key_comparator(it->first, k) == false)
					break ;
			return (it);
		}

	 /**
	  * @brief  Returns an const_iterator pointing to the first element in the container whose key is not considered to go before k (i.e., either it is equivalent or goes after).
	  * @note   
	  * @param  k: Key to search for.
	  * @retval An const_iterator to the the first element in the container whose key is not considered to go before k, or map::end if all keys are considered to go before k.
	  */
		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator it, ite;
			for (it = begin(), ite = end(); it != ite; ++it)
				if (key_comparator(it->first, k) == false)
					break ;
			return (it);
		}

	 /**
	  * @brief  Returns an iterator pointing to the first element in the container whose key is considered to go after k.
	  * @note   
	  * @param  k: Key to search for.
	  * @retval An iterator to the the first element in the container whose key is considered to go after k, or map::end if no keys are considered to go after k.
	  */
		iterator upper_bound (const key_type& k)
		{
			iterator it, ite;
			for (it = begin(), ite = end(); it != ite; ++it)
				if (key_comparator(k, it->first) == true)
					break ;
			return (it);
		}

	 /**
	  * @brief  Returns an const_iterator pointing to the first element in the container whose key is considered to go after k.
	  * @note   
	  * @param  k: Key to search for.
	  * @retval An const_iterator to the the first element in the container whose key is considered to go after k, or map::end if no keys are considered to go after k.
	  */
		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator it, ite;
			for (it = begin(), ite = end(); it != ite; ++it)
				if (key_comparator(k, it->first) == true)
					break ;
			return (it);
		}

	 /**
	  * @brief  Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
	  * @note   
	  * @param  k: Key to search for.
	  * @retval The function returns a pair, whose member pair::first is the lower bound of the range (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
	  */
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return(ft::make_pair(lower_bound(k), upper_bound(k)));
		}

	 /**
	  * @brief  Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
	  * @note   
	  * @param  k: Key to search for.
	  * @retval The function returns a pair, whose member pair::first is the lower bound of the range (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
	  */
		pair<iterator,iterator> equal_range (const key_type& k)
		{
			return(ft::make_pair(lower_bound(k), upper_bound(k)));
		}

	 /**
	  * @brief  Returns a copy of the allocator object associated with the map.
	  * @note   
	  * @retval The allocator.
	  */
		allocator_type get_allocator() const
		{
			return(allocator_type(value_allocator));
		}

	protected:
		value_compare	value_comparator;
		key_compare		key_comparator;
		allocator_type	value_allocator;
		container_type	bst;
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (	const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		typedef typename map<Key,T,Compare,Alloc>::const_iterator const_iterator;

		if (lhs.size() != rhs.size())
			return (false);

		const_iterator first1, last1, first2;
		for (first1 = lhs.begin(), first2 = rhs.begin(), last1 = lhs.end(); first1 != last1; ++first1, ++first2)
			if (*first1 != *first2)
				return (false);
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{ return (!(lhs == rhs)); }

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{
		return(ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{ return(!(rhs < lhs)); }

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{ return(rhs < lhs); }

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
					const map<Key,T,Compare,Alloc>& rhs )
	{ return(!(lhs < rhs)); }

	template<class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{ x.swap(y); }

}

#endif // MAP_HPP