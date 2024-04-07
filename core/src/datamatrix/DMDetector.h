/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#ifdef __cpp_impl_coroutine
#include <Generator.h>
#include <DetectorResult.h>
#endif

namespace ZXing {

class BitMatrix;
class DetectorResult;

namespace DataMatrix {

#ifdef __cpp_impl_coroutine
typedef Generator<DetectorResult> DetectorResults;
#else
typedef DetectorResult DetectorResults;
#endif

DetectorResults Detect(const BitMatrix& image, bool tryHarder, bool tryRotate, bool isPure);

} // DataMatrix
} // ZXing
