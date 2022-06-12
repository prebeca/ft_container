/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySearchTree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:26:00 by user42            #+#    #+#             */
/*   Updated: 2022/01/10 13:07:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include <functional>
# include <memory>
# include <iostream>
# include <cstdlib>
# include <sstream>

# include "iterator.hpp"
# include "pair.hpp"

namespace ft
{

	template <typename T, typename Compare = std::less<T>,
	typename Alloc = std::allocator<T> >
	class BinarySearchTree
	{
	private:
		struct	Node;

	public:
		typedef T														value_type;
		typedef T&														reference;
		typedef T*														pointer;
		typedef Compare													value_compare;
		typedef Alloc													allocator_type;
		typedef typename ft::bst_iterator<Node, value_type>				iterator;
		typedef typename ft::bst_iterator<const Node, const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

	private:
		typedef typename allocator_type::template rebind<Node>::other	node_allocator_type;

	public:

		BinarySearchTree(value_compare comp = value_compare(), value_type default_node_value = value_type())
		: root(NULL), comp(comp), nb_elem(0)
		{
			end_node = node_allocator.allocate(1);
			node_allocator.construct(end_node, default_node_value);
			root = end_node->left = end_node->parent = end_node;

		}

		template<class Iterator>
		BinarySearchTree(Iterator first, Iterator last, value_compare comp = value_compare(), value_type default_node_value = value_type())
		: root(NULL), comp(comp), nb_elem(0)
		{
			end_node = node_allocator.allocate(1);
			node_allocator.construct(end_node, default_node_value);
			root = end_node->left = end_node->parent = end_node;
			insert(first, last);
		}

		BinarySearchTree(const BinarySearchTree & n)
		: root(NULL), comp(n.comp), nb_elem(0)
		{
			end_node = node_allocator.allocate(1);
			node_allocator.construct(end_node, *n.end_node);
			root = end_node->left = end_node->parent = end_node;
			insert(n.begin(), n.end());
		}

		~BinarySearchTree()
		{
			clear();
			node_allocator.destroy(end_node);
			node_allocator.deallocate(end_node, 1);
		}

		BinarySearchTree& operator=(const BinarySearchTree & n)
		{
			clear();
			insert(n.begin(), n.end());
			return (*this);
		}

		/**
		 * @note   Iterator
		 */

		iterator begin() { return (iterator(end_node->left)); }
		const_iterator begin() const { return (const_iterator(end_node->left)); }

		iterator end() { return (iterator(end_node)); }
		const_iterator end() const { return (const_iterator(end_node)); }

		reverse_iterator rbegin() { return (reverse_iterator(end())); }
 		const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
		
		reverse_iterator rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

		/**
		 * @note   Modifiers
		 */

		ft::pair<iterator, bool> insert(const value_type& value)
		{
			ft::pair<Node*, ft::pair<iterator, bool> > p = _insert(root, NULL, value);
			root = p.first;
			return (p.second);
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				insert(*first);
		}

		void	erase(const value_type& value)
		{ root = _erase(root, value); }

		void	erase(iterator position)
		{
			Node* current = position.current;
			Node** pos = &root;
			if (current->parent)
				pos = (current->parent->left == current ? &current->parent->left : &current->parent->right);
			*pos = _erase(position.current, *position);
		}
		
		void	erase(iterator first, iterator last)
		{
			while (first != last)
			{
				iterator next = first++;
				erase(*next);
			}
		}

		void clear()
		{
			_clear(root);
			root = end_node->left = end_node->right = end_node;
		}

		/**
		 * @note   Other
		 */

		bool	empty() const
		{ return(!nb_elem); }

		size_t size() const
		{ return (nb_elem); }

		size_t max_size() const
		{ return (node_allocator.max_size()); }

		iterator	find(value_type value)
		{ return (iterator(_find(root, value))); }

		const_iterator	find(value_type value) const
		{ return (const_iterator(_find(root, value))); }

		std::string print_newick() const
		{
			std::stringstream ss;
			_print_newick(ss, root);
			ss << ";";
			return(ss.str());
		}

		void swap(BinarySearchTree& bst)
		{
			Node* tmp_root		= this->root;
			Node* tmp_end_node	= this->end_node;
			size_t tmp_nb_elem	= this->nb_elem;

			this->root		= bst.root;
			this->end_node	= bst.end_node;
			this->nb_elem	= bst.nb_elem;

			bst.root = tmp_root;
			bst.end_node = tmp_end_node;
			bst.nb_elem = tmp_nb_elem;
		}

	private:

		struct Node
		{
			typedef value_type	value_type;
			value_type content;

			Node*	parent;
			Node* 	left;
			Node*	right;
			int		height;

			Node(const value_type& content, Node* parent = NULL, Node* left = NULL, Node* right = NULL, int height = 0)
			: content(content), parent(parent), left(left), right(right), height(height)
			{}

			Node(const Node& n)
			: content(n.content), parent(n.parent), left(n.left), right(n.right), height(n.height)
			{}

			static Node* node_rightMost(Node* n)
			{
				if (!n->right || n->right->height == 0)
					return (n);
				return(node_rightMost(n->right));
			}

			static Node* node_leftMost(Node* n)
			{
				if (n->left->height == 0)
					return (n);
				return(node_leftMost(n->left));
			}

			static const Node* node_rightMost(const Node* n)
			{
				if (!n->right || n->right->height == 0)
					return (n);
				return(node_rightMost(n->right));
			}

			static const Node* node_leftMost(const Node* n)
			{
				if (n->left->height == 0)
					return (n);
				return(node_leftMost(n->left));
			}

			Node *previous()
			{
				if (height != 0)
				{
					if (left->height == 0 && left->left == this)
						return (this);
					if (left->height != 0)
						return (node_rightMost(left));
				}
				Node *next = this;
				while (next)
				{
					if (next->parent == NULL)
						return (this);
					if (next == next->parent->right)
						return (next->parent);
					next = next->parent;
				}
				return (next);
			}

			const Node *previous() const
			{
				if (height != 0)
				{
					if (left->height == 0 && left->left == this)
						return (this);
					if (left->height != 0)
						return (node_rightMost(left));
				}
				const Node *next = this;
				while (next)
				{
					if (next->parent == NULL)
						return (this);
					if (next == next->parent->right)
						return (next->parent);
					next = next->parent;
				}
				return (next);
			}

			Node*	next()
			{
				if (right == NULL)
					return (this);
				else
				{
					if (right->height == 0 && right->parent == this)
						return(right);
					if (right->height != 0)
						return(node_leftMost(right));
				}
				Node* next = this;
				while (next)
				{
					if (next->parent == NULL)
						return(this);
					if (next == next->parent->left)
						return (next->parent);
					next = next->parent;
				}
				return (next);
			}

			const Node*	next() const
			{
				if (right == NULL)
					return (this);
				else
				{
					if (right->height == 0 && right->parent == this)
						return(right);
					if (right->height != 0)
						return(node_leftMost(right));
				}
				const Node* next = this;
				while (next)
				{
					if (next->parent == NULL)
						return(this);
					if (next == next->parent->left)
						return (next->parent);
					next = next->parent;
				}
				return (next);
			}
		};

		Node* _rotate_right(Node* n)
		{
			Node* l_child = n->left;
			Node* lr_grand_child = l_child->right;

			l_child->right = n;
			l_child->parent = n->parent;
			n->parent = l_child;
			n->left = lr_grand_child;
			if (lr_grand_child != end_node)
				lr_grand_child->parent = n;
			
			n->height = 1 + std::max(n->left->height, n->right->height);
			l_child->height = 1 + std::max(l_child->left->height, l_child->right->height);

			return (l_child);
		}

		Node* _rotate_left(Node* n)
		{
			Node* r_child = n->right;
			Node* rl_grand_child = r_child->left;

			r_child->left = n;
			r_child->parent = n->parent;
			n->parent = r_child;
			n->right = rl_grand_child;
			if (rl_grand_child != end_node)
				rl_grand_child->parent = n;

			n->height = 1 + std::max(n->left->height, n->right->height);
			r_child->height = 1 + std::max(r_child->left->height, r_child->right->height);

			return (r_child);
		}

		ft::pair<Node*, ft::pair<iterator, bool> >	_insert(Node* n, Node* parent, const value_type& value)
		{
			ft::pair<Node*, ft::pair<iterator, bool> > p;

			if (n == end_node)
			{
				Node* new_node = node_allocator.allocate(1);
				node_allocator.construct(new_node, Node(value, parent, end_node, end_node, 1));
				++nb_elem;
				if (!parent || (parent == end_node->left && comp(value, parent->content)))
					end_node->left = new_node;
				if (!parent || (parent == end_node->parent && comp(parent->content, value)))
					end_node->parent = new_node;
				return (ft::make_pair(new_node, ft::make_pair(iterator(new_node), true)));
			}

			if (comp(value, n->content))
			{
				p = _insert(n->left, n, value);
				n->left = p.first;
			}
			else if (comp(n->content, value))
			{
				p = _insert(n->right, n, value);
				n->right = p.first;
			}
			else
				return (ft::make_pair(n, ft::make_pair(iterator(n), false)));

			n->height = 1 + std::max(n->left->height, n->right->height);

			int balance = _get_balance(n);

			if (balance > 1 && comp(value, n->left->content))
				return (ft::make_pair(_rotate_right(n), p.second));
			if (balance < -1 && comp(n->right->content, value))
				return (ft::make_pair(_rotate_left(n), p.second));
			if (balance > 1 && comp(n->left->content, value))
			{
				n->left = _rotate_left(n->left);
				return (ft::make_pair(_rotate_right(n), p.second));
			}
			if (balance < -1 && comp(value, n->right->content))
			{
				n->right = _rotate_right(n->right);
				return (ft::make_pair(_rotate_left(n), p.second));
			}

			return (ft::make_pair(n, p.second));
		}

		Node*	_erase(Node* n, const value_type& value)
		{
			if (n == end_node)
				return (n);

			if (comp(value, n->content))
				n->left = _erase(n->left, value);
			else if (comp(n->content, value))			
				n->right = _erase(n->right, value);
			else
			{
				Node** n_pos = &root;
				if (n->parent)
					n_pos = (n->parent->left == n ? &n->parent->left : &n->parent->right);
				if (n->left == end_node || n->right == end_node)
				{
					Node* child = (n->left != end_node ? n->left : n->right);
					if (child == end_node)
					{
						*n_pos = end_node;
						Node* replacement = end_node;
						if (n->parent)
							replacement = n->parent;
						if (n == end_node->left)
							end_node->left = replacement;
						if (n == end_node->parent)
							end_node->parent = replacement;
					}
					else
					{
						*n_pos = child;
						child->parent = n->parent;
						if (n == end_node->left)
							end_node->left = child;
						if (n == end_node->parent)
							end_node->parent = child;
					}
				}
				else
				{
					Node* next_inorder = Node::node_leftMost(n->right);
					Node** next_inorder_pos = (next_inorder->parent->left == next_inorder ? &next_inorder->parent->left : &next_inorder->parent->right);
					*next_inorder_pos = next_inorder->right;
					if (*next_inorder_pos != end_node)
						(*next_inorder_pos)->parent = next_inorder->parent;
					
					*n_pos = next_inorder;
					next_inorder->parent = n->parent;
					next_inorder->left = n->left;
					if (n->left != end_node)
						n->left->parent = next_inorder;
					next_inorder->right = n->right;
					if (n->right != end_node)
						n->right->parent = next_inorder;
				}
				node_allocator.destroy(n);
				node_allocator.deallocate(n, 1);
				n = *n_pos;
				--nb_elem;
			}

			if (n == end_node)
				return (n);

			n->height = 1 + std::max(n->left->height, n->right->height);
			
			int balance = _get_balance(n);

			if (balance > 1 && _get_balance(n->left) >= 0)
				return (_rotate_right(n));

			if (balance > 1 && _get_balance(n->left) < 0)
			{
				n->left = _rotate_left(n->left);
				return (_rotate_right(n));
			}

			if (balance < -1 && _get_balance(n->right) <= 0)
				return (_rotate_left(n));
			
			if (balance < -1 && _get_balance(n->right) > 0)
			{
				n->right = _rotate_right(n->right);
				return (_rotate_left(n));
			}
			return (n);
		}

		void _print_newick(std::stringstream& ss, Node* n) const
		{
			if (n == end_node)
				return ;

			if (n->left != end_node || n->right != end_node)
				ss << "(";
			_print_newick(ss, n->left);
			if (n->left != end_node && n->right != end_node)
				ss << ",";
			_print_newick(ss, n->right);
			if (n->left != end_node || n->right != end_node)
				ss << ")";
			ss << n->content << ":" << n->height;
		}

		Node*	_find(Node* n, const value_type& value)
		{
			if (n == end_node)
				return (end_node);
			if (!comp(value, n->content) && !comp(n->content, value))
				return (n);
			Node* result;
			if ((result = _find(n->left, value)) != end_node)
				return (result);
			if ((result = _find(n->right, value)) != end_node)
				return (result);
			return (end_node);
		}

		const Node*	_find(const Node* n, const value_type& value) const
		{
			if (n == end_node)
				return (end_node);
			if (!comp(value, n->content) && !comp(n->content, value))
				return (n);
			const Node* result;
			if ((result = _find(n->left, value)) != end_node)
				return (result);
			if ((result = _find(n->right, value)) != end_node)
				return (result);
			return (end_node);
		}

		int _get_balance(Node* n)
		{ return (n->left->height - n->right->height); }

		void _clear(Node* n)
		{
			if (n == end_node)
				return ;
			_clear(n->left);
			_clear(n->right);
			Node** delete_pos = &root;
			if (n->parent)
				delete_pos = (n->parent->left == n ? &n->parent->left : &n->parent->right);
			*delete_pos = end_node;
			node_allocator.destroy(n);
			node_allocator.deallocate(n, 1);
			--nb_elem;
		}

		Node*				root;
		value_compare		comp;
		Node*				end_node;
		node_allocator_type node_allocator;
		int 				nb_elem;
	};

	template<class T, class Compare, class Alloc>
	void swap(BinarySearchTree<T, Compare, Alloc>& lhs, BinarySearchTree<T, Compare, Alloc>& rhs)
	{ lhs.swap(rhs); }

}

#endif // BINARY_SEARCH_TREE_HPP