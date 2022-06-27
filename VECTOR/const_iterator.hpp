#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP
#include "../UTILS/iterator_traits.hpp"
// #include "iterator.hpp"

// ft::vector<int>::const_iterator = ft::vector<int>::<T*>

namespace ft {


template <typename Iter>
class const_iterator
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

		const_iterator() : ptr_() {}
		const_iterator(pointer ptr) : ptr_(ptr) {}
		const_iterator(const const_iterator &other) : ptr_(other.ptr_) {}
		template <typename T>
		const_iterator(const iterator<T> &other) : ptr_(other.data()) {}
		const_iterator &operator=(const const_iterator &other) {
			if (this != &other)
				ptr_ = other.ptr_;
			return (*this);
		}
		~const_iterator() {}
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

		const_iterator	operator+(const const_iterator &other)
		{
			const_iterator ret(this->ptr_ + other.ptr_); // ???? 
			return (ret);
		}
		const_iterator	operator+(difference_type n)
		{
			const_iterator ret(this->ptr_ + n);
			return (ret);
		}
		difference_type	operator-(const const_iterator &other)
		{
			return (this->ptr_ - other.ptr_);
		}
		const_iterator	operator-(difference_type n)
		{
			const_iterator ret(this->ptr_ - n);
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
		const_iterator	&operator++()
		{
			++ptr_;
			return(*this);
		}
		const_iterator	operator++(int)
		{
			const_iterator tmp(*this);
			++ptr_;
			return(tmp);
		}
		const_iterator	&operator--()
		{
			--ptr_;
			return(*this);
		}
		const_iterator	operator--(int)
		{
			const_iterator tmp(*this);
			--ptr_;
			return(tmp);
		}
/*______________________COMPARISON_OPERATORS____________________________*/
		bool		operator==(const const_iterator &other)
		{
			return (this->ptr_ == other.ptr_);
		}
		bool		operator!=(const const_iterator &other)
		{
			return (this->ptr_ != other.ptr_);
		}
		bool		operator<(const const_iterator &other)
		{
			return (this->ptr_ < other.ptr_);
		}
		bool		operator>(const const_iterator &other)
		{
			return (other.ptr_ < this->ptr_);
		}
		bool		operator<=(const const_iterator &other)
		{
			return (!(this->ptr_ > other.ptr_));
		}
		bool		operator>=(const const_iterator &other)
		{
			return (!(other.ptr_ > this->ptr_));
		}

		pointer data() {return(this->ptr_);}
		pointer data() const {return(this->ptr_);}
};


template <typename Iter>
class const_reverse_iterator
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

		const_reverse_iterator() : ptr_() {}
		const_reverse_iterator(pointer ptr) : ptr_(ptr) {}
		const_reverse_iterator(const const_reverse_iterator &other) : ptr_(other.ptr_) {}
		template <typename T>
		const_reverse_iterator(const reverse_iterator<T> &other) : ptr_(other.data()) {}
		const_reverse_iterator &operator=(const const_reverse_iterator &other) {
			if (this != &other)
				ptr_ = other.ptr_;
			return (*this);
		}
		~const_reverse_iterator() {}
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

		const_reverse_iterator	operator+(const const_reverse_iterator &other)
		{
			const_reverse_iterator ret(this->ptr_ - other.ptr_);
			return (ret);
		}
		const_reverse_iterator	operator+(difference_type n)
		{
			const_reverse_iterator ret(this->ptr_ - n);
			return (ret);
		}
		const_reverse_iterator	operator-(const const_reverse_iterator &other)
		{
			const_reverse_iterator ret(this->ptr_ + other.ptr_);
			return (ret);
		}
		const_reverse_iterator	operator-(difference_type n)
		{
			const_reverse_iterator ret(this->ptr_ + n);
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
		const_reverse_iterator	&operator++()
		{
			--ptr_;
			return(*this);
		}
		const_reverse_iterator	operator++(int)
		{
			const_reverse_iterator tmp(*this);
			--ptr_;
			return(tmp);
		}
		const_reverse_iterator	&operator--()
		{
			++ptr_;
			return(*this);
		}
		const_reverse_iterator	operator--(int)
		{
			const_reverse_iterator tmp(*this);
			++ptr_;
			return(tmp);
		}
/*______________________COMPARISON_OPERATORS____________________________*/
		bool		operator==(const const_reverse_iterator &other)
		{
			return (this->ptr_ == other.ptr_);
		}
		bool		operator!=(const const_reverse_iterator &other)
		{
			return (this->ptr_ != other.ptr_);
		}
		bool		operator<(const const_reverse_iterator &other)
		{
			return (this->ptr_ < other.ptr_);
		}
		bool		operator>(const const_reverse_iterator &other)
		{
			return (other.ptr_ < this->ptr_);
		}
		bool		operator<=(const const_reverse_iterator &other)
		{
			return (!(this->ptr_ > other.ptr_));
		}
		bool		operator>=(const const_reverse_iterator &other)
		{
			return (!(other.ptr_ > this->ptr_));
		}

		pointer data() {return(this->ptr_);}
		pointer data() const {return(this->ptr_);}
};
}






#endif
