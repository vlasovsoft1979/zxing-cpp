/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Reader.h"

#include <list>

namespace ZXing { namespace Pdf417 {

/**
* This implementation can detect and decode PDF417 codes in an image.
*
* @author Guenther Grau
*/
class Reader : public ZXing::Reader
{
public:
	explicit Reader(const ReaderOptions& opts, bool supportsInversion = false) : ZXing::Reader(opts, supportsInversion) {}
	Barcode decode(const BinaryBitmap& image) const;
	Barcodes decode(const BinaryBitmap& image, int maxSymbols) const;
};

}} // namespace ZXing::Pdf417
