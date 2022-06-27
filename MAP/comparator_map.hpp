#ifndef COMPARATOR_MAP_HPP
#define COMPARATOR_MAP_HPP
#include "map_iterator.hpp"
#include "const_map_iterator.hpp"
#include "reverse_map_iterator.hpp"
#include "const_reverse_map_iterator.hpp"

namespace ft {

template <typename Key, typename Value, typename T, typename U>
bool operator==(map_iterator<Key, Value, T> &lhs, const_map_iterator<Key, Value, U> &rhs)
{
	return (lhs.data() == rhs.data());
}

template <typename Key, typename Value, typename T, typename U>
bool operator==(const_map_iterator<Key, Value, T> &lhs, map_iterator<Key, Value, U> &rhs)
{
	return (lhs.data() == rhs.data());
}

template <typename Key, typename Value, typename T, typename U>
bool operator!=(map_iterator<Key, Value, T> &lhs, const_map_iterator<Key, Value, U> &rhs)
{
	return (lhs.data() != rhs.data());
}

template <typename Key, typename Value, typename T, typename U>
bool operator!=(const_map_iterator<Key, Value, T> &lhs, map_iterator<Key, Value, U> &rhs)
{
	return (lhs.data() != rhs.data());
}

template <typename Key, typename Value, typename T, typename U>
bool operator==(reverse_map_iterator<Key, Value, T> &lhs, const_reverse_map_iterator<Key, Value, U> &rhs)
{
	return (lhs.data() == rhs.data());
}

template <typename Key, typename Value, typename T, typename U>
bool operator==(const_reverse_map_iterator<Key, Value, T> &lhs, reverse_map_iterator<Key, Value, U> &rhs)
{
	return (lhs.data() == rhs.data());
}

template <typename Key, typename Value, typename T, typename U>
bool operator!=(reverse_map_iterator<Key, Value, T> &lhs, const_reverse_map_iterator<Key, Value, U> &rhs)
{
	return (lhs.data() != rhs.data());
}

template <typename Key, typename Value, typename T, typename U>
bool operator!=(const_reverse_map_iterator<Key, Value, T> &lhs, reverse_map_iterator<Key, Value, U> &rhs)
{
	return (lhs.data() != rhs.data());
}





}


#endif