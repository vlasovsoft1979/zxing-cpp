/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ODRowReader.h"

namespace ZXing { namespace OneD {

/**
* @brief A reader that can read all available UPC/EAN formats.
*/
class MultiUPCEANReader : public RowReader
{
public:
	explicit MultiUPCEANReader(const ReaderOptions& opts) : RowReader(opts) {}
	Barcode decodePattern(int rowNumber, PatternView& next, std::unique_ptr<DecodingState>&) const;
};

}} // namespace ZXing::OneD
