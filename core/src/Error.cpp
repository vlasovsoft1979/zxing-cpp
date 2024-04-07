/*
 * Copyright 2022 Axel Waggershauser
 */
// SPDX-License-Identifier: Apache-2.0

#include "Error.h"

namespace ZXing {

constexpr Error::Type Error::Format;
constexpr Error::Type Error::Checksum;
constexpr Error::Type Error::Unsupported;

std::string Error::location() const
{
	if (!_file)
		return {};
	std::string file(_file);
	return file.substr(file.find_last_of("/\\") + 1) + ":" + std::to_string(_line);
}

std::string ToString(const Error& e)
{
	const char* name[] = {"", "FormatError", "ChecksumError", "Unsupported"};
	std::string ret = name[static_cast<int>(e.type())];
	if (!e.msg().empty())
		ret += " (" + e.msg() + ")";
	auto location = e.location();
	if (!location.empty())
		ret += " @ " + e.location();
	return ret;
}

}
