#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "../UTILS/iterator_traits.hpp"
// #include "const_iterator.hpp"

// ft::vector<int>::iterator = ft::vector<int>::<T*>

namespace ft {

template <typename Iter>
class iterator
{
	public:

		typedef Iter															iterator_type;
		typedef std::random_access_iterator_tag									iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;

	private:

		pointer ptr_;

	public:

		iterator() : ptr_() {}
		iterator(pointer ptr) : ptr_(ptr) {}
		iterator(const iterator &other) : ptr_(other.ptr_) {}
		iterator &operator=(const iterator &other) {
			if (this != &other)
				ptr_ = other.ptr_;
			return (*this);
		}
		~iterator() {}
		reference operator*()
		{
			return (*ptr_);
		}

		reference &operator[](difference_type n)
		{
			return (*(this->ptr_ + n));
		}
		const reference &operator[](difference_type n) const
		{
			return (*(this->ptr_ + n));
		}

/*______________________ARITHMETHIC_OPERATORS____________________________*/

		iterator	operator+(const iterator &other)
		{
			iterator ret(this->ptr_ + other.ptr_); // ???? 
			return (ret);
		}
		iterator	operator+(difference_type n)
		{
			iterator ret(this->ptr_ + n);
			return (ret);
		}
		difference_type	operator-(const iterator &other)
		{
			return (this->ptr_ - other.ptr_);
		}
		iterator	operator-(difference_type n)
		{
			iterator ret(this->ptr_ - n);
			return (ret);
		}
		void		operator+=(difference_type n)
		{
			this->ptr_ += n;
		}
		void		operator-=(difference_type n)
		{
			this->ptr_ -= n;
		}

/*______________________PREINCREMENT_PREDECREMENT____________________________*/
		iterator	&operator++()
		{
			++ptr_;
			return(*this);
		}
		iterator	operator++(int)
		{
			iterator tmp(*this);
			++ptr_;
			return(tmp);
		}
		iterator	&operator--()
		{
			--ptr_;
			return(*this);
		}
		iterator	operator--(int)
		{
			iterator tmp(*this);
			--ptr_;
			return(tmp);
		}
/*______________________COMPARISON_OPERATORS____________________________*/
		bool		operator==(const iterator &other)
		{
			return (this->ptr_ == other.ptr_);
		}
		bool		operator!=(const iterator &other)
		{
			return (this->ptr_ != other.ptr_);
		}
		bool		operator<(const iterator &other)
		{
			return (this->ptr_ < other.ptr_);
		}
		bool		operator>(const iterator &other)
		{
			return (other.ptr_ < this->ptr_);
		}
		bool		operator<=(const iterator &other)
		{
			return (!(this->ptr_ > other.ptr_));
		}
		bool		operator>=(const iterator &other)
		{
			return (!(other.ptr_ > this->ptr_));
		}

		pointer data() {return(this->ptr_);}
		pointer data() const {return(this->ptr_);}
};


template <typename Iter>
class reverse_iterator
{
	public:

		typedef				Iter															iterator_type;
		typedef				std::random_access_iterator_tag									iterator_category;
		typedef typename	ft::iterator_traits<iterator_type>::value_type					value_type;
		typedef typename	ft::iterator_traits<iterator_type>::reference					reference;
		typedef typename	ft::iterator_traits<iterator_type>::pointer						pointer;
		typedef typename	ft::iterator_traits<iterator_type>::difference_type				difference_type;

	private:

		pointer ptr_;

	public:

		reverse_iterator() : ptr_() {}
		reverse_iterator(pointer ptr) : ptr_(ptr) {}
		reverse_iterator(const reverse_iterator &other) : ptr_(other.ptr_) {}
		reverse_iterator &operator=(const reverse_iterator &other) {
			if (this != &other)
				ptr_ = other.ptr_;
			return (*this);
		}
		~reverse_iterator() {}
		reference operator*()
		{
			return (*ptr_);
		}

		reference &operator[](difference_type n) //??
		{
			return (*(this->ptr_ - n));
		}
		const reference &operator[](difference_type n) const //??
		{
			return (*(this->ptr_ - n));
		}

/*______________________ARITHMETHIC_OPERATORS____________________________*/

		reverse_iterator	operator+(const reverse_iterator &other)
		{
			reverse_iterator ret(this->ptr_ - other.ptr_);
			return (ret);
		}
		reverse_iterator	operator+(difference_type n)
		{
			reverse_iterator ret(this->ptr_ - n);
			return (ret);
		}
		reverse_iterator	operator-(const reverse_iterator &other)
		{
			reverse_iterator ret(this->ptr_ + other.ptr_);
			return (ret);
		}
		reverse_iterator	operator-(difference_type n)
		{
			reverse_iterator ret(this->ptr_ + n);
			return (ret);
		}
		void		operator+=(difference_type n)
		{
			this->ptr_ -= n;
		}
		void		operator-=(difference_type n)
		{
			this->ptr_ += n;
		}

/*______________________PREINCREMENT_PREDECREMENT____________________________*/
		reverse_iterator	&operator++()
		{
			--ptr_;
			return(*this);
		}
		reverse_iterator	operator++(int)
		{
			reverse_iterator tmp(*this);
			--ptr_;
			return(tmp);
		}
		reverse_iterator	&operator--()
		{
			++ptr_;
			return(*this);
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator tmp(*this);
			++ptr_;
			return(tmp);
		}
/*______________________COMPARISON_OPERATORS____________________________*/
		bool		operator==(const reverse_iterator &other)
		{
			return (this->ptr_ == other.ptr_);
		}
		bool		operator!=(const reverse_iterator &other)
		{
			return (this->ptr_ != other.ptr_);
		}
		bool		operator<(const reverse_iterator &other)
		{
			return (this->ptr_ < other.ptr_);
		}
		bool		operator>(const reverse_iterator &other)
		{
			return (other.ptr_ < this->ptr_);
		}
		bool		operator<=(const reverse_iterator &other)
		{
			return (!(this->ptr_ > other.ptr_));
		}
		bool		operator>=(const reverse_iterator &other)
		{
			return (!(other.ptr_ > this->ptr_));
		}

		pointer data() {return(this->ptr_);}
		pointer data() const {return(this->ptr_);}
};
}






#endif
