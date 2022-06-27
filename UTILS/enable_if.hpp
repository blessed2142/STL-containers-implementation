#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft {

template <bool condition, typename Type = void>
struct enable_if {};

template <typename Type>
struct enable_if<true, Type>
{
	typedef Type type;
};
}


#endif
