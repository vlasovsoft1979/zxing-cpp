/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ODRowReader.h"

namespace ZXing { namespace OneD {

class CodabarReader : public RowReader
{
public:
	Barcode decodePattern(int rowNumber, PatternView& next, std::unique_ptr<DecodingState>& state) const;
};

}} // namespace ZXing::OneD
