/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ODRowReader.h"

namespace ZXing { namespace OneD {

class Code39Reader : public RowReader
{
public:
	explicit Code39Reader(const ReaderOptions& opts) : RowReader(opts) {}
	/**
	* Creates a reader that can be configured to check the last character as a check digit,
	* or optionally attempt to decode "extended Code 39" sequences that are used to encode
	* the full ASCII character set.
	*/
	Barcode decodePattern(int rowNumber, PatternView& next, std::unique_ptr<DecodingState>&) const;
};

}} // namespace ZXing::OneD
