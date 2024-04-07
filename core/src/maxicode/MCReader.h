/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Reader.h"

namespace ZXing { namespace MaxiCode {

class Reader : public ZXing::Reader
{
public:
	Barcode decode(const BinaryBitmap& image) const;
};

}} // namespace ZXing::MaxiCode
