/*
* Copyright 2022 Axel Waggershauser
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ZXAlgorithms.h"

#include <iterator>

namespace ZXing {

template <typename Iterator>
struct StrideIter
{
	Iterator pos;
	int stride;

	typedef std::random_access_iterator_tag iterator_category;
	typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
	typedef typename std::iterator_traits<Iterator>::value_type value_type;
	typedef Iterator pointer;
	typedef typename std::iterator_traits<Iterator>::reference reference;

	auto operator*() const -> decltype(*pos) { return *pos; }
	auto operator[](int i) const -> decltype(*(pos + i * stride)) { return *(pos + i * stride); }
	StrideIter<Iterator>& operator++() { return pos += stride, *this; }
	StrideIter<Iterator> operator++(int) { auto temp = *this; ++*this; return temp; }
	bool operator!=(const StrideIter<Iterator>& rhs) const { return pos != rhs.pos; }
	StrideIter<Iterator> operator+(int i) const { return {pos + i * stride, stride}; }
	StrideIter<Iterator> operator-(int i) const { return {pos - i * stride, stride}; }
	int operator-(const StrideIter<Iterator>& rhs) const { return narrow_cast<int>((pos - rhs.pos) / stride); }
};

//template <typename Iterator>
//StrideIter(const Iterator&, int) -> StrideIter<Iterator>;


template <typename Iterator>
struct Range
{
	Iterator _begin, _end;

	Range(Iterator b, Iterator e) : _begin(b), _end(e) {}

	template <typename C>
	Range(const C& c) : _begin(std::begin(c)), _end(std::end(c)) {}

	Iterator begin() const noexcept { return _begin; }
	Iterator end() const noexcept { return _end; }
	explicit operator bool() const { return begin() < end(); }
	int size() const { return narrow_cast<int>(end() - begin()); }
};

//template <typename C>
//Range(const C&) -> Range<typename C::const_iterator>;

} // namespace ZXing
