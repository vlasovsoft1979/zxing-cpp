/*
* Copyright 2021 Axel Waggershauser
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

namespace ZXing {

struct StructuredAppendInfo
{
	int index;
	int count;
	std::string id;

    StructuredAppendInfo() : index(-1), count(-1) {}
};

} // ZXing
