/*
 * Copyright 2023 Antoine Mérino
 */
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ODRowReader.h"

namespace ZXing { namespace OneD {

/**
 * <p>Implements decoding of the DX Edge Film code format, a type or barcode found on 35mm films.</p>
 *
 * <p>See <a href="https://en.wikipedia.org/wiki/DX_encoding">https://en.wikipedia.org/wiki/DX_encoding</a></p>
 */

class DXFilmEdgeReader : public RowReader
{
public:
	explicit DXFilmEdgeReader(const ReaderOptions& opts) : RowReader(opts) {}
	Barcode decodePattern(int rowNumber, PatternView& next, std::unique_ptr<DecodingState>&) const;
};

}} // namespace ZXing::OneD
