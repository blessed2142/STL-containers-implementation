#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP
#include "iterator.hpp"
#include "const_iterator.hpp"

namespace ft {

template <typename T, typename U>
bool operator==(iterator<T> &lhs, const_iterator<U> &rhs)
{
	return (lhs.data() == rhs.data());
}

template <typename T, typename U>
bool operator==(const_iterator<T> &lhs, iterator<U> &rhs)
{
	return (lhs.data() == rhs.data());
}

template <typename T, typename U>
bool operator!=(iterator<T> &lhs, const_iterator<U> &rhs)
{
	return (!(lhs != rhs));
}

template <typename T, typename U>
bool operator!=(const_iterator<T> &lhs, iterator<U> &rhs)
{
	return (!(lhs != rhs));
}

template <typename T, typename U>
bool operator<(iterator<T> &lhs, const_iterator<U> &rhs)
{
	return (lhs.data() < rhs.data());
}

template <typename T, typename U>
bool operator<(const_iterator<T> &lhs, iterator<U> &rhs)
{
	return (lhs.data() < rhs.data());
}

template <typename T, typename U>
bool operator>(iterator<T> &lhs, const_iterator<U> &rhs)
{
	return (lhs.data() > rhs.data());
}

template <typename T, typename U>
bool operator>(const_iterator<T> &lhs, iterator<U> &rhs)
{
	return (lhs.data() > rhs.data());
}

template <typename T, typename U>
bool operator<=(iterator<T> &lhs, const_iterator<U> &rhs)
{
	return (lhs.data() <= rhs.data());
}

template <typename T, typename U>
bool operator<=(const_iterator<T> &lhs, iterator<U> &rhs)
{
	return (lhs.data() <= rhs.data());
}

template <typename T, typename U>
bool operator>=(iterator<T> &lhs, const_iterator<U> &rhs)
{
	return (lhs.data() >= rhs.data());
}

template <typename T, typename U>
bool operator>=(const_iterator<T> &lhs, iterator<U> &rhs)
{
	return (lhs.data() >= rhs.data());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
bool operator==(reverse_iterator<T> &lhs, const_reverse_iterator<U> &rhs)
{
	return (lhs.data() == rhs.data());
}

template <typename T, typename U>
bool operator==(const_reverse_iterator<T> &lhs, reverse_iterator<U> &rhs)
{
	return (lhs.data() == rhs.data());
}

template <typename T, typename U>
bool operator!=(reverse_iterator<T> &lhs, const_reverse_iterator<U> &rhs)
{
	return (!(lhs != rhs));
}

template <typename T, typename U>
bool operator!=(const_reverse_iterator<T> &lhs, reverse_iterator<U> &rhs)
{
	return (!(lhs != rhs));
}

template <typename T, typename U>
bool operator<(reverse_iterator<T> &lhs, const_reverse_iterator<U> &rhs)
{
	return (lhs.data() < rhs.data());
}

template <typename T, typename U>
bool operator<(const_reverse_iterator<T> &lhs, reverse_iterator<U> &rhs)
{
	return (lhs.data() < rhs.data());
}

template <typename T, typename U>
bool operator>(reverse_iterator<T> &lhs, const_reverse_iterator<U> &rhs)
{
	return (lhs.data() > rhs.data());
}

template <typename T, typename U>
bool operator>(const_reverse_iterator<T> &lhs, reverse_iterator<U> &rhs)
{
	return (lhs.data() > rhs.data());
}

template <typename T, typename U>
bool operator<=(reverse_iterator<T> &lhs, const_reverse_iterator<U> &rhs)
{
	return (lhs.data() <= rhs.data());
}

template <typename T, typename U>
bool operator<=(const_reverse_iterator<T> &lhs, reverse_iterator<U> &rhs)
{
	return (lhs.data() <= rhs.data());
}

template <typename T, typename U>
bool operator>=(reverse_iterator<T> &lhs, const_reverse_iterator<U> &rhs)
{
	return (lhs.data() >= rhs.data());
}

template <typename T, typename U>
bool operator>=(const_reverse_iterator<T> &lhs, reverse_iterator<U> &rhs)
{
	return (lhs.data() >= rhs.data());
}
}





#endif