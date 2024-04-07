#pragma once

namespace stdx
{

template<typename T, bool a = false>
struct enable_if
{
    static_assert(a, "not supported");
};

template <typename T>
struct enable_if<T, true>
{
    typedef T value; // if true define the T type value
};

template <class T, T v>
struct integral_constant   //integral C++ struct in C++98 manner
{
    typedef T value_type;
    typedef integral_constant<T,v> type;
    static const T value = v;
    operator T() { return value; }
};

typedef integral_constant<bool,true> true_type;
typedef integral_constant<bool,false> false_type;

template<typename T> struct is_integral : public false_type{};
template<> struct is_integral<char> : public true_type{};
template<> struct is_integral<int> : public true_type{};
template<> struct is_integral<long> : public true_type{};
template<> struct is_integral<unsigned char> : public true_type{};
template<> struct is_integral<unsigned int> : public true_type{};
template<> struct is_integral<unsigned long> : public true_type{};

}
