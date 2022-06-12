/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:40:02 by user42            #+#    #+#             */
/*   Updated: 2022/01/11 15:14:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <deque>

#ifdef STL //CREATE A REAL STL EXAMPLE
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif
#include <list>
#include <map>
#include <stack>
#include <vector>

#define RAND_VALUE (rand() % 100 + 1)

#define MAX_RAM 500000000
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

struct test_struct
{
	std::string		key;
	int				value;
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};


/**
 * @brief  VECTOR =============================================================
 */

/**
 * @brief  test vector constructors
 */
void test_vector_constructors()
{
	std::cout << " ~ VECTOR CONSTRUCTOR" << std::endl;

	ft::vector<int>::size_type i;

	ft::vector<int> a(RAND_VALUE, RAND_VALUE);
	std::cout << "vector constructor(fill) - { ";
	for (i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector constructor(fill) size - " << a.size() << std::endl;

	ft::vector<int> b;
	std::cout << "vector constructor(default) - { ";
	for (i = 0; i < b.size(); ++i)
		std::cout << b[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector constructor(default) size - " << b.size() << std::endl;

	ft::vector<int> c(a);
	std::cout << "vector constructor(copy) - { ";
	for (i = 0; i < c.size(); ++i)
		std::cout << c[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector constructor(copy) size - " << c.size() << std::endl;

	ft::vector<int> e(c.begin(), c.end());
	std::cout << "vector constructor(range) - { ";
	for (i = 0; i < e.size(); ++i)
		std::cout << e[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector constructor(range) size - " << e.size() << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  test vector operator=
 */
void test_vector_operator_equal()
{
	std::cout << " ~ VECTOR OPERATOR=" << std::endl;

	ft::vector<int> a(RAND_VALUE, RAND_VALUE);
	ft::vector<int> b;

	std::cout << "vector operator= - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector operator= size - " << a.size() << std::endl;

	std::cout << "vector operator= - { ";
	for (size_t i = 0; i < b.size(); ++i)
		std::cout << b[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector operator= size - " << b.size() << std::endl;

	b = a;

	std::cout << "vector operator= - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector operator= size - " << a.size() << std::endl;

	std::cout << "vector operator= - { ";
	for (size_t i = 0; i < b.size(); ++i)
		std::cout << b[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector operator= size - " << b.size() << std::endl;
	
	std::cout << std::endl;
}

/**
 * @brief  test vector iterator
 */
void test_vector_iterator()
{
	std::cout << " ~ VECTOR ITERATOR" << std::endl;

	ft::vector<int> a;
	for (int i = 0; i < RAND_VALUE; ++i)
		a.push_back(i);
	

	ft::vector<int>::iterator it = a.begin();
	ft::vector<int>::iterator ite = a.end();

	std::cout << "random access iterator - " << it[a.size() / 2] << std::endl;

	std::cout << "vector iterator - { ";
	for (;it != ite; ++it)
		std::cout << *it << " ";
	std::cout << "}" << std::endl;

	ft::vector<int>::const_iterator c_it = a.begin();
	ft::vector<int>::const_iterator c_ite = a.end();

	std::cout << "random access const_iterator - " << c_it[a.size() / 2] << std::endl;

	std::cout << "vector const_iterator - { ";
	for (;c_it != c_ite; ++c_it)
		std::cout << *c_it << " ";
	std::cout << "}" << std::endl;

	// reverse_iterator
	
	ft::vector<int>::reverse_iterator rit = a.rbegin();
	ft::vector<int>::reverse_iterator rite = a.rend();

	std::cout << "random access reverse_iterator - " << rit[a.size() / 2] << std::endl;

	std::cout << "vector reverse_iterator - { ";
	for (;rit != rite; ++rit)
		std::cout << *rit << " ";
	std::cout << "}" << std::endl;

	ft::vector<int>::const_reverse_iterator c_rit = a.rbegin();
	ft::vector<int>::const_reverse_iterator c_rite = a.rend();

	std::cout << "random access const_reverse_iterator - " << c_rit[a.size() / 2] << std::endl;

	std::cout << "vector const_reverse_iterator - { ";
	for (;c_rit != c_rite; ++c_rit)
		std::cout << *c_rit << " ";
	std::cout << "}" << std::endl;

	// incrementation test

	it = a.begin();
	std::cout << "vector pre-incrementation - { ";
	for (size_t i = 0; i < a.size() / 2; ++it, ++i)
		std::cout << *it << " ";
	std::cout << "}" << std::endl;

	std::cout << "vector pre-decrementation - { ";
	for (; it != a.begin(); --it)
		std::cout << *it << " ";
	std::cout << "}" << std::endl;

	std::cout << "vector post-incrementation - { ";
	for (size_t i = 0; i < a.size() / 2; it++, ++i)
		std::cout << *it << " ";
	std::cout << "}" << std::endl;

	std::cout << "vector post-decrementation - { ";
	for (; it != a.begin(); it--)
		std::cout << *it << " ";
	std::cout << "}" << std::endl;

	it = a.begin();
	std::cout << "iterator operator+= - " << *(it += (a.size() / 2)) << std::endl;
	std::cout << "iterator operator-= - " << *(it -= (a.size() / 2)) << std::endl;
	std::cout << "iterator operator+ (a + n) - " << *(it + (a.size() / 2)) << std::endl;
	std::cout << "iterator operator+ (n + a) - " << *((a.size() / 2) + it) << std::endl;
	it = a.end();
	std::cout << "iterator operator- (a - n) - " << *(it - (a.size() / 2)) << std::endl;
	std::cout << "iterator operator- (a - b) - " << (it - a.begin()) << std::endl;

	// test operator->

	test_struct a_struct;
	a_struct.key = "yolo";
	a_struct.value = 42;

	ft::vector<test_struct> b(5, a_struct);
	ft::vector<test_struct>::iterator struct_it = b.begin();

	std::cout << "iterator::operator-> - " << struct_it->key << " " << struct_it->value << std::endl;

	// relational operator
	std::cout << "iterator operator== - " << (a.begin() == a.end()) << std::endl;
	std::cout << "iterator operator!= - " << (a.begin() != a.end()) << std::endl;
	std::cout << "iterator operator> - " << (a.begin() > a.end()) << std::endl;
	std::cout << "iterator operator>= - " << (a.begin() >= a.end()) << std::endl;
	std::cout << "iterator operator< - " << (a.begin() < a.end()) << std::endl;
	std::cout << "iterator operator<= - " << (a.begin() <= a.end()) << std::endl;

	std::cout << "iterator operator== - " << (a.begin() == a.begin()) << std::endl;
	std::cout << "iterator operator!= - " << (a.begin() != a.begin()) << std::endl;
	std::cout << "iterator operator> - " << (a.begin() > a.begin()) << std::endl;
	std::cout << "iterator operator>= - " << (a.begin() >= a.begin()) << std::endl;
	std::cout << "iterator operator< - " << (a.begin() < a.begin()) << std::endl;
	std::cout << "iterator operator<= - " << (a.begin() <= a.begin()) << std::endl;

	std::cout << "iterator operator== - " << (a.end() == a.begin()) << std::endl;
	std::cout << "iterator operator!= - " << (a.end() != a.begin()) << std::endl;
	std::cout << "iterator operator> - " << (a.end() > a.begin()) << std::endl;
	std::cout << "iterator operator>= - " << (a.end() >= a.begin()) << std::endl;
	std::cout << "iterator operator< - " << (a.end() < a.begin()) << std::endl;
	std::cout << "iterator operator<= - " << (a.end() <= a.begin()) << std::endl;

	// use iterator with stl
	std::vector<int> stl_v(a.begin(), a.end());
	std::vector<int>::iterator itt = stl_v.begin();

	std::cout << "vector use ft::iterator with stl - { ";
	for (;itt != stl_v.end(); ++itt)
		std::cout << *itt << " ";
	std::cout << "}" << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  test vector size max size
 */
void test_vector_size_max_size()
{
	std::cout << " ~ VECTOR SIZE / MAX_SIZE" << std::endl;

	ft::vector<int> a;
	std::cout << "vector max_size - " << a.max_size() << std::endl;
	std::cout << "vector empty - " << a.empty() << std::endl;
	
	std::cout << "vector size - ";
	for (int i = 0; i < RAND_VALUE; ++i)
		a.push_back(RAND_VALUE);
	std::cout << a.size() << std::endl;

	a.resize(20);
	std::cout << "vector resize(20) size - " << a.size() << std::endl;

	a.resize(50);
	std::cout << "vector resize(50) size - " << a.size() << std::endl;
	a.resize(50);
	std::cout << "vector resize(50) size - " << a.size() << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  test vector reserve
 */
void test_vector_reserve_capacity()
{
	std::cout << " ~ VECTOR RESERVE / CAPACITY" << std::endl;

	ft::vector<int> a;
	std::cout << "vector reserve(42) - ";
	try
	{
		a.reserve(RAND_VALUE);
		std::cout << "OK" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "vector reserve(max_size() + 42) - ";
	try
	{
		a.reserve(a.max_size() + 42);
		std::cout << "should have thrown a length_error exception"<< std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "OK" << std::endl;
	}

	std::cout << "vector capacity - " << a.capacity() << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  tes vector elements access
 */
void test_vector_elements_access()
{
	std::cout << " ~ VECTOR ELEMENTS ACCESS" << std::endl;

	size_t size = RAND_VALUE + 42;
	ft::vector<int> a;
	for (size_t i = 0; i < size; ++i)
		a.push_back(RAND_VALUE);
	
	std::cout << "vector a[0] - " << a[0] << std::endl;
	std::cout << "vector a[size - 1] - " << a[size - 1] << std::endl;
	std::cout << "vector a[size / 2] - " << a[size / 2] << std::endl;
	std::cout << "vector a[size / 3] - " << a[size / 3] << std::endl;

	try
	{
		std::cout << "vector at(0) - " << a.at(0) << std::endl;
		std::cout << "vector at(size - 1) - " << a.at(size - 1) << std::endl;
		std::cout << "vector at(size / 2) - " << a.at(size / 2) << std::endl;
		std::cout << "vector at(size + 42) - " << a.at(size + 42) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "catch exception" << std::endl;
	}
	
	std::cout << "vector front() - " << a.front() << std::endl;
	std::cout << "vector back() - " << a.back() << std::endl;
	
	std::cout << std::endl;
}

/**
 * @brief  test vector modifier
 */
void test_vector_modifier()
{
	std::cout << " ~ VECTOR MODIFIER" << std::endl;
	ft::vector<int> a;

	// assing 

	a.assign(RAND_VALUE, RAND_VALUE);
	std::cout << "vector assign(fill) - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector a size - " << a.size() << std::endl;

	ft::vector<int> b;

	b.assign(a.begin(), a.end());
	std::cout << "vector assing(range) - { ";
	for (size_t i = 0; i < b.size(); ++i)
		std::cout << b[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector b size - " << b.size() << std::endl;

	// push/pop_back

	a.push_back(RAND_VALUE);
	std::cout << "vector push_back size - " << a.size() << std::endl;
	a.pop_back();
	std::cout << "vector pop_back size - " << a.size() << std::endl;

	// insert

	a.insert(a.begin(), RAND_VALUE);
	std::cout << "vector insert(element) - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector a size - " << a.size() << std::endl;

	a.insert(a.begin(), RAND_VALUE, RAND_VALUE);
	std::cout << "vector insert(fill) - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector a size - " << a.size() << std::endl;

	a.insert(a.end(), b.begin(), b.end());
	std::cout << "vector insert(range) - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector a size - " << a.size() << std::endl;
	
	// erase

	a.erase(a.begin() + a.size() / 2);
	std::cout << "vector erase(position) - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector a size - " << a.size() << std::endl;
	
	a.erase(a.begin() + a.size() / 2, a.end());
	std::cout << "vector erase(first, last) - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector a size - " << a.size() << std::endl;

	// clear

	a.clear();
	std::cout << "vector clear - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector a size - " << a.size() << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  test vector get_allocator
 */
void test_vector_get_allocator()
{
	std::cout << " ~ VECTOR GET ALLOCATOR" << std::endl;

	ft::vector<int> a;
	std::cout << a.get_allocator().max_size() << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  test vector relational operator
 */
void test_vector_relational_operator()
{
	std::cout << " ~ VECTOR RELATIONAL OPERATOR" << std::endl;

	ft::vector<int> a;
	ft::vector<int> b;

	for(int i = 0; i < RAND_VALUE; ++i)
		a.push_back(i * RAND_VALUE * 69);
	for(int i = 0; i < RAND_VALUE; ++i)
		b.push_back(i * RAND_VALUE * 42);

	std::cout << "vector operator== - " << (a == b) << std::endl;
	std::cout << "vector operator!= - " << (a != b) << std::endl;
	std::cout << "vector operator> - " << (a > b) << std::endl;
	std::cout << "vector operator>= - " << (a >= b) << std::endl;
	std::cout << "vector operator< - " << (a < b) << std::endl;
	std::cout << "vector operator<= - " << (a <= b) << std::endl;

	std::cout << "vector operator== - " << (a == a) << std::endl;
	std::cout << "vector operator!= - " << (a != a) << std::endl;
	std::cout << "vector operator> - " << (a > a) << std::endl;
	std::cout << "vector operator>= - " << (a >= a) << std::endl;
	std::cout << "vector operator< - " << (a < a) << std::endl;
	std::cout << "vector operator<= - " << (a <= a) << std::endl;

	std::cout << "vector operator== - " << (b == a) << std::endl;
	std::cout << "vector operator!= - " << (b != a) << std::endl;
	std::cout << "vector operator> - " << (b > a) << std::endl;
	std::cout << "vector operator>= - " << (b >= a) << std::endl;
	std::cout << "vector operator< - " << (b < a) << std::endl;
	std::cout << "vector operator<= - " << (b <= a) << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  test vector swap
 */
void test_vector_swap()
{
	std::cout << " ~ VECTOR SWAP" << std::endl;

	ft::vector<int> a(RAND_VALUE, RAND_VALUE);
	ft::vector<int> b;

	std::cout << "vector a - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector a size - " << a.size() << std::endl;

	std::cout << "vector b - { ";
	for (size_t i = 0; i < b.size(); ++i)
		std::cout << b[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector b size - " << b.size() << std::endl;

	swap(a, b);
	std::cout << "swap(a, b)" << std::endl;
	std::cout << "vector a - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector a size - " << a.size() << std::endl;

	std::cout << "vector b - { ";
	for (size_t i = 0; i < b.size(); ++i)
		std::cout << b[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector b size - " << b.size() << std::endl;

	a.swap(b);
	std::cout << "a.swap(b)" << std::endl;
	std::cout << "vector a - { ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector a size - " << a.size() << std::endl;

	std::cout << "vector b - { ";
	for (size_t i = 0; i < b.size(); ++i)
		std::cout << b[i] << " ";
	std::cout << "}" << std::endl;
	std::cout << "vector b size - " << b.size() << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  STACK ==============================================================
 */

/**
 * @brief  test stack constructors
 */
void test_stack()
{
	std::cout << " ~ STACK" << std::endl;

	ft::stack<int> a;
	std::cout << "stack constructor size - " << a.size() << std::endl;
	std::cout << "stack empty - " << a.empty() << std::endl;

	for (int i = 0; i < RAND_VALUE; ++i)
		a.push(i);
	std::cout << "stack size after pushes - " << a.size() << std::endl;
	std::cout << "stack empty - " << a.empty() << std::endl;

	ft::stack<int> b;
	for (int i = 0; i < RAND_VALUE; ++i)
		b.push(i * RAND_VALUE);

	std::cout << "vector operator== - " << (a == b) << std::endl;
	std::cout << "vector operator!= - " << (a != b) << std::endl;
	std::cout << "vector operator> - " << (a > b) << std::endl;
	std::cout << "vector operator>= - " << (a >= b) << std::endl;
	std::cout << "vector operator< - " << (a < b) << std::endl;
	std::cout << "vector operator<= - " << (a <= b) << std::endl;

	std::cout << "vector operator== - " << (a == a) << std::endl;
	std::cout << "vector operator!= - " << (a != a) << std::endl;
	std::cout << "vector operator> - " << (a > a) << std::endl;
	std::cout << "vector operator>= - " << (a >= a) << std::endl;
	std::cout << "vector operator< - " << (a < a) << std::endl;
	std::cout << "vector operator<= - " << (a <= a) << std::endl;

	std::cout << "vector operator== - " << (b == a) << std::endl;
	std::cout << "vector operator!= - " << (b != a) << std::endl;
	std::cout << "vector operator> - " << (b > a) << std::endl;
	std::cout << "vector operator>= - " << (b >= a) << std::endl;
	std::cout << "vector operator< - " << (b < a) << std::endl;
	std::cout << "vector operator<= - " << (b <= a) << std::endl;

	std::cout << "stack top & pop - { ";
	for (size_t i = 0; !a.empty(); ++i)
	{
		std::cout << a.top() << " ";
		a.pop();
	}
	std::cout << "}" << std::endl;
	std::cout << "stack size - " << a.size() << std::endl;
	std::cout << "stack empty - " << a.empty() << std::endl;

	ft::stack<int, std::list<int> > d;
	for (int i = 0; i < RAND_VALUE; ++i)
		d.push(i * RAND_VALUE);
	std::cout << "stack top & pop - { ";
	for (size_t i = 0; !d.empty(); ++i)
	{
		std::cout << d.top() << " ";
		d.pop();
	}
	std::cout << "}" << std::endl;
	std::cout << "stack size - " << d.size() << std::endl;
	std::cout << "stack empty - " << d.empty() << std::endl;

	std::list<int> l;
	for (int i = 0; i < RAND_VALUE; ++i)
		l.push_back(i * RAND_VALUE);

	ft::stack<int, std::list<int> > e(l);
	std::cout << "stack size - " << e.size() << std::endl;
	std::cout << "stack empty - " << e.empty() << std::endl;
	std::cout << "stack top & pop - { ";
	for (size_t i = 0; !e.empty(); ++i)
	{
		std::cout << e.top() << " ";
		e.pop();
	}
	std::cout << "}" << std::endl;
	std::cout << "stack size - " << e.size() << std::endl;
	std::cout << "stack empty - " << e.empty() << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  MAP ==============================================================
 */

/**
 * @brief  test map constructors
 */
void test_map_constructors()
{
	std::cout << " ~ MAP CONSTRUCTOR" << std::endl;


	ft::map<int, std::string>::iterator it;

	ft::map<int, std::string> a;
	for (int i = 0; i < RAND_VALUE; ++i)
		a.insert(ft::make_pair<int, std::string>(RAND_VALUE, "yolo"));
	std::cout << "map constructor(default) - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map constructor(default) size - " << a.size() << std::endl;

	ft::map<int, std::string> b(a);
	std::cout << "map constructor(copy) - { ";
	for (it = b.begin(); it != b.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map constructor(copy) size - " << b.size() << std::endl;

	ft::map<int, std::string> c(b.begin(), b.end());
	std::cout << "map constructor(range) - { ";
	for (it = c.begin(); it != c.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map constructor(range) size - " << c.size() << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  test map operator=
 */
void test_map_operator_equal()
{
	std::cout << " ~ MAP OPERATOR=" << std::endl;

	ft::map<int, std::string>::iterator it;

	ft::map<int, std::string> a;
	for (int i = 0; i < RAND_VALUE; ++i)
		a.insert(ft::make_pair<int, std::string>(RAND_VALUE, "yolo"));
	ft::map<int, std::string> b;
	for (int i = 0; i < RAND_VALUE; ++i)
		b.insert(ft::make_pair<int, std::string>(RAND_VALUE, "yolo"));

	std::cout << "map operator= - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map operator= size - " << a.size() << std::endl;

	std::cout << "map operator= - { ";
	for (it = b.begin(); it != b.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map operator= size - " << b.size() << std::endl;

	b = a;

	std::cout << "map operator= - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map operator= size - " << a.size() << std::endl;

	std::cout << "map operator= - { ";
	for (it = b.begin(); it != b.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map operator= size - " << b.size() << std::endl;
	
	std::cout << std::endl;
}

/**
 * @brief  test map iterator
 */
void test_map_iterator()
{
	std::cout << " ~ MAP ITERATOR" << std::endl;

	ft::map<int, std::string> a;
	for (int i = 0; i < RAND_VALUE; ++i)
		a.insert(ft::make_pair<int, std::string>(RAND_VALUE, "yolo"));
	

	ft::map<int, std::string>::iterator it = a.begin();
	ft::map<int, std::string>::iterator ite = a.end();

	std::cout << "map iterator - { ";
	for (;it != ite; ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;

	ft::map<int, std::string>::const_iterator c_it = a.begin();
	ft::map<int, std::string>::const_iterator c_ite = a.end();

	std::cout << "map const_iterator - { ";
	for (;c_it != c_ite; ++c_it)
		std::cout << c_it->first << " ";
	std::cout << "}" << std::endl;

	// reverse_iterator
	
	ft::map<int, std::string>::reverse_iterator rit = a.rbegin();
	ft::map<int, std::string>::reverse_iterator rite = a.rend();

	std::cout << "map reverse_iterator - { ";
	for (;rit != rite; ++rit)
		std::cout << rit->first << " ";
	std::cout << "}" << std::endl;

	ft::map<int, std::string>::const_reverse_iterator c_rit = a.rbegin();
	ft::map<int, std::string>::const_reverse_iterator c_rite = a.rend();

	std::cout << "map const_reverse_iterator - { ";
	for (;c_rit != c_rite; ++c_rit)
		std::cout << c_rit->first << " ";
	std::cout << "}" << std::endl;

	// incrementation test

	it = a.begin();
	std::cout << "map pre-incrementation - { ";
	for (size_t i = 0; i < a.size() / 2; ++it, ++i)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;

	std::cout << "map pre-decrementation - { ";
	for (; it != a.begin(); --it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;

	std::cout << "map post-incrementation - { ";
	for (size_t i = 0; i < a.size() / 2; it++, ++i)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;

	std::cout << "map post-decrementation - { ";
	for (; it != a.begin(); it--)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;

	// relational operator
	std::cout << "iterator operator== - " << (a.begin() == a.end()) << std::endl;
	std::cout << "iterator operator!= - " << (a.begin() != a.end()) << std::endl;

	std::cout << "iterator operator== - " << (a.begin() == a.begin()) << std::endl;
	std::cout << "iterator operator!= - " << (a.begin() != a.begin()) << std::endl;

	std::cout << "iterator operator== - " << (a.end() == a.begin()) << std::endl;
	std::cout << "iterator operator!= - " << (a.end() != a.begin()) << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  test map size max size
 */
void test_map_size_max_size()
{
	std::cout << " ~ MAP SIZE / MAX_SIZE" << std::endl;

	ft::map<int, std::string>::iterator it;

	ft::map<int, std::string> a;
	std::cout << "map max_size - " << a.max_size() << std::endl;
	std::cout << "map size - " << a.size() << std::endl;
	std::cout << "map empty - " << a.empty() << std::endl;
	
	for (int i = 0; i < RAND_VALUE; ++i)
		a.insert(ft::make_pair<int, std::string>(RAND_VALUE, "yolo"));
	std::cout << "map post-decrementation - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map size - " << a.size() << std::endl;
	std::cout << "map empty - " << a.empty() << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  test map elements access
 */
void test_map_elements_access()
{
	std::cout << " ~ MAP ELEMENTS ACCESS" << std::endl;

	ft::map<int, int> a;
	size_t size = 42;
	for (size_t i = 0; i < size; ++i)
		a.insert(ft::make_pair(i, i * 42));
	
	std::cout << "map values (iterator) - { ";
	for (ft::map<int, int>::iterator it = a.begin(); it != a.end(); ++it)
		std::cout << it->second << " ";
	std::cout << "}" << std::endl;

	size_t max_size = a.size() + 10;
	std::cout << "map values (operator[]) - { ";
	for (size_t i = 0; i < max_size; ++i)
		std::cout << a[i] << " ";
	std::cout << "}" << std::endl;
	
	std::cout << std::endl;
}

/**
 * @brief  test map modifier
 */
void test_map_modifier()
{
	std::cout << " ~ MAP MODIFIER" << std::endl;
	ft::map<int, std::string> a;
	ft::map<int, std::string> b;
	ft::map<int, std::string>::iterator it;

	// insert

	std::cout << "key 42 inserted - " << a.insert(ft::make_pair(42, "A")).second << std::endl;
	std::cout << "key 69 inserted - " << a.insert(ft::make_pair(69, "A")).second << std::endl;
	std::cout << "key 42 inserted - " << a.insert(ft::make_pair(42, "C")).second << std::endl;
	std::cout << "key 85 inserted - " << a.insert(ft::make_pair(85, "B")).second << std::endl;
	std::cout << "key 11 inserted - " << a.insert(ft::make_pair(11, "B")).second << std::endl;
	std::cout << "key 69 inserted - " << a.insert(ft::make_pair(69, "F")).second << std::endl;
	
	it = a.insert(a.end(), ft::make_pair(5, "F"));
	std::cout << "key inserted - " << it->first << " | " << it->second << std::endl;
	it = a.insert(a.begin(), ft::make_pair(642, "F"));
	std::cout << "key inserted - " << it->first << " | " << it->second << std::endl;

	std::cout << "map insert(element) - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map size - " << a.size() << std::endl;

	b.insert(a.begin(), a.end());
	std::cout << "map insert(range) - { ";
	for (it = b.begin(); it != b.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map size - " << b.size() << std::endl;

	// erase

	a.erase(a.find(42));
	std::cout << "map erase(position) - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map size - " << a.size() << std::endl;
	
	a.erase(69);
	std::cout << "map erase(key) - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map size - " << a.size() << std::endl;

	a.erase(a.begin(), a.find(85));
	std::cout << "map erase(first, last) - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map size - " << a.size() << std::endl;

	// clear

	a.clear();
	std::cout << "map clear - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;
	std::cout << "map size - " << a.size() << std::endl;
	std::cout << "map empty - " << a.empty() << std::endl;

	std::cout << std::endl;
}

/**
 * @brief  test map swap relational_ope
 */
void test_map_swap_relational_ope()
{
	std::cout << " ~ MAP SWAP & RELATIONAL OPE" << std::endl;
	ft::map<int, std::string> a;
	ft::map<int, std::string> b;
	ft::map<int, std::string>::iterator it;

	a[-56] = "froid";
	a[21] = "ecc";
	a[42] = "ecole";
	a[69] = "lmao";
	a[123] = "bus";
	a[666] = "satan";

	b[-56] = "froid";
	b[21] = "AH";
	b[42] = "ecole";
	b[69] = "lmao";

	std::cout << "map a - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;

	std::cout << "map b - { ";
	for (it = b.begin(); it != b.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;

	std::cout << "a == b = " << (a == b) << std::endl;
	std::cout << "a != b = " << (a != b) << std::endl;
	std::cout << "a < b = " << (a < b) << std::endl;
	std::cout << "a <= b = " << (a <= b) << std::endl;
	std::cout << "a > b = " << (a > b) << std::endl;
	std::cout << "a >= b = " << (a >= b) << std::endl;

	std::cout << "b == a = " << (b == a) << std::endl;
	std::cout << "b != a = " << (b != a) << std::endl;
	std::cout << "b < a = " << (b < a) << std::endl;
	std::cout << "b <= a = " << (b <= a) << std::endl;
	std::cout << "b > a = " << (b > a) << std::endl;
	std::cout << "b >= a = " << (b >= a) << std::endl;

	std::cout << "a.swap(b)" << std::endl;
	ft::swap(a, b);

	std::cout << "map a - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;

	std::cout << "map b - { ";
	for (it = b.begin(); it != b.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;

	std::cout << "a == b = " << (a == b) << std::endl;
	std::cout << "a != b = " << (a != b) << std::endl;
	std::cout << "a < b = " << (a < b) << std::endl;
	std::cout << "a <= b = " << (a <= b) << std::endl;
	std::cout << "a > b = " << (a > b) << std::endl;
	std::cout << "a >= b = " << (a >= b) << std::endl;

	std::cout << "b == a = " << (b == a) << std::endl;
	std::cout << "b != a = " << (b != a) << std::endl;
	std::cout << "b < a = " << (b < a) << std::endl;
	std::cout << "b <= a = " << (b <= a) << std::endl;
	std::cout << "b > a = " << (b > a) << std::endl;
	std::cout << "b >= a = " << (b >= a) << std::endl;
}

/**
 * @brief  test value key comp
 */
void test_map_value_key_comp()
{
	std::cout << " ~ MAP VALUE KEY COMP" << std::endl;
	ft::map<int, int> a;

	a[69] = 87;
	a[42] = 456;
	a[21] = 4;
	a[5] = 84;
	a[489] = 20;

	std::cout << a.key_comp()(a.begin()->first, (++a.begin())->first) << std::endl;
	std::cout << a.value_comp()(*a.begin(), *(++a.begin())) << std::endl;

}

/**
 * @brief  test value key comp
 */
void test_map_operation()
{
	std::cout << " ~ MAP OPERATION" << std::endl;
	ft::map<int, int> a;
	ft::map<int, int>::iterator it;

	a[69] = 87;
	a[42] = 456;
	a[21] = 4;
	a[5] = 84;
	a[489] = 20;

	std::cout << "map a - { ";
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "}" << std::endl;

	// find
	std::cout << "searching 21456 : ";
	if ((it = a.find(21456)) != a.end())
		std::cout << it->first << std::endl;
	else
		std::cout << "not found" << std::endl;

	std::cout << "searching 42 : ";
	if ((it = a.find(42)) != a.end())
			std::cout << it->first << std::endl;
	else
		std::cout << "not found" << std::endl;
	
	// count
	std::cout << "count key 21456 : " << a.count(21546) << std::endl;
	std::cout << "count key 42 : " << a.count(42) << std::endl;

	// lower bound
	std::cout << "lowerbound for 42 : ";
	if ((it = a.lower_bound(42)) != a.end())
		std::cout << it->first << std::endl;
	else
		std::cout << "map::end" << std::endl;

	std::cout << "lowerbound for -56 : ";
	if ((it = a.lower_bound(-56)) != a.end())
		std::cout << it->first << std::endl;
	else
		std::cout << "map::end" << std::endl;

	std::cout << "lowerbound for 6541568 : ";
	if ((it = a.lower_bound(6541568)) != a.end())
		std::cout << it->first << std::endl;
	else
		std::cout << "map::end" << std::endl;

	// upper bound
	std::cout << "upperbound for 42 : ";
	if ((it = a.upper_bound(42)) != a.end())
		std::cout << it->first << std::endl;
	else
		std::cout << "map::end" << std::endl;

	std::cout << "upperbound for -56 : ";
	if ((it = a.upper_bound(-56)) != a.end())
		std::cout << it->first << std::endl;
	else
		std::cout << "map::end" << std::endl;

	std::cout << "upperbound for 6541568 : ";
	if ((it = a.upper_bound(6541568)) != a.end())
		std::cout << it->first << std::endl;
	else
		std::cout << "map::end" << std::endl;
	
	// equal range
	ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> p;

	p = a.equal_range(42);
	std::cout << "upperbound for 42 : ";
	if (p.first != a.end())
		std::cout << p.first->first << " - ";
	else
		// std::cout << "map::end" << " - ";
	if (p.second != a.end())
		std::cout << p.second->first << std::endl;
	else
		std::cout << "map::end" << std::endl;

	p = a.equal_range(-56);
	std::cout << "range for -56 : ";
	if (p.first != a.end())
		std::cout << p.first->first << " - ";
	else
		std::cout << "map::end" << " - ";
	if (p.second != a.end())
		std::cout << p.second->first << std::endl;
	else
		std::cout << "map::end" << std::endl;

	p = a.equal_range(6541568);
	std::cout << "range for 6541568 : ";
	if (p.first != a.end())
		std::cout << p.first->first << " - ";
	else
		std::cout << "map::end" << " - ";
	if (p.second != a.end())
		std::cout << p.second->first << std::endl;
	else
		std::cout << "map::end" << std::endl;
}

/**
 * @brief  MAIN ===============================================================
 */

int more_test()
{
	std::cout << std::boolalpha;

	/**
	 *  vector
	 */
	test_vector_constructors();
	test_vector_operator_equal();
	test_vector_iterator();
	test_vector_size_max_size();
	test_vector_reserve_capacity();
	test_vector_elements_access();
	test_vector_modifier();
	test_vector_get_allocator();
	test_vector_relational_operator();
	test_vector_swap();

	/**
	 *  stack
	 */
	test_stack();

	/**
	 *  map
	 */
	test_map_constructors();
	test_map_operator_equal();
	test_map_iterator();
	test_map_size_max_size();
	test_map_elements_access();
	test_map_modifier();
	test_map_swap_relational_ope();
	test_map_value_key_comp();
	test_map_operation();

	return (0);
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
#ifdef	STL
	std::cout << "using STL containers" << std::endl;
#else
	std::cout << "using FT containers" << std::endl;
#endif
	std::cout << " ~ SUBJECT MAIN TEST" << std::endl;

	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
		std::cout << e.what() << std::endl;
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}

	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	more_test();
	return (0);
}