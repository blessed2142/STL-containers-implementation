#ifndef MAP_HPP
#define MAP_HPP
#include "pair.hpp"
#include "../UTILS/iterator_traits.hpp"
#include "tree.hpp"
#include "map_iterator.hpp"
#include <algorithm>
#include "const_map_iterator.hpp"
#include "reverse_map_iterator.hpp"
#include "const_reverse_map_iterator.hpp"
#include <stdexcept>
#include "../UTILS/equal.hpp"

namespace ft {

template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator<pair<const Key,T> >    // map::allocator_type
           >
class map
{
	public:

		typedef	Key																		key_type;
		typedef	T																		mapped_type;
		typedef	pair<const key_type, mapped_type>										value_type;
		typedef	Compare																	key_compare;
		typedef	Alloc																	allocator_type;
		typedef	typename allocator_type::reference										reference;
		typedef	typename allocator_type::const_reference								const_reference;
		typedef	typename allocator_type::pointer										pointer;
		typedef	typename allocator_type::const_pointer									const_pointer;
		typedef	size_t																	size_type;
		typedef	map_iterator<key_type, mapped_type, value_type*>						iterator;
		typedef	const_map_iterator<key_type, mapped_type, const value_type*>			const_iterator;
		typedef	reverse_map_iterator<key_type, mapped_type, value_type*>				reverse_iterator;
		typedef	const_reverse_map_iterator<key_type, mapped_type, const value_type*>	const_reverse_iterator;
		typedef pair<iterator, bool> insert_pair;

	class value_compare : std::binary_function<value_type,value_type,bool>
	{
		friend class map;
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}
		public:

		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};
	private:


		allocator_type												alloc_;
		key_compare													comp_;
		size_type													size_;
		Tree<key_type, mapped_type, allocator_type, value_compare>	map_tree_; 

	public:

/*____________________CONSTRUCTORS_&&_DESCTRUCTOR____________________*/

		explicit map (const key_compare& comp = key_compare(),
		              const allocator_type& alloc = allocator_type()) : alloc_(alloc),
					  													comp_(comp),
																		size_(0),
		map_tree_(Tree<key_type, mapped_type, allocator_type, value_compare>(key_compare())) {}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) :	alloc_(alloc),
															comp_(comp),
															size_(0), 
		map_tree_(Tree<key_type, mapped_type, allocator_type, value_compare>(key_compare()))
		{
			insert(first, last);
		}

		map (const map& x) :	alloc_(x.alloc_),
								comp_(x.comp_),
								size_(x.size_),
								map_tree_(x.map_tree_) {}

		~map() {}

/*____________________ASIGNMENT_OPERATOR____________________*/
		map &operator=(const map &other)
		{
			if (this != &other)
			{
				this->map_tree_ = other.map_tree_;
				this->alloc_ = other.alloc_;
				this->comp_ = other.comp_;
				this->size_ = other.size_;
			}
			return (*this);
		}

/*____________________ITERATORS____________________*/
		iterator begin()
		{

			return iterator(map_tree_.rb_minimum(map_tree_.root_),
			map_tree_.root_, map_tree_.TNILL_);
		}

		iterator end()
		{
			iterator ret(map_tree_.TNILL_, map_tree_.root_, map_tree_.TNILL_);
			return (ret);
		}

		const_iterator begin() const
		{
			return const_iterator(map_tree_.rb_minimum(map_tree_.root_),
			map_tree_.root_, map_tree_.TNILL_);
		}



		const_iterator end() const
		{
			const_iterator ret(map_tree_.TNILL_, map_tree_.root_,
			map_tree_.TNILL_);
			return (ret);
		}

		reverse_iterator rbegin()
		{
			// reverse_iterator ret(map_tree_.TNILL_, map_tree_.root_, map_tree_.TNILL_);
			return reverse_iterator(map_tree_.rb_maximum(map_tree_.root_), map_tree_.root_, map_tree_.TNILL_);
		}

		reverse_iterator rend()
		{
			reverse_iterator ret(map_tree_.TNILL_, map_tree_.root_, map_tree_.TNILL_);
			return reverse_iterator(ret);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(map_tree_.rb_maximum(map_tree_.root_), map_tree_.root_, map_tree_.TNILL_);
		}

		const_reverse_iterator rend() const
		{
			const_reverse_iterator ret(map_tree_.TNILL_, map_tree_.root_, map_tree_.TNILL_);
			return const_reverse_iterator(ret);
		}

/*____________________CAPACITY____________________*/

		bool empty() const
		{
			return (!this->size_);
		}

		size_type size() const { return (this->size_); }

		size_type max_size() const
		{
			return (this->map_tree_.alloc_.max_size());
		}

/*____________________ELEMENT_ACCESS____________________*/

		mapped_type& operator[] (const key_type& k)
		{
			this->insert(ft::pair<key_type, mapped_type> (k, mapped_type()));
			Node<key_type, mapped_type> *x = map_tree_.search(k);
			return (x->data_.second);
		}

		mapped_type& at (const key_type& k)
		{
			Node<key_type, mapped_type> *x = map_tree_.TNILL_;
			x = map_tree_.search(k);
			if (x == map_tree_.TNILL_)
				throw std::out_of_range("out");
			else
				return (x->data_.second);
		}

		const mapped_type& at (const key_type& k) const
		{
			Node<key_type, mapped_type> *x = map_tree_.TNILL_;
			x = map_tree_.search(k);
			if (x == map_tree_.TNILL_)
				throw std::out_of_range("out");
			else
				return (x->data_.second);
		}

/*____________________MODIFIERS____________________*/

		insert_pair insert(const value_type& val)
		{
			int res_b = -1;
			try { res_b = map_tree_.insert(val); }
			catch (std::exception &ex) {std::cout << "excep. is caught during insertion\n"; throw;}
			if (res_b == 1)
				++size_;
			iterator res_it = iterator(map_tree_.search(val.first), map_tree_.root_, map_tree_.TNILL_);
			insert_pair ret(res_it, static_cast<bool>(res_b));
			return (ret);
		}

		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			int yes = 0;
			try {yes = map_tree_.insert(val);}
			catch (std::exception &ex) {std::cout << "excep. is caught during insertion\n"; throw;}
			if (yes)
				++size_;
			iterator res_it = iterator(map_tree_.search(val.first), map_tree_.root_, map_tree_.TNILL_);
			return (res_it);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			int yes = 0;
			for ( ; first != last; ++first)
			{
				try {yes = map_tree_.insert(*first);}
				catch (std::exception &ex) {std::cout << "excep. is caught during insertion\n"; throw;}
				if (yes)
					++size_;
			}
		}


		void erase (iterator position)
		{
			bool yes = false;
			yes = map_tree_.rb_delete(map_tree_.search(position->first));
			if (yes)
				--size_;
		}

		size_type erase (const key_type& k)
		{
			Node<key_type, mapped_type> *x = map_tree_.search(k);
			if (x != map_tree_.TNILL_)
			{
				if (map_tree_.rb_delete(map_tree_.search(k)))
					--size_;
				return (1);
			}
			return (0);
		}

		void erase (iterator first, iterator last)
		{
			while (first != last)
				this->erase(first++);
		}

		void swap (map& x)
		{
			std::swap(alloc_, x.alloc_);
			std::swap(comp_, x.comp_);
			std::swap(size_, x.size_);
			std::swap(map_tree_.alloc_, x.map_tree_.alloc_);
			std::swap(map_tree_.TNILL_, x.map_tree_.TNILL_);
			std::swap(map_tree_.root_, x.map_tree_.root_);

		}

		void clear()
		{
			for ( ; map_tree_.root_ != map_tree_.TNILL_ ; )
				map_tree_.rb_delete(map_tree_.root_);
			this->size_ = 0;
		}

/*____________________OBSERVERS____________________*/

		key_compare key_comp() const { return (this->comp_); }
		value_compare value_comp() const { return (map_tree_.value_comp()); }

/*____________________OPERATIONS____________________*/

		iterator find (const key_type& k)
		{
			iterator ret(map_tree_.search(k), map_tree_.root_, map_tree_.TNILL_);
			return(ret);
		}

		const_iterator find (const key_type& k) const
		{
			iterator ret(map_tree_.search(k), map_tree_.root_, map_tree_.TNILL_);
			return(ret);
		}

		size_type count (const key_type& k) const
		{
			if (map_tree_.search(k) != map_tree_.TNILL_)
				return (1);
			return (0);
		}

		iterator lower_bound (const key_type& k)
		{
			bool left = false;
			Node<key_type, mapped_type> *x = map_tree_.root_;
			Node<key_type, mapped_type> *y = map_tree_.root_;
			while (x != map_tree_.TNILL_ && k != x->data_.first) // ??
			{
				y = x;
				if (comp_(k, x->data_.first))
				{
					left = true;
					x = x->left_;
				}
				else
				{
					left = false;
					x = x->right_;
				}
			}
			if (!comp_(k, x->data_.first) && !comp_(x->data_.first, k) && x != map_tree_.TNILL_)
				return(iterator(x, map_tree_.root_, map_tree_.TNILL_));
			else
			{
				if (left == true)
					return(iterator(y, map_tree_.root_, map_tree_.TNILL_));
				return(iterator(map_tree_.successor(y), map_tree_.root_, map_tree_.TNILL_));
			}
		}

		const_iterator lower_bound (const key_type& k) const
		{
			bool left = false;
			Node<key_type, mapped_type> *x = map_tree_.root_;
			Node<key_type, mapped_type> *y = map_tree_.root_;
			while (x != map_tree_.TNILL_ && k != x->data_.first) // ??
			{
				y = x;
				if (comp_(k, x->data_.first))
				{
					left = true;
					x = x->left_;
				}
				else
				{
					left = false;
					x = x->right_;
				}
			}
			if (!comp_(k, x->data_.first) && !comp_(x->data_.first, k) && x != map_tree_.TNILL_)
				return(iterator(x, map_tree_.root_, map_tree_.TNILL_));
			else
			{
				if (left == true)
					return(iterator(y, map_tree_.root_, map_tree_.TNILL_));
				return(iterator(map_tree_.successor(y), map_tree_.root_, map_tree_.TNILL_));
			}
		}

		iterator upper_bound (const key_type& k)
		{
			bool left = false;
			Node<key_type, mapped_type> *x = map_tree_.root_;
			Node<key_type, mapped_type> *y = map_tree_.root_;
			while (x != map_tree_.TNILL_ && k != x->data_.first) // ?
			{
				y = x;
				// if (k < x->data_.first)
				if (comp_(k, x->data_.first))
				{
					left = true;
					x = x->left_;
				}
				else
				{
					left = false;
					x = x->right_;
				}
			}
			if (!comp_(k, x->data_.first) && !comp_(x->data_.first, k) && x != map_tree_.TNILL_)
				return(iterator(map_tree_.successor(x), map_tree_.root_, map_tree_.TNILL_));
			else
			{
				if (left == true)
					return(iterator(y, map_tree_.root_, map_tree_.TNILL_));
				return(iterator(map_tree_.successor(y), map_tree_.root_, map_tree_.TNILL_));
			}
		}

		const_iterator upper_bound (const key_type& k) const
		{
			bool left = false;
			Node<key_type, mapped_type> *x = map_tree_.root_;
			Node<key_type, mapped_type> *y = map_tree_.root_;
			while (x != map_tree_.TNILL_ && k != x->data_.first) // ?
			{
				y = x;
				if (comp_(k, x->data_.first))
				{
					left = true;
					x = x->left_;
				}
				else
				{
					left = false;
					x = x->right_;
				}
			}
			if (!comp_(k, x->data_.first) && !comp_(x->data_.first, k) && x != map_tree_.TNILL_)
				return(iterator(map_tree_.successor(x), map_tree_.root_, map_tree_.TNILL_));
			else
			{
				if (left == true)
					return(iterator(y, map_tree_.root_, map_tree_.TNILL_));
				return(iterator(map_tree_.successor(y), map_tree_.root_, map_tree_.TNILL_));
			}
		}

		pair<iterator,iterator> equal_range (const key_type& k)
		{
			return (pair<iterator, iterator> (lower_bound(k), upper_bound(k)));
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return (pair<const_iterator, const_iterator> (lower_bound(k), upper_bound(k)));
		}

		allocator_type get_allocator() const
		{
			allocator_type ret = allocator_type();
			return (ret);
		}

};

template <typename Key, typename T>
bool operator==(const map<Key, T> &lhs, const map<Key, T> &rhs)
{
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && ft::equal(rhs.begin(), rhs.end(), lhs.begin()));
}

template <typename Key, typename T>
bool operator!=(const map<Key, T> &lhs, const map<Key, T> &rhs)
{
	return (!(lhs == rhs));
}

template <typename Key, typename T>
bool operator<(const map<Key, T> &lhs, const map<Key, T> &rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename Key, typename T>
bool operator>(const map<Key, T> &lhs, const map<Key, T> &rhs)
{
	return (rhs < lhs);
}

template <typename Key, typename T>
bool operator<=(const map<Key, T> &lhs, const map<Key, T> &rhs)
{
	return (!(lhs > rhs));
}

template <typename Key, typename T>
bool operator>=(const map<Key, T> &lhs, const map<Key, T> &rhs)
{
	return (!(rhs > lhs));
}
}

#endif
