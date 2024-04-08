/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

namespace ZXing {
namespace Pdf417 {

/**
* @author Guenther Grau
*/
class BarcodeMetadata
{
	int _columnCount;
	int _errorCorrectionLevel;
	int _rowCountUpperPart;
	int _rowCountLowerPart;

public:
	BarcodeMetadata() : _columnCount(0), _errorCorrectionLevel(0), _rowCountUpperPart(0), _rowCountLowerPart(0) {}
	BarcodeMetadata(int columnCount, int rowCountUpperPart, int rowCountLowerPart, int errorCorrectionLevel)
	    : _columnCount(columnCount), _errorCorrectionLevel(errorCorrectionLevel), _rowCountUpperPart(rowCountUpperPart),
	      _rowCountLowerPart(rowCountLowerPart)
	{
	}

	int columnCount() const {
		return _columnCount;
	}

	int errorCorrectionLevel() const {
		return _errorCorrectionLevel;
	}

	int rowCount() const {
		return _rowCountUpperPart + _rowCountLowerPart;
	}

	int rowCountUpperPart() const {
		return _rowCountUpperPart;
	}

	int rowCountLowerPart() const {
		return _rowCountLowerPart;
	}

};

} // Pdf417
} // ZXing
