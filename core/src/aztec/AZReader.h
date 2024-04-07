/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Reader.h"

namespace ZXing { namespace Aztec {

class Reader : public ZXing::Reader
{
public:
	Barcode decode(const BinaryBitmap& image) const ;
	Barcodes decode(const BinaryBitmap& image, int maxSymbols) const;
};

}} // namespace ZXing::Aztec
