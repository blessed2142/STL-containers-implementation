#ifndef TREE_HPP
#define TREE_HPP
#define RED true
#define BLACK false
// #include "map_iterator.hpp"


namespace ft {

template <typename Key, typename T>
class Node
{
	public:
		ft::pair<const Key, T> data_;
		Node	*p_;
		Node	*left_;
		Node	*right_;
		bool	red_;
		Node() : data_(ft::pair<Key, T> (Key(), T())), p_(NULL), left_(NULL), right_(NULL), red_(true) {}
		Node(const ft::pair<Key, T> &val) : data_(val), p_(NULL), left_(NULL), right_(NULL), red_(true) {}
		Node(const Node &other) :	data_(other.data_),
									p_(other.p_),
									left_(other.left_),
									right_(other.right_),
									red_(other.red_) {}
		Node &operator=(const Key &other)
		{
			if (this != &other)
			{
				this->data_ = other.data_;
				this->p_ = other.p_;
				this->left_ = other.left_;
				this->right_ = other.right_;
				this->red_ = other.red_;
			}
			return (*this);
		}
		~Node() {}
};

template<typename Key, typename T, typename Alloc = std::allocator< ft::pair<Key, T> >, typename Compare = std::less<Key> >
class Tree
{
	public:

		typedef typename Alloc::template
		rebind< Node<Key, T> >::other node_allocator;
		typedef typename node_allocator::pointer node_pointer;
		Node<Key, T> *root_;
		Node<Key, T> *TNILL_;
		node_allocator alloc_;
		Compare			comp_;

	private:

		Tree() : alloc_(Alloc()), comp_(Compare())
		{
			TNILL_ = alloc_.allocate(1);
			alloc_.construct(TNILL_, Node<Key, T>());
			TNILL_->red_ = false;
			root_ = TNILL_;
		}

	public:

		Tree(const Compare &comp) : alloc_(Alloc()), comp_(comp)
		{
			try { TNILL_ = alloc_.allocate(1); }
			catch(std::bad_alloc &ex) {std::cerr << "exp. caught during allocation\n"; throw ;}
			try { alloc_.construct(TNILL_, Node<Key, T>()); }
			catch(...) {std::cerr << "MAP NOT CREATED!\n"; alloc_.deallocate(TNILL_, 1); throw ;}
			TNILL_->red_ = false;
			root_ = TNILL_;
		}
		Tree(const Tree &other) : alloc_(other.alloc_), comp_(other.comp_)
		{
			try {this->TNILL_ = alloc_.allocate(1);}
			catch(std::bad_alloc &ex) {std::cerr << "exp. caught during allocation\n"; throw ;}
			try {alloc_.construct(this->TNILL_, Node<Key, T>());}
			catch(...) {std::cerr << "MAP NOT CREATED!\n"; alloc_.deallocate(TNILL_, 1); throw ;}
			this->TNILL_->red_ = false;
			if (other.root_ == other.TNILL_)
				this->root_ = this->TNILL_;
			else
			{
				this->root_ = this->TNILL_;
				node_pointer x = other.rb_minimum(other.root_);
				this->insert(ft::pair<Key, T> (x->data_.first, x->data_.second));
				for ( ; x != other.TNILL_ ; )
				{
					x = other.successor(x);
					this->insert(ft::pair<Key, T> (x->data_.first, x->data_.second));
				}
			}
		}

		~Tree()
		{
			for ( ; root_ != TNILL_ ; )
				rb_delete(root_);
			root_ = NULL;
			if (TNILL_ != NULL)
			{
				alloc_.destroy(TNILL_);
				alloc_.deallocate(TNILL_, 1);
			}
			TNILL_ = NULL;
		}

		Tree &operator=(const Tree &other)
		{
			if (this != &other)
			{
				this->~Tree();
				this->TNILL_ = alloc_.allocate(1);
				alloc_.construct(this->TNILL_, Node<Key, T>());
				this->TNILL_->red_ = false;
				if (other.root_ == other.TNILL_)
					this->root_ = this->TNILL_;
				else
				{
					this->root_ = this->TNILL_;
					node_pointer x = other.rb_minimum(other.root_);
					this->insert(ft::pair<Key, T> (x->data_.first, x->data_.second));
					for ( ; x != other.TNILL_ ; )
					{
						x = other.successor(x);
						this->insert(ft::pair<Key, T> (x->data_.first, x->data_.second));
					}
				}
				this->alloc_ = other.alloc_;
				this->comp_ = other.comp_;
			}
			return (*this);
		}

		void left_rotate(node_pointer x)
		{
			node_pointer y = x->right_;
			x->right_ = y->left_;
			if (y->left_ != TNILL_)
				y->left_->p_ = x;
			y->p_ = x->p_;
			if (x->p_ == TNILL_)
				root_ = y;
			else if (x == x->p_->left_)
				x->p_->left_ = y;
			else 
				x->p_->right_ = y;
			y->left_ = x;
			x->p_ = y;
		}

		void right_rotate(node_pointer y)
		{
			node_pointer x = y->left_;
			y->left_ = x->right_;

			if (x->right_ != TNILL_)
				x->right_->p_ = y;
			x->p_ = y->p_;
			if (y->p_ == TNILL_)
				root_ = x;
			else if (y == y->p_->right_)
				y->p_->right_ = x;
			else 
				y->p_->left_ = x;
			x->right_ = y;
			y->p_ = x;
		}
		// void insert(const Key &key, const T &t)
		// {
		// 	ft::pair<Key, T>
		// }

		int insert(const ft::pair<Key, T> &val)
		{
			node_pointer p = NULL;
			try {p = alloc_.allocate(1);}
			catch(std::bad_alloc &ex) { std::cerr << "exp. caught during allocation in insert.\n";
			throw std::exception(); }
			alloc_.construct(p, Node<Key, T>(val));
			return (insert(p));
		}

		int insert(node_pointer z)
		{
			// std::cout << "HERE: " << comp_(5, 4) << std::endl;
			node_pointer y = TNILL_;
			node_pointer x = root_;
			if (z->data_.first == search(z->data_.first)->data_.first &&
			search(z->data_.first) != TNILL_)
			{
				alloc_.destroy(z);
				alloc_.deallocate(z, 1);
				return (0);
			}
			while (x != TNILL_)
			{
				y = x;
				if (comp_(z->data_, x->data_))
					x = x->left_;
				else
					x = x->right_;
			}
			z->p_= y;
			if (y == TNILL_)
				root_ = z;
			else if (comp_(z->data_, y->data_))
				y->left_ = z;
			else 
				y->right_ = z;
			z->left_ = TNILL_;
			z->right_ = TNILL_;
			z->red_ = true;
			return (insert_fixup(z));
		}

		int insert_fixup(node_pointer z)
		{
			while (z->p_->red_ == RED)
			{
				if (z->p_ == z->p_->p_->left_)
				{
					node_pointer y = z->p_->p_->right_;
					if (y->red_ == RED)
					{
			 			z->p_->red_ = BLACK;
						y->red_ = BLACK;
						z->p_->p_->red_ = RED;
						z = z->p_->p_;
					}
					else
					{
						if (z == z->p_->right_)
						{
							z = z->p_;
							left_rotate(z);
						}
						z->p_->red_ = BLACK;
						z->p_->p_->red_ = RED;
						right_rotate(z->p_->p_);
					}
				}
				else
				{
					node_pointer y = z->p_->p_->left_;
					if (y->red_ == RED)
					{
			 			z->p_->red_ = BLACK;
						y->red_ = BLACK;
						z->p_->p_->red_ = RED;
						z = z->p_->p_;
					}
					else
					{
						if (z == z->p_->left_)
						{
							z = z->p_;
							right_rotate(z);
						}
						z->p_->red_ = BLACK;
						z->p_->p_->red_ = RED;
						left_rotate(z->p_->p_);
					}
				}
			}
			root_->red_ = BLACK;
			return(1);
		}

		void transplant(node_pointer u, node_pointer v)
		{
			if (u->p_ == TNILL_)
				root_ = v;
			else if (u == u->p_->left_)
				u->p_->left_ = v;
			else
				u->p_->right_ = v;
			v->p_ = u->p_;
		}

		bool rb_delete(node_pointer z)
		{
			if (z == TNILL_)
				return false;
			node_pointer x = TNILL_;
			node_pointer y = z;
			bool y_orig_color = y->red_;
			if (z->left_ == TNILL_)
			{
				x = z->right_;
				transplant(z, z->right_);
			}
			else if (z->right_ == TNILL_)
			{
				x = z->left_;
				transplant(z, z->left_);
			}
			else
			{
				y = rb_minimum(z->right_);
				y_orig_color = y->red_;
				x = y->right_;
				if (y->p_ == z)
					x->p_ = y;
				else
				{
					transplant(y, y->right_);
					y->right_ = z->right_;
					y->right_->p_ = y;
				}
				transplant(z, y);
				y->left_ = z->left_;
				y->left_->p_ = y;
				y->red_ = z->red_;
			}
			if (y_orig_color == BLACK)
				rb_delete_fixup(x);
			alloc_.destroy(z);
			alloc_.deallocate(z, 1);
			return (true);
		}

		void rb_delete_fixup(node_pointer x)
		{
			node_pointer w;

			while (x != root_ && x->red_ == BLACK)
			{
				if (x == x->p_->left_)
				{
					w = x->p_->right_;
					if (w->red_ == RED)
					{
						w->red_ = BLACK;
						x->p_->red_ = RED;
						left_rotate(x->p_);
						w = x->p_->right_;
					}
					if (w->left_->red_ == BLACK && w->right_->red_ == BLACK)
					{
						w->red_ = RED;
						x = x->p_;
					}
					else
					{
						if (w->right_->red_ == BLACK)
						{
							w->left_->red_ = BLACK;
							w->red_ = RED;
							right_rotate(w);
							w = x->p_->right_;
						}
						w->red_ = x->p_->red_;
						x->p_->red_ = BLACK;
						w->right_->red_ = BLACK;
						left_rotate(x->p_);
						x = root_;
					}
				}
				else
				{
					w = x->p_->left_;
					if (w->red_ == RED)
					{
						w->red_ = BLACK;
						x->p_->red_ = RED;
						right_rotate(x->p_);
						w = x->p_->left_;
					}
					if (w->right_->red_ == BLACK && w->left_->red_ == BLACK)
					{
						w->red_ = RED;
						x = x->p_;
					}
					else
					{
						if (w->left_->red_ == BLACK)
						{
							w->right_->red_ = BLACK;
							w->red_ = RED;
							left_rotate(w);
							w = x->p_->left_; //
						}
						w->red_ = x->p_->red_;
						x->p_->red_ = BLACK;
						w->left_->red_ = BLACK;
						right_rotate(x->p_);
						x = root_;
					}
				}
			}
			x->red_ = BLACK;
		}



		void printer(node_pointer x)
		{
			if (x != TNILL_)
			{
				printer(x->left_);
				printer(x->right_);
			}
		}

		node_pointer search(const Key &k)
		{
			node_pointer x = root_;
			ft::pair<Key, T> k_pair (k, T());
			while (x != TNILL_ && k != x->data_.first)
			{
				// if (k < x->data_.first)
				// if (comp_(k, x->data_.first))
				if (comp_(k_pair, x->data_))
					x = x->left_;
				else
					x = x->right_;
			}
			return (x);
		}

		node_pointer search(const Key &k) const
		{
			node_pointer x = root_;
			ft::pair<Key, T> k_pair (k, T());
			while (x != TNILL_ && k != x->data_.first)
			{
				// if (k < x->data_.first)
				if (comp_(k_pair, x->data_))
					x = x->left_;
				else
					x = x->right_;
			}
			return (x);
		}

		node_pointer rb_minimum(node_pointer x)
		{
			while (x->left_ != TNILL_ && x->left_ != NULL)
				x = x->left_;
			return (x);
		}
		node_pointer rb_minimum(node_pointer x) const
		{
			while (x->left_ != TNILL_ && x->left_ != NULL)
				x = x->left_;
			return (x);
		}

		node_pointer rb_maximum(node_pointer x)
		{
			while (x->right_ != TNILL_ && x->right_ != NULL)
				x = x->right_;
			return (x);
		}
		node_pointer successor(node_pointer x)
		{
			if (x->right_ != TNILL_)
			{
				return (rb_minimum(x->right_));
			}
			node_pointer y = x->p_;
			while (y != TNILL_ && x == y->right_)
			{
				x = y;
				y = y->p_;
			}
			return (y);
		}
		node_pointer predecessor(node_pointer y)
		{
			if (y->left_ != TNILL_)
				return (rb_maximum(y->left_));
			node_pointer x = y->p_;
			while (x != TNILL_ && y == x->left_)
			{
				y = x;
				x = x->p_;
			}
			return (x);
		}

		node_pointer successor(node_pointer x) const
		{
			if (x->right_ != TNILL_)
			{
				return (rb_minimum(x->right_));
			}
			node_pointer y = x->p_;
			while (y != TNILL_ && x == y->right_)
			{
				x = y;
				y = y->p_;
			}
			return (y);
		}
		node_pointer predecessor(node_pointer y) const
		{
			if (y->left_ != TNILL_)
				return (rb_maximum(y->left_));
			node_pointer x = y->p_;
			while (x != TNILL_ && y == x->left_)
			{
				y = x;
				x = x->p_;
			}
			return (x);
		}

		Compare value_comp() const
		{
			return (this->comp_);
		}
};

}
#endif
