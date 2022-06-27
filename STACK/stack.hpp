#ifndef STACK_HPP
#define STACK_HPP

#include "../VECTOR/vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T> >
class stack
{
	public:

		typedef Container										container_type;
		typedef T												value_type;
		typedef size_t											size_type;
		typedef typename container_type::reference				reference;
		typedef typename container_type::const_reference		const_reference;
	
	private:

		container_type cont_;

	public:

		explicit stack (const container_type& ctnr = container_type()) : cont_(ctnr) {}
		stack(const stack &other) : cont_(other.cont_) {}
		stack &operator=(const stack &other)
		{
			if (this != &other)
				this->cont_ = other.cont_;
			return (*this);
		}
		~stack() {}

		bool empty() const { return (cont_.empty()); }
		size_type size() const { return(cont_.size()); }
		value_type& top() { return (cont_.back()); }
		const value_type& top() const { return (cont_.back()); }
		void push (const value_type& val) { cont_.push_back(val); }
		void pop() { cont_.pop_back(); }

		template <class A, class Cont>
		friend bool operator==(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
		template <class A, class Cont>
		friend bool operator!=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
		template <class A, class Cont>
		friend bool operator<(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
		template <class A, class Cont>
		friend bool operator>(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
		template <class A, class Cont>
		friend bool operator<=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
		template <class A, class Cont>
		friend bool operator>=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
};

template <class A, class Cont>
bool operator== (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
{
	return (lhs.cont_ == rhs.cont_);
}

template <class A, class Cont>
bool operator!=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
{
	return (lhs.cont_ != rhs.cont_);
}

template <class A, class Cont>
bool operator<(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
{
	return (lhs.cont_ < rhs.cont_);
}

template <class A, class Cont>
bool operator>(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
{
	return (lhs.cont_ > rhs.cont_);
}

template <class A, class Cont>
bool operator<=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
{
	return (lhs.cont_ <= rhs.cont_);
}

template <class A, class Cont>
bool operator>=(const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
{
	return (lhs.cont_ >= rhs.cont_);
}

}
#endif
