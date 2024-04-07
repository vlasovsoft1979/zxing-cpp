/*
 * Copyright 2022 Axel Waggershauser
 */
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include <cstdint>

namespace ZXing {

class Error
{
public:
	enum class Type : uint8_t { None, Format, Checksum, Unsupported };
	Type type() const noexcept { return _type; }
	const std::string& msg() const noexcept { return _msg; }
	explicit operator bool() const noexcept { return _type != Type::None; }

	std::string location() const;

	Error() : _file(nullptr), _line(-1), _type(Type::None) {}
	Error(Type type, std::string msg = std::string()) : _msg(std::move(msg)), _type(type) {}
	Error(const char* file, short line, Type type, std::string msg = std::string()) : _msg(std::move(msg)), _file(file), _line(line), _type(type) {}

	static constexpr auto Format = Type::Format;
	static constexpr auto Checksum = Type::Checksum;
	static constexpr auto Unsupported = Type::Unsupported;

	inline bool operator==(const Error& o) const noexcept
	{
		return _type == o._type && _msg == o._msg && _file == o._file && _line == o._line;
	}
	inline bool operator!=(const Error& o) const noexcept { return !(*this == o); }

protected:
	std::string _msg;
	const char* _file;
	short _line;
	Type _type;
};

inline bool operator==(const Error& e, Error::Type t) noexcept { return e.type() == t; }
inline bool operator!=(const Error& e, Error::Type t) noexcept { return !(e == t); }
inline bool operator==(Error::Type t, const Error& e) noexcept { return e.type() == t; }
inline bool operator!=(Error::Type t, const Error& e) noexcept { return !(t == e); }

#define FormatError(...) Error(__FILE__, __LINE__, Error::Format, std::string(__VA_ARGS__))
#define ChecksumError(...) Error(__FILE__, __LINE__, Error::Checksum, std::string(__VA_ARGS__))
#define UnsupportedError(...) Error(__FILE__, __LINE__, Error::Unsupported, std::string(__VA_ARGS__))

std::string ToString(const Error& e);

}
