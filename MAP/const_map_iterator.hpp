#ifndef CONST_MAP_ITERATOR
#define CONST_MAP_ITERATOR
#include "../UTILS/iterator_traits.hpp"
// #include "nullptr.hpp"
#include "pair.hpp"

namespace ft {


template <typename Key, typename T, typename Iter>
class const_map_iterator
{
	public:

		typedef Iter															iterator_type;
		typedef ft::bidirectional_iterator_tag									iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;

	// private:

		typedef Node<Key, T>* node_pointer;
		node_pointer	ptr_;
		node_pointer	root_;
		node_pointer	TNILL_;

	public:


		const_map_iterator() : ptr_(NULL), root_(NULL), TNILL_(NULL) {}

		const_map_iterator(node_pointer ptr, node_pointer root, node_pointer TNILL) : ptr_(ptr), root_(root), TNILL_(TNILL) {}
		// map_iterator(node_pointer ptr) : ptr_(ptr) {}


		template <typename U> 
		const_map_iterator(const map_iterator<Key, T, U> &other) : ptr_(other.ptr_), root_(other.root_), TNILL_(other.TNILL_) {}

		const_map_iterator(const const_map_iterator &other) : ptr_(other.ptr_), root_(other.root_), TNILL_(other.TNILL_) {}

		~const_map_iterator() {}

		const_map_iterator &operator=(const const_map_iterator &other) {
			if (this != &other)
			{
				this->ptr_ = other.ptr_;
				this->root_ = other.root_;
				this->TNILL_ = other.TNILL_;
			}
			return (*this);
		}

		value_type operator*()
		{
			return (ptr_->data_);
		}

		// pointer operator->()
		// {
		// 	pointer p = &ptr_->data_;
		// 	return (p);
		// }

		pointer operator->() const
		{
			pointer p = &ptr_->data_;
			return (p);
		}

		// void print_root()
		// {
		// 	if (tree_->root_ != tree_->TNILL_)
		// 		std::cout << tree_->root_->data_.first << std::endl;
		// }

		const_map_iterator &operator++()
		{
			if (this->ptr_ == NULL || this->ptr_ == this->TNILL_)
			{
				this->ptr_ = it_minimum(this->root_);
			}
			else
			{
				this->ptr_ = it_successor(this->ptr_);
			}
			return (*this);
		}

		const_map_iterator &operator--()
		{
			if (this->ptr_ == NULL || this->ptr_ == this->TNILL_)
				this->ptr_ = it_maximum(this->root_);
			else
				this->ptr_ = it_predecessor(this->ptr_);
			return (*this);
		}

		const_map_iterator operator++(int)
		{
			const_map_iterator ret(*this);
			if (this->ptr_ == NULL || this->ptr_ == this->TNILL_)
				this->ptr_ = it_minimum(this->root_);
			else
				this->ptr_ = it_successor(this->ptr_);
			return (ret);
		}

		const_map_iterator operator--(int)
		{
			const_map_iterator ret(*this);
			if (this->ptr_ == NULL || this->ptr_ == this->TNILL_)
				this->ptr_ = it_maximum(this->root_);
			else
				this->ptr_ = it_predecessor(this->ptr_);
			return (ret);
		}

		node_pointer it_minimum(node_pointer x) const
		{
			while (x->left_ != TNILL_ && x->left_ != NULL)
				x = x->left_;
			return (x);
		}

		node_pointer it_maximum(node_pointer x) const
		{
			while (x->right_ != TNILL_ && x->right_ != NULL)
				x = x->right_;
			return (x);
		}

		node_pointer it_successor(node_pointer x) const
		{
			if (x->right_ != TNILL_)
			{
				return (it_minimum(x->right_));
			}
			node_pointer y = x->p_;
			while (y != TNILL_ && x == y->right_)
			{
				x = y;
				y = y->p_;
			}
			return (y);
		}

		node_pointer it_predecessor(node_pointer y) const
		{
			if (y->left_ != TNILL_)
				return (it_maximum(y->left_));
			node_pointer x = y->p_;
			while (x != TNILL_ && y == x->left_)
			{
				y = x;
				x = x->p_;
			}
			return (x);
		}

		bool operator==(const const_map_iterator &other)
		{
			return (this->ptr_ == other.ptr_);
		}
		bool operator!=(const const_map_iterator &other)
		{
			return (!(this->ptr_ == other.ptr_));
		}

		node_pointer data() const { return (this->ptr_); }
};

}
#endif

