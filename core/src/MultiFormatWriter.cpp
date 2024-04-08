/*
* Copyright 2017 Huy Cuong Nguyen
*/
// SPDX-License-Identifier: Apache-2.0

#include "MultiFormatWriter.h"

#include "BitMatrix.h"
#include "aztec/AZWriter.h"
#include "datamatrix/DMWriter.h"
#include "oned/ODCodabarWriter.h"
#include "oned/ODCode128Writer.h"
#include "oned/ODCode39Writer.h"
#include "oned/ODCode93Writer.h"
#include "oned/ODEAN13Writer.h"
#include "oned/ODEAN8Writer.h"
#include "oned/ODITFWriter.h"
#include "oned/ODUPCAWriter.h"
#include "oned/ODUPCEWriter.h"
#include "pdf417/PDFWriter.h"
#include "qrcode/QRErrorCorrectionLevel.h"
#include "qrcode/QRWriter.h"
#include "Utf.h"

#include <stdexcept>

namespace ZXing {

BitMatrix
MultiFormatWriter::encode(const std::wstring& contents, int width, int height) const
{
	auto AztecEccLevel = [&](Aztec::Writer& writer, int eccLevel) { writer.setEccPercent(eccLevel * 100 / 8); };
	auto Pdf417EccLevel = [&](Pdf417::Writer& writer, int eccLevel) { writer.setErrorCorrectionLevel(eccLevel); };
	auto QRCodeEccLevel = [&](QRCode::Writer& writer, int eccLevel) {
		writer.setErrorCorrectionLevel(static_cast<QRCode::ErrorCorrectionLevel>(--eccLevel / 2));
	};

	switch (_format) {
	case BarcodeFormat::Aztec: return exec1(Aztec::Writer(), AztecEccLevel, contents, width, height);
	case BarcodeFormat::DataMatrix: return exec2(DataMatrix::Writer(), contents, width, height);
	case BarcodeFormat::PDF417: return exec1(Pdf417::Writer(), Pdf417EccLevel,  contents, width, height);
	case BarcodeFormat::QRCode: return exec1(QRCode::Writer(), QRCodeEccLevel, contents, width, height);
	case BarcodeFormat::Codabar: return exec0(OneD::CodabarWriter(), contents, width, height);
	case BarcodeFormat::Code39: return exec0(OneD::Code39Writer(), contents, width, height);
	case BarcodeFormat::Code93: return exec0(OneD::Code93Writer(), contents, width, height);
	case BarcodeFormat::Code128: return exec0(OneD::Code128Writer(), contents, width, height);
	case BarcodeFormat::EAN8: return exec0(OneD::EAN8Writer(), contents, width, height);
	case BarcodeFormat::EAN13: return exec0(OneD::EAN13Writer(), contents, width, height);
	case BarcodeFormat::ITF: return exec0(OneD::ITFWriter(), contents, width, height);
	case BarcodeFormat::UPCA: return exec0(OneD::UPCAWriter(), contents, width, height);
	case BarcodeFormat::UPCE: return exec0(OneD::UPCEWriter(), contents, width, height);
	default: throw std::invalid_argument(std::string("Unsupported format: ") + ToString(_format));
	}
}

BitMatrix MultiFormatWriter::encode(const std::string& contents, int width, int height) const
{
	return encode(FromUtf8(contents), width, height);
}

} // ZXing
