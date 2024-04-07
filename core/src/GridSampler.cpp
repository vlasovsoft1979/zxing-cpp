/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
* Copyright 2020 Axel Waggershauser
*/
// SPDX-License-Identifier: Apache-2.0

#include "GridSampler.h"

#ifdef PRINT_DEBUG
#include "LogMatrix.h"
#include "BitMatrixIO.h"
#endif

namespace ZXing {

#ifdef PRINT_DEBUG
LogMatrix log;
#endif

DetectorResult SampleGrid(const BitMatrix& image, int width, int height, const PerspectiveTransform& mod2Pix)
{
	return SampleGrid(image, width, height, {ROI{0, width, 0, height, mod2Pix}});
}

DetectorResult SampleGrid(const BitMatrix& image, int width, int height, const ROIs& rois)
{
#ifdef PRINT_DEBUG
	LogMatrix log;
	static int i = 0;
	LogMatrixWriter lmw(log, image, 5, "grid" + std::to_string(i++) + ".pnm");
#endif
	if (width <= 0 || height <= 0)
		return {};

	for (auto&& roi : rois) {
		// Precheck the corners of every roi to bail out early if the grid is "obviously" not completely inside the image
		auto isInside = [&roi, &image](int x, int y) { return image.isIn(roi.mod2Pix(centered(PointI(x, y)))); };
		if (!roi.mod2Pix.isValid() || !isInside(roi.x0, roi.y0) || !isInside(roi.x1 - 1, roi.y0) || !isInside(roi.x1 - 1, roi.y1 - 1) || !isInside(roi.x0, roi.y1 - 1))
			return {};
	}

	BitMatrix res(width, height);
	for (auto&& roi : rois) {
		for (int y = roi.y0; y < roi.y1; ++y)
			for (int x = roi.x0; x < roi.x1; ++x) {
				auto p = roi.mod2Pix(centered(PointI{x, y}));
				// Due to a "numerical instability" in the PerspectiveTransform generation/application it has been observed
				// that even though all boundary grid points get projected inside the image, it can still happen that an
				// inner grid points is not. See #563. A true perspective transformation cannot have this property.
				// The following check takes 100% care of the issue and turned out to be less of a performance impact than feared.
				// TODO: Check some mathematical/numercial property of mod2Pix to determine if it is a perspective transforation.
				if (!image.isIn(p))
					return {};

#ifdef PRINT_DEBUG
				log(p, 3);
#endif
#if 0
				int sum = 0;
				for (int dy = -1; dy <= 1; ++dy)
					for (int dx = -1; dx <= 1; ++dx)
						sum += image.get(p + PointF(dx, dy));
				if (sum >= 5)
#else
				if (image.get(p))
#endif
					res.set(x, y);
			}
	}

#ifdef PRINT_DEBUG
	printf("width: %d, height: %d\n", width, height);
//	printf("%s", ToString(res).c_str());
#endif

	auto projectCorner = [&](PointI p) {
		for (auto&& roi : rois)
			if (roi.x0 <= p.x && p.x <= roi.x1 && roi.y0 <= p.y && p.y <= roi.y1)
				return PointI(roi.mod2Pix(PointF(p)) + PointF(0.5, 0.5));

		return PointI();
	};

	return {std::move(res),
			{projectCorner({0, 0}), projectCorner({width, 0}), projectCorner({width, height}), projectCorner({0, height})}};
	}

} // ZXing
