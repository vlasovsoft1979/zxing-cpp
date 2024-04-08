/*
* Copyright 2017 Huy Cuong Nguyen
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "BarcodeFormat.h"
#include "CharacterSet.h"
#include "BitMatrix.h"

#include <string>

namespace ZXing {

class BitMatrix;

/**
* This class is here just for convenience as it offers single-point service
* to generate barcodes for all supported formats. As a result, this class
* offer very limited customization compared to what are available in each
* individual encoder.
*/
class MultiFormatWriter
{
public:
	explicit MultiFormatWriter(BarcodeFormat format) : _format(format), _encoding(CharacterSet::Unknown), _margin(-1), _eccLevel(-1)  {}

	/**
	* Used for Aztec, PDF417, and QRCode only.
	*/
	MultiFormatWriter& setEncoding(CharacterSet encoding) {
		_encoding = encoding;
		return *this;
	}

	/**
	* Used for Aztec, PDF417, and QRCode only, [0-8].
	*/
	MultiFormatWriter& setEccLevel(int level) {
		_eccLevel = level;
		return *this;
	}

	/**
	* Used for all formats, sets the minimum number of quiet zone pixels.
	*/
	MultiFormatWriter& setMargin(int margin) {
		_margin = margin;
		return *this;
	}

	BitMatrix encode(const std::wstring& contents, int width, int height) const;
	BitMatrix encode(const std::string& contents, int width, int height) const;

private:
	template<typename T>
	BitMatrix exec0(T&& writer, const std::wstring& contents, int width, int height) const
	{
		if (_margin >=0)
			writer.setMargin(_margin);
		return writer.encode(contents, width, height);
	}

	template<typename T, typename E>
	BitMatrix exec1(T&& writer, E setEccLevel, const std::wstring& contents, int width, int height) const
	{
		if (_encoding != CharacterSet::Unknown)
			writer.setEncoding(_encoding);
		if (_eccLevel >= 0 && _eccLevel <= 8)
			setEccLevel(writer, _eccLevel);
		return exec0(std::move(writer), contents, width, height);
	}

	template<typename T>
	BitMatrix exec2(T&& writer, const std::wstring& contents, int width, int height) const
	{
		if (_encoding != CharacterSet::Unknown)
			writer.setEncoding(_encoding);
		return exec0(std::move(writer), contents, width, height);
	};

private:
	BarcodeFormat _format;
	CharacterSet _encoding;
	int _margin;
	int _eccLevel;
};

} // ZXing
