cmake_minimum_required(VERSION 3.16)

project(zxing)

add_library(zxing STATIC 
    src/Reader.h
    src/Version.h
    src/ZXConfig.h
    src/ZXTestSupport.h
    src/LogMatrix.h
    src/BitHacks.h
    src/Flags.h
    src/ImageView.h
    src/Quadrilateral.h
    src/RegressionLine.h
    src/DetectorResult.h
    src/DecoderResult.h
    src/BitMatrixCursor.h
    src/ReaderOptions.h
    src/StructuredAppend.h
    src/ThresholdBinarizer.h
    src/Error.cpp src/Error.h
    src/BitArray.cpp src/BitArray.h
    src/GridSampler.cpp src/GridSampler.h
    src/ConcentricFinder.cpp src/ConcentricFinder.h
    src/PerspectiveTransform.cpp src/PerspectiveTransform.h
    src/BitSource.cpp src/BitSource.h
    src/CharacterSet.cpp src/CharacterSet.h
    src/Content.cpp src/Content.h
    src/Barcode.cpp src/Barcode.h
    src/BarcodeFormat.cpp src/BarcodeFormat.h
    src/GenericGF.cpp src/GenericGF.h
    src/GenericGFPoly.cpp src/GenericGFPoly.h
    src/ECI.cpp src/ECI.h
    src/HRI.cpp src/HRI.h
    src/TextDecoder.cpp src/TextDecoder.h
    src/Utf.cpp src/Utf.h
    src/ReedSolomonDecoder.cpp src/ReedSolomonDecoder.h
    src/ReadBarcode.cpp src/ReadBarcode.h
    src/GlobalHistogramBinarizer.cpp src/GlobalHistogramBinarizer.h
    src/HybridBinarizer.cpp src/HybridBinarizer.h
    src/BinaryBitmap.cpp src/BinaryBitmap.h
    src/MultiFormatReader.cpp src/MultiFormatReader.h
    src/BitMatrix.cpp src/BitMatrix.h
)

target_sources(zxing PRIVATE
    src/libzueci/zueci.c
    src/libzueci/zueci.h
    src/libzueci/zueci_big5.h
    src/libzueci/zueci_common.h
    src/libzueci/zueci_gb18030.h
    src/libzueci/zueci_gb2312.h
    src/libzueci/zueci_gbk.h
    src/libzueci/zueci_ksx1001.h
    src/libzueci/zueci_sb.h
    src/libzueci/zueci_sjis.h
)

target_sources(zxing PRIVATE
    src/qrcode/QRECB.h
    src/qrcode/QRDataMask.h
    src/qrcode/QRDetector.cpp src/qrcode/QRDetector.h
    src/qrcode/QRFormatInformation.cpp src/qrcode/QRFormatInformation.h
    src/qrcode/QRVersion.cpp src/qrcode/QRVersion.h
    src/qrcode/QRErrorCorrectionLevel.cpp src/qrcode/QRErrorCorrectionLevel.h
    src/qrcode/QRDecoder.cpp src/qrcode/QRDecoder.h
    src/qrcode/QRBitMatrixParser.cpp src/qrcode/QRBitMatrixParser.h
    src/qrcode/QRCodecMode.cpp src/qrcode/QRCodecMode.h
    src/qrcode/QRDataBlock.cpp src/qrcode/QRDataBlock.h
    src/qrcode/QRReader.cpp src/qrcode/QRReader.h
)

target_sources(zxing PRIVATE
    src/tools/optional.hpp
    src/tools/string_view.hpp
    src/tools/algorithm.hpp
    src/tools/type_traits.hpp
)

if (MSVC)
    target_compile_options(zxing PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/Zc:__cplusplus>)
else()
    target_compile_options(zxing PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++0x>)
endif()

include_directories(src src/qrcode src/libzueci src/tools)

add_subdirectory(src/tests)
