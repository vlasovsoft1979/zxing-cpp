/*
* Copyright 2020 Axel Waggershauser
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "BitHacks.h"

#include <cstddef>
#include <iterator>
#include <type_traits>

namespace ZXing {

template<typename Enum>
class Flags
{
	static_assert(std::is_enum<Enum>::value, "Flags is only usable on enumeration types.");

	typedef int Int;
	Int i;

	constexpr inline Flags(Int other) : i(other) {}
	constexpr static inline unsigned highestBitSet(Int x) noexcept { return x < 2 ? x : 1 + highestBitSet(x >> 1); }

public:
	typedef Enum enum_type;

    constexpr inline Flags() : i(0) {}
	constexpr inline Flags(Enum flag) noexcept : i(Int(flag)) {}

//	constexpr inline Flags(std::initializer_list<Enum> flags) noexcept
//		: i(initializer_list_helper(flags.begin(), flags.end()))
//	{}

	class iterator
	{
		friend class Flags;
		const Int _flags;
		int _pos;
        iterator() : _flags(0), _pos(0) {}
		iterator(Int i, int p) : _flags(i), _pos(p) {}
	public:
		typedef std::input_iterator_tag iterator_category;
		typedef Enum value_type;
		typedef std::ptrdiff_t difference_type;
		typedef Enum* pointer;
		typedef Enum& reference;

		Enum operator*() const noexcept { return Enum(1 << _pos); }

		iterator& operator++() noexcept
		{
			while (++_pos < BitHacks::HighestBitSet(_flags) && !((1 << _pos) & _flags))
				;
			return *this;
		}

		bool operator==(const iterator& rhs) const noexcept { return _pos == rhs._pos; }
		bool operator!=(const iterator& rhs) const noexcept { return !(*this == rhs); }
	};

	iterator begin() const noexcept { return {i, BitHacks::NumberOfTrailingZeros(i)}; }
	iterator end() const noexcept { return {i, BitHacks::HighestBitSet(i) + 1}; }

	bool empty() const noexcept { return i == 0; }
	int count() const noexcept { return BitHacks::CountBitsSet(i); }

	constexpr inline bool operator==(Flags other) const noexcept { return i == other.i; }

	inline Flags& operator&=(Flags mask) noexcept { return i &= mask.i, *this; }
	inline Flags& operator&=(Enum mask) noexcept { return i &= Int(mask), *this; }
	inline Flags& operator|=(Flags other) noexcept { return i |= other.i, *this; }
	inline Flags& operator|=(Enum other) noexcept { return i |= Int(other), *this; }
//	inline Flags &operator^=(Flags other) noexcept { return i ^= other.i, *this; }
//	inline Flags &operator^=(Enum other) noexcept { return i ^= Int(other), *this; }

	constexpr inline Flags operator&(Flags other) const noexcept { return i & other.i; }
	constexpr inline Flags operator&(Enum other) const noexcept { return i & Int(other); }
	constexpr inline Flags operator|(Flags other) const noexcept { return i | other.i; }
	constexpr inline Flags operator|(Enum other) const noexcept { return i | Int(other); }
//	constexpr inline Flags operator^(Flags other) const noexcept { return i ^ other.i; }
//	constexpr inline Flags operator^(Enum other) const noexcept { return i ^ Int(other); }
//	constexpr inline Flags operator~() const noexcept { return ~i; }

//	constexpr inline operator Int() const noexcept { return i; }
//	constexpr inline bool operator!() const noexcept { return !i; }
//	constexpr inline Int asInt() const noexcept { return i; }

	constexpr inline bool testFlag(Enum flag) const noexcept
	{
		return (i & Int(flag)) == Int(flag) && (Int(flag) != 0 || i == Int(flag));
	}
	constexpr inline bool testFlags(Flags mask) const noexcept { return i & mask.i; }
	inline Flags& setFlag(Enum flag, bool on = true) noexcept
	{
		return on ? (*this |= flag) : (*this &= ~Int(flag));
	}
	inline void clear() noexcept { i = 0; }

	constexpr static Flags all() noexcept { return ~(unsigned(~0) << highestBitSet(Int(Enum::_max))); }

private:
//	constexpr static inline Int
//	initializer_list_helper(typename std::initializer_list<Enum>::const_iterator it,
//							typename std::initializer_list<Enum>::const_iterator end) noexcept
//	{
//		return (it == end ? Int(0) : (Int(*it) | initializer_list_helper(it + 1, end)));
//	}
};

#define ZX_DECLARE_FLAGS(FLAGS, ENUM) \
	typedef Flags<ENUM> FLAGS; \
	constexpr inline FLAGS operator|(FLAGS::enum_type e1, FLAGS::enum_type e2) noexcept { return FLAGS(e1) | e2; } \
	constexpr inline FLAGS operator|(FLAGS::enum_type e, FLAGS f) noexcept { return f | e; } \
	constexpr inline bool operator==(FLAGS::enum_type e, FLAGS f) noexcept { return FLAGS(e) == f; } \
	constexpr inline bool operator==(FLAGS f, FLAGS::enum_type e) noexcept { return FLAGS(e) == f; }

} // ZXing

