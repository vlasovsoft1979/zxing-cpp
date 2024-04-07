/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Reader.h"

namespace ZXing { namespace QRCode {

class Reader : public ZXing::Reader
{
public:
	explicit Reader(const ReaderOptions& opts, bool supportsInversion = false) : ZXing::Reader(opts, supportsInversion) {}
	Barcode decode(const BinaryBitmap& image) const;
	Barcodes decode(const BinaryBitmap& image, int maxSymbols) const;
};

}} // namespace ZXing::QRCode
