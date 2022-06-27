// catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl; throw; }
#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
#include <exception>
#include <iostream>
#include <alloca.h>
#include <iterator>
#include "iterator.hpp"
#include "const_iterator.hpp"
#include "../UTILS/is_integral.hpp"
#include "../UTILS/enable_if.hpp"

namespace ft {

template < typename T, class Allocator = std::allocator<T> >
class vector
{
	public:

		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef size_t										size_type;
		typedef ft::iterator<pointer>						iterator;
		typedef ft::const_iterator<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<pointer>				reverse_iterator;
		typedef ft::const_reverse_iterator<const_pointer>			const_reverse_iterator;

	private:

		allocator_type	alloc_;
		size_type		capacity_;
		size_type		size_;
		pointer 		arr_;

	public:
/*____________________CONSTRUCTORS____________________*/

		explicit vector (const allocator_type& alloc = allocator_type()) : alloc_(alloc), capacity_(0), size_(0), arr_(NULL) { }
		
		explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) :  alloc_(alloc), capacity_(n), size_(n)
		{
			try { this->arr_ = alloc_.allocate(this->capacity_); }
			catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl; 
			this->capacity_ = 0; this->size_ = 0; throw ;}
			try
			{
				for (size_t i = 0; i < this->size_; ++i)
					alloc_.construct(this->arr_ + i, val);
			}
			catch(...)
			{
				std::cerr << "contruct threw exp.\n";
				for (size_t i = 0; i < this->size_; ++i)
					alloc_.destroy(this->arr_ + i);
				this->size_ = 0;
			}
		}
		
		vector(const vector &other) : alloc_(other.alloc_), capacity_(other.capacity()), size_(other.size())
		{
			try { this->arr_ = alloc_.allocate(other.capacity()); }
			catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl; 
			this->capacity_ = 0; this->size_ = 0; throw ;}
			try
			{
				for (size_t i = 0; i < other.size(); ++i)
					alloc_.construct(this->arr_ + i, other.at(i));
			}
			catch (...)
			{
				std::cerr << "contruct threw exp.\n";
				for (size_t i = 0; i < this->size_; ++i)
					alloc_.destroy(this->arr_ + i);
				this->size_ = 0;
				throw ;
			}
		}
		
		template <typename InputIterator>
		vector (InputIterator first,
				typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type last,
				const allocator_type& alloc = allocator_type())
		{
			typename InputIterator::difference_type n = last - first;
			this->capacity_ = n;
			this->alloc_ = alloc;
			this->size_ = n;
			try { this->arr_ = this->alloc_.allocate(n); }
			catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl;
			this->capacity_ = 0; this->size_ = 0; throw; }
			try
			{
				for (size_t i = 0; first != last; ++first, ++i)
					this->alloc_.construct(this->arr_ + i, *first);
			}
			catch (...)
			{
				std::cerr << "contruct threw exp.\n";
				for (size_t i = 0; i < this->size_; ++i)
					this->alloc_.destroy(this->arr_ + i);
				this->size_ = 0;
				throw;
			}
		}

/*____________________DESTRUCTOR____________________*/

		~vector()
		{
			for (size_t i = 0; i < size_; ++i)
				this->alloc_.destroy(this->arr_ + i);
			this->alloc_.deallocate(this->arr_, this->capacity_);
			this->arr_ = NULL;
		}

/*____________________ASIGNMENT____________________*/

		vector &operator=(const vector &other)
		{
			if (this != &other)
			{
				this->~vector();
				this->alloc_ = other.alloc_;
				this->capacity_ = other.capacity_;
				this->size_ = other.size_;
				try {this->arr_ = alloc_.allocate(this->capacity_);}
				catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl;
				this->size_ = 0 ;this->capacity_ = 0; throw; }
				try {
				for (size_t i = 0; i < size_; ++i)
					this->alloc_.construct(this->arr_ + i, *(other.arr_ + i));
				}
				catch(...)
				{
					std::cerr << "contruct threw exp.\n";
					for (size_t i = 0; i < size_; ++i)
						this->alloc_.destroy(this->arr_ + i);
					this->size_ = 0;
					throw;
				}
			}
			return (*this);
		}

/*____________________ITERATORS____________________*/

		iterator begin() {
			return (this->arr_);
		}
		iterator end() {
			return (this->arr_ + this->size_);
		}
		const_iterator begin() const {
			return (this->arr_);
		}
		const_iterator end() const {
			return (this->arr_ + this->size_);
		}

		reverse_iterator rbegin() {
			return (this->arr_ + this->size_ - 1);
		}
		reverse_iterator rend() {
			return (this->arr_ - 1);
		}
		const_reverse_iterator rbegin() const {
			return (this->arr_ - 1);
		}
		const_reverse_iterator rend() const {
			return (this->arr_ - 1);
		}


/*____________________CAPACITY____________________*/

		size_type size() const { return (size_); }
		size_type max_size() const { return (this->alloc_.max_size()); }
		void resize (size_type n, value_type val = value_type())
		{
			if (n < this->size_)
			{
				for (size_t i = n; i < size_; ++i)
					alloc_.destroy(this->arr_ + i);
				this->size_ = n;
			}
			else if (n > this->size_)
			{
				for (size_t i = this->size_; i < n; ++i)
					push_back(val);
			}
		}
		void reserve (size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("");
			if (n > this->capacity_)
			{
				size_t t_size = this->size_;
				pointer tmp_ = NULL;
				try { tmp_ = alloc_.allocate(n); }
				catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what()
				<< std::endl; throw ; }
				try
				{
					for (size_t i = 0; i < this->size_; ++i)
						alloc_.construct(tmp_ + i, *(this->arr_ + i));
				}
				catch (...)
				{
					std::cerr << "contruct threw exp.\n";
					for (size_t i = 0; i < this->size_; ++i)
						alloc_.destroy(tmp_ + i);
					alloc_.deallocate(tmp_, n);
					throw;
				}
				this->~vector();
				this->size_ = t_size;
				this->capacity_ = n;
				this->arr_ = tmp_;
			}
		}
		size_type capacity() const { return (this->capacity_); }
		bool empty() const { return (size_ == 0); }

/*____________________ELEMENT_ACCESS____________________*/



		reference operator[](size_t n) { return (arr_[n]); }
		
		reference at(size_t n)
		{
			if (n >= static_cast<size_t>(size_))
				throw std::out_of_range("");
			return (arr_[n]);
		}
		
		reference front() {return (this->arr_[0]);}
		reference back() {return (this->arr_[size_ - 1]);}

		const_reference operator[](size_t n) const { return (arr_[n]); }
		const_reference at(size_t n) const
		{
			if (n >= static_cast<size_t>(size_))
					throw std::out_of_range("");
			return (arr_[n]);
		}
		const_reference front() const {return (this->arr_[0]);}
		const_reference back() const {return (this->arr_[size_ - 1]);}

/*____________________MODIFIERS____________________*/

		void assign (size_type n, const value_type& val) // exceptions are needed 
		{
			if (n <= this->capacity_)
			{
				for (size_t i = 0; i < this->size_; ++i)
					this->alloc_.destroy(this->arr_ + i);
				try
				{
					for (size_t i = 0; i < n; ++i)
						this->alloc_.construct(this->arr_ + i, val);
				}
				catch(...)
				{
					std::cerr << "contruct threw exp.\n";
					for (size_t i = 0; i < n; ++i)
						this->alloc_.destroy(this->arr_ + i);
					this->size_ = 0;
					throw ;
				}
				this->size_ = n;
			}
			else if (n > this->capacity_)
			{
				pointer tmp_ = NULL;
				try { tmp_ = alloc_.allocate(n); }
				catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what()
				<< std::endl; throw; return ;}
				try
				{
					for (size_t i = 0; i < n; ++i)
						this->alloc_.construct(tmp_ + i, val);
				}
				catch (...)
				{
					std::cerr << "contruct threw exp.\n";
					for (size_t i = 0; i < n; ++i)
						this->alloc_.destroy(tmp_ + i);
					alloc_.deallocate(tmp_, n);
					throw ;
			
				}
				this->~vector();
				this->capacity_ = n;
				this->size_ = n;
				this->arr_ = tmp_;
			}
		}
		template <class InputIterator>
  		void assign (InputIterator first, 
		typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type last) {

			typename InputIterator::difference_type n = last - first;
			if (static_cast<size_t>(n) <= this->capacity_)
			{
				for (size_t i = 0; i < this->size_; ++i)
					this->alloc_.destroy(this->arr_ + i);
				try
				{
					for (size_t i = 0; i < static_cast<size_t>(n); ++i, ++first)
						this->alloc_.construct(this->arr_ + i, *first);
				}
				catch(...)
				{
					std::cerr << "contruct threw exp.\n";
					for (size_t i = 0; i < this->size_; ++i)
						this->alloc_.destroy(this->arr_ + i);
					this->size_ = 0;
					throw ;
				}
				this->size_ = n;
			}
			else if (static_cast<size_t>(n) > this->capacity_)
			{
				pointer tmp_ = NULL;
				try { tmp_ = alloc_.allocate(static_cast<size_t>(n)); }
				catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what()
				<< std::endl; throw; return ;}
				try
				{
					for (size_t i = 0; i < static_cast<size_t>(n); ++i, ++first)
						this->alloc_.construct(tmp_ + i, *first);
				}
				catch(...)
				{
					std::cerr << "contruct threw exp.\n";
					for (size_t i = 0; i < static_cast<size_t>(n); ++i)
						this->alloc_.destroy(tmp_ + i);
					alloc_.deallocate(tmp_, n);
					throw ;
				}
				this->~vector();
				this->capacity_ = static_cast<size_t>(n);
				this->size_ = static_cast<size_t>(n);
				this->arr_ = tmp_;
			}
		}


		void push_back(const value_type& val)
		{
			if (this->capacity_ == 0)
			{
				if (this->arr_ != NULL)
					this->alloc_.deallocate(this->arr_, this->capacity_);
				++this->capacity_;
				try { this->arr_ = alloc_.allocate(this->capacity_); } 
				catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl; 
				this->arr_ = NULL; this->capacity_ = 0; throw; }
				try
				{
					alloc_.construct(this->arr_, val);
				}
				catch(...)
				{
					std::cerr << "contruct threw exp.\n";
					alloc_.destroy(this->arr_);
					this->size_ = 0;
					this->arr_ = NULL;
					throw ;
				}
				++this->size_;
			}
			else if (this->size_ < this->capacity_)
			{
				try
				{
					alloc_.construct(this->arr_ + this->size_, val);
				}
				catch (...)
				{
					std::cerr << "contruct threw exp.\n";
					alloc_.destroy(this->arr_ + this->size_);
					throw ;
				}
				++this->size_;
			}
			else if (this->size_ == this->capacity_)
			{
				pointer tmp = NULL;
				try { tmp = alloc_.allocate(this->capacity_ * 2); }
				catch(std::bad_alloc &ex) { std::cerr << "bad_alloc caught: " << ex.what() << std::endl; throw; } 
				size_t t_cap = this->capacity_;
				size_t t_size = this->size_;
				try
				{
					for (size_t i = 0; i < this->size_; ++i)
						alloc_.construct(tmp + i, *(this->arr_ + i));
					alloc_.construct(tmp + t_size, val);
				}
				catch(...)
				{
					std::cerr << "contruct threw exp.\n";
					for (size_t i = 0; i < this->size_; ++i)
						alloc_.destroy(tmp + i);
					alloc_.destroy(tmp + t_size);
					alloc_.deallocate(tmp, t_cap);
					throw ;
				}
				this->~vector();
				this->capacity_ = t_cap * 2;
				this->size_ = t_size;
				this->arr_ = tmp;
				++this->size_;
			}
		}

		void pop_back(void)
		{
			alloc_.destroy(this->arr_ + this->size_);
			--this->size_;
		}

		iterator insert (iterator position, const value_type& val)
		{
			typename ft::vector<T>::iterator::difference_type diff = position - this->begin();
			size_t new_pos = diff;
			size_t curr_size = this->size_;
			if (this->size_ < this->capacity_)
			{
				try
				{
					for ( ; curr_size > new_pos; --curr_size)
					{
						this->alloc_.destroy(this->arr_ + curr_size);
						this->alloc_.construct(this->arr_ + curr_size, *(this->arr_ + (curr_size - 1)));
					}
					this->alloc_.construct(this->arr_ + new_pos, val);
				}
				catch (...)
				{
					std::cerr << "contruct threw exp.1\n";
					for (size_t i = 0; i < this->size_; ++i)
						this->alloc_.destroy(this->arr_ + i);
					this->size_ = 0;
					this->arr_ = NULL;
					throw ;
				}
				++this->size_;
			}
			else if (this->size_ == this->capacity_)
			{
				pointer tmp = NULL;
				try {tmp = this->alloc_.allocate(this->capacity_ * 2);}
				catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl; throw; }
				try
				{
					for (size_t i = 0; i < new_pos; ++i)
						this->alloc_.construct(tmp + i, *(this->arr_ + i));
					this->alloc_.construct(tmp + (new_pos), val);
					for (size_t i = new_pos++; i < this->size_; ++i, ++new_pos)
						this->alloc_.construct(tmp + new_pos, *(this->arr_ + i));
				}
				catch(...)
				{
					std::cerr << "contruct threw exp.2\n";
					for (size_t i = 0; i < this->size_; ++i)
						this->alloc_.destroy(tmp + i);
					this->alloc_.deallocate(tmp, this->capacity_ * 2);
					throw ;
				}
				this->~vector();
				this->arr_ = tmp;
				this->size_ = curr_size + 1;
				if (!this->capacity_)
					++this->capacity_;
				else
					this->capacity_ *= 2;
			}
			return (iterator(this->arr_ + diff));
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			typename ft::vector<T>::iterator::difference_type diff = position - this->begin();
			size_t new_pos = diff;
			if (!n)
				return ;
			if (this->size_ + n <= this->capacity_)
			{
				pointer tmp = NULL;
				try {tmp = this->alloc_.allocate(this->capacity_);}
				catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl; throw; }
				try
				{
					for (size_t i = 0; i < new_pos; ++i)
						this->alloc_.construct(tmp + i, *(this->arr_ + i));
					size_t i = new_pos;
					for (size_t j = 0; j < n; ++j, ++new_pos)
						this->alloc_.construct(tmp + new_pos, val);
					for ( ; i < this->size_; ++i, ++new_pos)
						this->alloc_.construct(tmp + new_pos, *(this->arr_ + i));
				}
				catch(...)
				{
					std::cerr << "contruct threw exp.3\n";
					for (size_t i = 0; i < this->size_; ++i)
						this->alloc_.destroy(tmp + i);
					this->alloc_.deallocate(tmp, this->capacity_);
					throw ;
				}
				size_t new_size = this->size_ + n;
				this->~vector();
				this->size_ = new_size;
				this->arr_ = tmp;
			}
			else
			{
				size_t new_cap;
				if (this->capacity_ * 2 >= this->size_ + n)
					new_cap = this->capacity_ * 2;
				else
					new_cap = this->size_ +  n;
				pointer tmp = NULL;
				try {tmp = this->alloc_.allocate(new_cap);}
				catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl; throw; }
				try
				{
					for (size_t i = 0; i < new_pos; ++i)
						this->alloc_.construct(tmp + i, *(this->arr_ + i));
					size_t i = new_pos;
					for (size_t j = 0; j < n; ++j, ++new_pos)
						this->alloc_.construct(tmp + new_pos, val);
					for ( ; i < this->size_; ++i, ++new_pos)
						this->alloc_.construct(tmp + new_pos, *(this->arr_ + i));
				}
				catch(...)
				{
					std::cerr << "contruct threw exp.4\n";
					for (size_t i = 0; i < this->size_; ++i)
						this->alloc_.destroy(tmp + i);
					this->alloc_.deallocate(tmp, new_cap);
					throw ;
				}
				size_t new_size = this->size_ + n;
				this->~vector();
				this->size_ = new_size;
				this->capacity_ = new_cap;
				this->arr_ = tmp;
			}
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first,
					typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type last)
		{
			typename InputIterator::difference_type diff = position - begin();
			typename InputIterator::difference_type distance = last - first;
			size_t new_pos = diff;
			if (this->size_ + static_cast<size_t>(distance) <= this->capacity_)
			{
				// std::cout << "YES1" << std::endl;
				pointer tmp = NULL;
				try {tmp = this->alloc_.allocate(this->capacity_);}
				catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl; throw ;}
				try
				{
					for (size_t i = 0; i < new_pos; ++i)
						this->alloc_.construct(tmp + i, *(this->arr_ + i));
					size_t i = new_pos;
					for (; first != last ; ++first, ++new_pos)
						this->alloc_.construct(tmp + new_pos, *first);
					for ( ; i < this->size_; ++i, ++new_pos)
						this->alloc_.construct(tmp + new_pos, *(this->arr_ + i));
				}
				catch(...)
				{
					std::cerr << "contruct threw exp.5\n";
					for (size_t i = 0; i < this->size_; ++i)
						this->alloc_.destroy(tmp + i);
					this->alloc_.deallocate(tmp, this->capacity_);
					throw ;
				}
				size_t new_size = this->size_ + static_cast<size_t>(distance);
				this->~vector();
				this->size_ = new_size;
				this->arr_ = tmp;
			}
			else
			{
				size_t new_cap;
				if (this->capacity_ * 2 >= this->size_ + static_cast<size_t>(distance))
					new_cap = this->capacity_ * 2;
				else
					new_cap = this->size_ + static_cast<size_t>(distance);
				pointer tmp = NULL;
				try {tmp = this->alloc_.allocate(new_cap);}
				catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl; throw; }
				try
				{
					for (size_t i = 0; i < new_pos; ++i)
						this->alloc_.construct(tmp + i, *(this->arr_ + i));
					size_t i = new_pos;
					for ( ; first != last; ++first, ++new_pos)
						this->alloc_.construct(tmp + new_pos, *first);
					for ( ; i < this->size_; ++i, ++new_pos)
						this->alloc_.construct(tmp + new_pos, *(this->arr_ + i));
				}
				catch(...)
				{
					for (size_t i = 0; i < new_cap; ++i)
						this->alloc_.destroy(tmp + i);
					this->alloc_.deallocate(tmp, new_cap);
					throw ;
				}
				size_t new_size = this->size_ + distance;
				this->~vector();
				this->size_ = new_size;
				this->capacity_ = new_cap;
				this->arr_ = tmp;
			}
		}
		
		iterator erase (iterator position)
		{
			typename iterator::difference_type diff = position - this->begin();
			this->alloc_.destroy(this->arr_ + diff);
			try
			{
				for (size_t i = static_cast<size_t>(diff) + 1; i < this->size_ ; ++i)
				{
					this->alloc_.construct(this->arr_ + i - 1, *(this->arr_ + i));
					this->alloc_.destroy(this->arr_ + i);
				}
			}
			catch(...)
			{
				for (size_t i = 0; i < this->size_ ; ++i)
				{
					this->alloc_.destroy(this->arr_ + i);
				}
				this->size_ = 0;
				this->arr_ = NULL;
				throw ;
			}
			--this->size_;
			return (iterator(this->arr_ + static_cast<size_t>(diff)));

		}
		
		iterator erase (iterator first, iterator last)
		{
			typename iterator::difference_type diff = first - this->begin();
			size_t diff_tmp = diff;
			typename iterator::difference_type distance = last - first;
			typename iterator::difference_type end_distance = this->end() - last;
			pointer tmp = NULL;
			try {tmp = this->alloc_.allocate(this->capacity_);}
			catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl; throw; }
			try
			{
				for (size_t i = 0; i < static_cast<size_t>(diff); ++i)
					this->alloc_.construct(tmp + i, *(this->arr_ + i));
				for (size_t i = 0; i < static_cast<size_t>(end_distance); ++i, ++diff)
					this->alloc_.construct(tmp + diff, *(this->arr_ + diff + distance));
			}
			catch(...)
			{
				for (size_t i = 0; i < this->capacity_; ++i)
					this->alloc_.destroy(tmp + i);
				this->alloc_.deallocate(tmp, this->capacity_);
				throw ;
			}
			this->~vector();
			this->size_ -= static_cast<size_t>(distance);
			this->arr_ = tmp;
			return (iterator(this->arr_ + static_cast<size_t>(diff_tmp)));
		}


		void swap (vector& x)
		{
			std::swap(this->size_, x.size_);
			std::swap(this->capacity_, x.capacity_);
			std::swap(this->alloc_, x.alloc_);
			std::swap(this->arr_, x.arr_);
		}

		void clear()
		{
			for (size_t i = 0; i < size_; ++i)
				alloc_.destroy(this->arr_ + i);
			this->size_ = 0;
		}

		allocator_type get_allocator() const {return(this->alloc_);}
		void print();
};

/*_________COMPARISON_OPERATORS___________*/

template <typename T>
bool operator==(const vector<T> &lhs, const vector<T> &rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	for (size_t i = 0; i < lhs.size(); ++i)
	{
		if (lhs.at(i) != rhs.at(i))
			return (false);
	}
	return (true);
}

template <typename T>
bool operator!=(const vector<T> &lhs, const vector<T> &rhs)
{
	return (!(lhs == rhs));
}

template <typename T>
bool operator<(const vector<T> &lhs, const vector<T> &rhs)
{
	for (size_t i = 0; i < lhs.size() && i < rhs.size(); ++i)
	{
		if (lhs.at(i) < rhs.at(i))
			return (true);
		else if (lhs.at(i) > rhs.at(i))
			return (false);
	}
	if (lhs.size() < rhs.size())
		return (true);
	return (false);
}

template <typename T>
bool operator>(const vector<T> &lhs, const vector<T> &rhs)
{
	return (rhs < lhs);
}

template <typename T>
bool operator>=(const vector<T> &lhs, const vector<T> &rhs)
{
	return (!(lhs < rhs));
}

template <typename T>
bool operator<=(const vector<T> &lhs, const vector<T> &rhs)
{
	return (!(lhs > rhs));
}




}


namespace std {
template <class T, class Allocator>
void swap (ft::vector<T ,Allocator>& x, ft::vector<T ,Allocator>& y) { x.swap(y); };

}
#endif
