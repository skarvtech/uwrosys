// Copyright (c) 2020 Skarv Technologies AS
// All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Project: UWROSYS
//          RobMoSys, Horizon 2020
//
// Author: Petter Norgren
//

#ifndef IMAGEBUFFER_HH_
#define IMAGEBUFFER_HH_

#define WITH_OLD_OPENCV_VERSION

#include <aceSmartSoft.hh>

#include "DomainVision/CommVideoImage.hh"

#include <mrpt/utils/CImage.h>
#include <mrpt/poses/CPose3D.h>

#include <cv.h>
#include <opencv2/highgui.hpp>
#include "OpenCVHelpers/OpenCVHelpers.hh"

#include <mutex>

class ImageBuffer {
private:
	std::mutex m_mtx;
	mrpt::utils::CImage m_image;
	bool m_newImage;

	IplImage* convertDataArrayToIplImage(const DomainVision::CommVideoImage &query_image, CvSize size);

public:
	ImageBuffer();
	virtual ~ImageBuffer();
	void init();
	void OnMsg(const DomainVision::CommVideoImage &msg);

	bool getImage(mrpt::utils::CImage &image);
};

#endif /* IMAGEBUFFER_HH_ */
