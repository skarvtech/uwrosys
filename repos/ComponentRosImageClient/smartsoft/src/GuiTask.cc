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

#include "GuiTask.hh"
#include "ComponentRosImageClient.hh"

#include <iostream>

GuiTask::GuiTask(SmartACE::SmartComponent *comp) 
:	GuiTaskCore(comp)
, 	m_window("ROV Operator Viewer")
{
	std::cout << "constructor GuiTask\n";
}
GuiTask::~GuiTask() 
{
	std::cout << "destructor GuiTask\n";
}

void GuiTask::rgb_image_cb(const DomainVision::CommVideoImage &input)
{
	IplImage* currentImage;
	mrpt::poses::CPose3D currentImagePose;

	if(!input.is_data_valid())
	{
		std::cout << "[GuiTask] Error: IMAGE INVALID" << std::endl;
		return;
	}

	//cvReleaseImage(&currentImage);
	currentImage = NULL;
	currentImage = convertDataArrayToIplImage(input, cvSize(input.get_width(), input.get_height()));

	currentImagePose = mrpt::poses::CPose3D(
			input.get_sensor_pose().get_x(1),
			input.get_sensor_pose().get_y(1),
			input.get_sensor_pose().get_z(1),
			input.get_sensor_pose().get_azimuth(),
			input.get_sensor_pose().get_elevation(),
			input.get_sensor_pose().get_roll()
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

	m_window.showImage(cimage);
}

int GuiTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	return 0;
}
int GuiTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	// to get the incoming data, use this methods:
	Smart::StatusCode status;

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int GuiTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}

IplImage* GuiTask::convertDataArrayToIplImage(const DomainVision::CommVideoImage &img, CvSize size)
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
