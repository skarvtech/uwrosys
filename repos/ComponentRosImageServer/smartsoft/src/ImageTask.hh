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

#ifndef _IMAGETASK_HH
#define _IMAGETASK_HH

#include "ImageTaskCore.hh"

#include <sensor_msgs/Image.h>

class ImageTask  : public ImageTaskCore
{
private:
public:
	ImageTask(SmartACE::SmartComponent *comp);
	virtual ~ImageTask();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();

	void _camera_image_cb(const sensor_msgs::Image::ConstPtr &msg);
};

#endif
