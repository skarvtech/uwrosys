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

#include <ImageBuffer.hh>

#include "ComponentRosImageClient.hh"


ImageBuffer::ImageBuffer() :
	m_newImage(false)
{
	;
}

ImageBuffer::~ImageBuffer() {
	std::unique_lock<std::mutex> lck (this->m_mtx);
	std::cout << "Destroyed ImageBuffer" << std::endl;
}

bool ImageBuffer::getImage(mrpt::utils::CImage &image)
{
	std::unique_lock<std::mutex> lock(m_mtx);
	bool newImage = this->m_newImage;
	image = this->m_image;
	this->m_newImage = false;
	return newImage;
}

void ImageBuffer::OnMsg(const DomainVision::CommVideoImage &msg)
{
	IplImage* currentImage;
	mrpt::poses::CPose3D currentImagePose;

	if(!msg.is_data_valid())
	{
		std::cout << "[GuiTask] Error: IMAGE INVALID" << std::endl;
		return;
	}

	currentImage = NULL;
	currentImage = convertDataArrayToIplImage(msg, cvSize(msg.get_width(), msg.get_height()));

	currentImagePose = mrpt::poses::CPose3D(
			msg.get_sensor_pose().get_x(1),
			msg.get_sensor_pose().get_y(1),
			msg.get_sensor_pose().get_z(1),
			msg.get_sensor_pose().get_azimuth(),
			msg.get_sensor_pose().get_elevation(),
			msg.get_sensor_pose().get_roll()
	);

	mrpt::utils::CImage cimage(currentImage);
	const size_t maxSize = 800;
	if (cimage.getWidth() > maxSize || cimage.getHeight() > maxSize)
	{
		unsigned int factor, newWidth, newHeight;

		factor = cimage.getWidth() / maxSize;
		newWidth = cimage.getWidth() / factor;
		newHeight = cimage.getHeight() / factor;

		cimage.scaleImage(newWidth, newHeight);
	}

	std::unique_lock<std::mutex> lock(this->m_mtx);
	this->m_newImage = true;
	this->m_image = cimage;
}

void ImageBuffer::init() {
	std::cout << "Initialized ImageBuffer" << std::endl;
}

IplImage* ImageBuffer::convertDataArrayToIplImage(const DomainVision::CommVideoImage &img, CvSize size)
{
	IplImage* ipl_image = NULL;

	if (img.get_format() == DomainVision::FormatType::RGB24)
	{
		unsigned char* arr_image = new unsigned char[img.get_size_as_rgb24()];
		img.get_as_rgb24(arr_image);

		ipl_image = OpenCVHelpers::copyRGBToIplImage(arr_image, img.get_height(), img.get_width());
		delete arr_image;
	}
	else
	{
		std::cout << "Image Format: " << img.get_format() << " not supported!" << std::endl;
	}

	return ipl_image;
}
