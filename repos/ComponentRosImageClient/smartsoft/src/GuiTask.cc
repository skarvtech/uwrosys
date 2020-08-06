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

#include <mrpt/utils/CImage.h>

#include <iostream>

#include <VisualizationHelper.hh>

GuiTask::GuiTask(SmartACE::SmartComponent *comp) 
:	GuiTaskCore(comp)
{
	std::cout << "constructor GuiTask\n";
}
GuiTask::~GuiTask() 
{
	std::unique_lock<std::mutex> lck (m_mtx);
	std::cout << "destructor GuiTask\n";
}

void GuiTask::rgb_image_cb(const DomainVision::CommVideoImage &input)
{
	std::unique_lock<std::mutex> lck (m_mtx);
	m_image_queue.push_back(input);
}

bool GuiTask::get_newest_image(DomainVision::CommVideoImage &newest_image)
{
	std::unique_lock<std::mutex> lck (m_mtx);

	if(m_image_queue.empty())
	{
		return false;
	}

	newest_image = m_image_queue.back();
	m_image_queue.clear();
	return true;
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
	DomainVision::CommVideoImage img;

	if (this->get_newest_image(img))
	{
		// TODO: convert image to CImage.
		// get image
		/*mrpt::utils::CImage img(COMP->currentImage);
		const size_t maxSize = 800;
		if (img.getWidth() > maxSize || img.getHeight() > maxSize)
		{
			unsigned int factor, newWidth, newHeight;

			factor = img.getWidth() / maxSize;
			newWidth = img.getWidth() / factor;
			newHeight = img.getHeight() / factor;

			img.scaleImage(newWidth, newHeight);
		}

		std::cout << COMP->currentImagePose <<  std::endl;

	//	justifyHorizon(img, COMP->currentImagePose);

		m_window.showImage(img);*/
	} else
	{
		std::cout << "[GuiTask] Error no image to show!" << std::endl;
	}

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int GuiTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}

void GuiTask::justifyHorizon(mrpt::utils::CImage &image, CPose3D &imagePose)
{

	TPlane robot_xy;
	createPlaneFromPoseXY(CPose3D(), robot_xy);
	TLine3D camera_x;
	createFromPoseX(imagePose, camera_x);
	TLine3D camera_y;
	createFromPoseY(imagePose, camera_y);

	double angle_x = getAngle(robot_xy, camera_x);
	double angle_y = getAngle(robot_xy, camera_y);

	std::cout << "##### Correction angle_x: " << RAD2DEG(angle_x) << " via getAngle(robot_xy, camera_x)" << std::endl;
	std::cout << "##### Correction angle_y: " << RAD2DEG(angle_y) << " via getAngle(robot_xy, camera_y)" << std::endl;

	double angle=0.0;

	if(abs(angle_x) < abs(angle_y))
	{
		std::cout << "Taking X-Angle." << std::endl;

		// check if Y-axis points towards sky or ground, i.e. if camera is upside down or not.
		// it is upside down if xAxisCamera.z > 0
		CPoint3D tmpPoint(0, 1, 0);
		tmpPoint = imagePose + tmpPoint; // find point that is along y-Axis of camera coord
		std::cout << "tmp point after first trans: " << tmpPoint << std::endl;
		CPoint3D pnt(tmpPoint - CPoint3D(imagePose)); // get that coordinate system down to ground to see wether the point from before is below or above ground level.
		std::cout << "pnt: " << pnt << std::endl;

		if(pnt.z() > 0) { // new point above 0-plane, i.e. camera upside down
			angle = angle_x;
			angle += M_PI; // add 180° to rotate image correct
		} else {
			angle = -angle_x; // rotate in the other direction
		}


	}
	else
	{
		std::cout << "Taking Y-Angle." << std::endl;

		// check if X-Axis points towards sky or ground, i.e. which side of camera
		// chassis (left/right) points towards sky or ground
		CPoint3D tmpPoint(1, 0, 0);
		tmpPoint = imagePose + tmpPoint; // find point that is along X-Axis of camera coord
		std::cout << "tmp point after first trans: " << tmpPoint << std::endl;
		CPoint3D pnt(tmpPoint - CPoint3D(imagePose)); // get that coordinate system down to ground to see wether the point from before is below or above ground level.
		std::cout << "pnt: " << pnt << std::endl;

		if(pnt.z() > 0) { // new point above 0-plane
			angle = -angle_y;
			angle += M_PI;
		} else {
			angle = +angle_y;
		}

		angle += M_PI_2; // add 90° because in this case, camera is sidewards (90° to ground plane)

	}

	std::cout << ">>>> Result angle: " << RAD2DEG(angle) << "°" << std::endl;

	image.rotateImage(angle, image.getWidth()/2, image.getHeight()/2);
}
