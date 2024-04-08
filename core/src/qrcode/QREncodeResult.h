/*
* Copyright 2016 Huy Cuong Nguyen
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "BitMatrix.h"
#include "ByteArray.h"
#include "QRCodecMode.h"
#include "QRVersion.h"

namespace ZXing { namespace QRCode {

/**
* @author satorux@google.com (Satoru Takabayashi) - creator
* @author dswitkin@google.com (Daniel Switkin) - ported from C++
*
* Original class name in Java was QRCode, as this name is taken already for the namespace,
* so it's renamed here EncodeResult.
*/
class EncodeResult
{
public:
	EncodeResult()
		: ecLevel(ErrorCorrectionLevel::Invalid)
		, mode(CodecMode::TERMINATOR)
		, version(nullptr)
		, maskPattern(-1)
	{}
	ErrorCorrectionLevel ecLevel;
	CodecMode mode;
	const Version* version;
	int maskPattern;
	BitMatrix matrix;
};

}} // namespace ZXing::QRCode
