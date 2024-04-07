/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "DetectorResult.h"

#include <utility>

namespace ZXing { namespace Aztec {

class DetectorResult : public ZXing::DetectorResult
{
	bool _compact;
	int _nbDatablocks;
	int _nbLayers;
	bool _readerInit;
	bool _isMirrored;

	DetectorResult(const DetectorResult&) = delete;
	DetectorResult& operator=(const DetectorResult&) = delete;

public:
	DetectorResult()
		: _compact(false)
		, _nbDatablocks(0)
		, _nbLayers(0)
		, _readerInit(false)
		, _isMirrored(false)
	{}
	DetectorResult(DetectorResult&&) = default;
	DetectorResult& operator=(DetectorResult&&) = default;

	DetectorResult(ZXing::DetectorResult&& result, bool isCompact, int nbDatablocks, int nbLayers, bool readerInit, bool isMirrored)
		: ZXing::DetectorResult{std::move(result)},
		  _compact(isCompact),
		  _nbDatablocks(nbDatablocks),
		  _nbLayers(nbLayers),
		  _readerInit(readerInit),
		  _isMirrored(isMirrored)
	{}

	bool isCompact() const { return _compact; }
	int nbDatablocks() const { return _nbDatablocks; }
	int nbLayers() const { return _nbLayers; }
	bool readerInit() const { return _readerInit; }
	bool isMirrored() const { return _isMirrored; }
};

}} // namespace ZXing::Aztec
