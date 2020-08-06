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

#include "ImageTask.hh"
#include "ComponentRosImageServer.hh"

#include <DomainVision/CommVideoImage.hh>

#include <iostream>

ImageTask::ImageTask(SmartACE::SmartComponent *comp) 
:	ImageTaskCore(comp)
{
	std::cout << "constructor ImageTask\n";
}
ImageTask::~ImageTask() 
{
	std::cout << "destructor ImageTask\n";
}

void ImageTask::_camera_image_cb(const sensor_msgs::Image::ConstPtr &msg)
{
	DomainVision::FormatType format;
	if(!msg->encoding.compare("rgb8"))
	{
		DomainVision::CommVideoImage::string2format("rgb24", format);
		DomainVision::CommVideoImage image(msg->width, msg->height, format, msg->data.data());
		COMP->rGBImagePushServiceOut->put(image);
	}
	else
	{
		std::cout << "ImageTask: Unsupported video encoding: " + msg->encoding + ".\n";
	}
}


int ImageTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	return 0;
}
int ImageTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	// to get the incoming data, use this methods:
	Smart::StatusCode status;

	//std::cout << "Hello from ImageTask " << std::endl;

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int ImageTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
