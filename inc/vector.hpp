/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:36:19 by user42            #+#    #+#             */
/*   Updated: 2022/01/11 15:09:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <iterator>
# include <memory>
# include <cstring>
# include <sstream>
# include <algorithm>

# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:

		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef normal_iterator<T>							iterator;
		typedef normal_iterator<const T>					const_iterator;
		typedef reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef reverse_iterator<iterator>					reverse_iterator;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;

		explicit vector(const allocator_type & alloc = allocator_type())
		: _alloc(alloc), _count(0), _capacity(0), _elements(NULL)
		{}

		explicit vector(size_type n,  const_reference val = value_type(), const allocator_type & alloc = allocator_type())
		: _alloc(alloc), _count(0), _capacity(0), _elements(NULL)
		{ insert(begin(), n, val); }

		template <class InputIterator>
		vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type & alloc = allocator_type())
		: _alloc(alloc), _count(0), _capacity(0), _elements(NULL)
		{ insert(begin(), first, last); }

		vector(const vector & src): _alloc(src._alloc), _count(0), _capacity(0), _elements(NULL)
		{ *this = src; }

		~vector(void)
		{
			clear();
			if (this->_elements != NULL)
				_alloc.deallocate(this->_elements, this->_capacity);
		}

		vector &	operator=(const vector & x)
		{
			if (this == &x)
				return (*this);

			clear();
			insert(begin(), x.begin(), x.end());
			return (*this);
		}

		//	iterators

		iterator		begin(void) { return (iterator(_elements)); }
		const_iterator	begin(void) const { return (const_iterator(_elements)); }

		iterator		end(void) { return (iterator(_elements + _count)); }
		const_iterator	end(void) const { return (const_iterator(_elements + _count)); }

		reverse_iterator		rbegin() { return (reverse_iterator(_elements + _count)); }
		const_reverse_iterator	rbegin() const { return (const_reverse_iterator(_elements + _count)); }

		reverse_iterator		rend() { return (reverse_iterator(_elements)); }
		const_reverse_iterator	rend() const { return (const_reverse_iterator(_elements)); }

		//	Capacity

		size_type	size(void) const { return (this->_count); }

		size_type	max_size(void) const { return (_alloc.max_size()); }

		void		resize(size_type n, value_type val = value_type())
		{
			if (n == _count)
				return ;
			if (n < _count)
			{
				for (size_type i = n; i < _count; ++i)
					_alloc.destroy(&_elements[i]);
			}
			else
			{
				reserve(n);
				for (size_type i = _count;  i < n; ++i)
					_alloc.construct(&_elements[i], val);
			}
			_count = n;
		}
		
		size_type	capacity(void) const { return (this->_capacity); }

		bool		empty(void) const { return ((this->_count == 0) ? true : false); }

		void		reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("vector::reserve");
			if (_capacity >= n)
				return ;
			pointer array = _alloc.allocate(n, this->_elements);
			if (array != this->_elements)
			{
				iterator it_elem = begin();
				iterator it_array(array);
				while (it_elem != end())
				{
					_alloc.construct(&*(it_array++), *it_elem);
					_alloc.destroy(&*(it_elem++));
				}
				this->_alloc.deallocate(this->_elements, this->_capacity);
			}
			this->_elements = array;
			this->_capacity = n;
		}

		//	Element access
		
		reference		operator[](size_type n) { return (_elements[n]); }
		const_reference	operator[](size_type n) const { return (const_cast<const_reference>(_elements[n])); }
		
		reference		at(size_type n) { range_check(n); return (_elements[n]); }
		const_reference	at(size_type n) const { range_check(n); return (const_cast<const_reference>(_elements[n])); }
		
		reference 		front(void) { return (*_elements); }
		const_reference front(void) const { return (const_cast<const_reference>(*_elements)); }

		reference 		back(void) { return (_elements[this->_count - 1]); }
		const_reference back(void) const { return (const_cast<const_reference>(_elements[this->_count - 1])); }

		//	Modifier

		void	assign(size_type count, const_reference value)
		{
			for (size_type i = 0; i < this->_count; ++i)
				_alloc.destroy(&_elements[i]);
			this->_count = 0;
			insert(begin(), count, value);
		}

		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last)
		{
			for (size_type i = 0; i < this->_count; ++i)
				_alloc.destroy(&_elements[i]);
			this->_count = 0;
			insert(begin(), first, last);
		}

		void	push_back(const_reference value) { insert(this->end(), value); }

		void	pop_back(void)
		{
			this->_alloc.destroy(&back());
			this->_count -= 1;
		}

		template <class InputIterator>
		void	insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			if (position < begin() || position > end() + 1 )
				std::__throw_out_of_range("ft::vector::insert : iterator out of range");

			difference_type nb_new_elem = std::distance(first, last);
			size_type offset = 0;
			if (this->_count > 0)
				offset = position - begin();

			if (this->_count + nb_new_elem >= this->capacity())
				reserve(((this->_count + nb_new_elem) * 2 > 0) ? (this->_count + nb_new_elem) * 2 : 1);

			position = begin() + offset;

			iterator it;
			if (end() - position > 0)
			{
				it = position + (end() - position) - 1;
				while (it >= position)
				 {
					_alloc.construct(&*(it + nb_new_elem), *it);
					_alloc.destroy(&*it);
					--it;
				}
			}

			it = position;
			while (it < position + nb_new_elem)
				_alloc.construct(&*(it++), *(first++));
			this->_count += nb_new_elem;
		}

		iterator	insert(iterator position, const_reference value)
		{
			size_type offset = 0;
			if (this->_elements != NULL)
				offset = position - this->begin();
			insert(position, 1, value);
			return (iterator(this->_elements + offset));
		}
		
		void	insert(iterator position, size_type n, const_reference value)
		{
			if (position < begin() || position > end() + 1 )
				std::__throw_out_of_range("ft::vector::insert : iterator out of range");

			size_type offset = 0;
			if (this->_count > 0)
				offset = position - begin();

			if ((this->_count + n) >= this->capacity())
				reserve(((this->_count + n) * 2 > 0) ? (this->_count + n) * 2 : 1);

			position = begin() + offset;

			iterator it;
			if (end() - position > 0)
			{
				it = position + (end() - position) - 1;
				while (it >= position)
				 {
					_alloc.construct(&*(it + n), *it);
					_alloc.destroy(&*it);
					--it;
				}
			}

			it = position;
			while (it < position + n)
				_alloc.construct(&*(it++), value);
			this->_count += n;
		}

		iterator	erase(iterator position)
		{
			erase(position, position + 1);
			return (position);
		}
		
		iterator	erase(iterator first, iterator last)
		{
			for (size_type i = 0; first + i != last; ++i)
				_alloc.destroy(&*(first + i));
			for (size_type i = 0; last + i != end(); ++i)
			{
				_alloc.construct(&*(first + i), *(last + i));
				_alloc.destroy(&*(last + i));
			}
			this->_count -= last - first;
			return (first);
		}

		void	swap(vector & v)
		{
			pointer		tmp_elements	= this->_elements;
			size_type	tmp_count		= this->_count;
			size_type	tmp_capacity	= this->_capacity;
			
			this->_elements = v._elements;
			this->_count	= v._count;
			this->_capacity = v._capacity;

			v._elements = tmp_elements;
			v._count	= tmp_count;
			v._capacity = tmp_capacity;
		}
		
		void	clear()
		{
			for (size_type i = 0; i < this->_count; ++i)
				_alloc.destroy(this->_elements + i);
			this->_count = 0;
		}

		//	Allocator

		allocator_type	get_allocator(void) const { return (this->_alloc); }

	protected:
		allocator_type	_alloc;
		size_type		_count;
		size_type		_capacity;
		pointer			_elements;

		void range_check(size_type n) const
		{
			if (n < this->_count)
				return ;
			
			std::ostringstream s;
			s << "vector::range_check: n (which is " << n << ") >= this->size() (which is " << this->size() << ")";
				throw std::out_of_range(s.str());
		}
	};

	// non-members overloads
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs)); }

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(rhs < lhs)); }

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs)); }

	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

}
#endif // VECTOR_HPP