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

#include "SonarTask.hh"
#include "ComponentUUVSonar.hh"

#include "Queue.hh"

#include <iostream>

#include <sys/time.h>
#include <Eigen/Dense>

SonarTask::SonarTask(SmartACE::SmartComponent *comp) 
:	SonarTaskCore(comp)
, 	m_queue(nullptr)
, 	m_counter(0)
{
	std::cout << "constructor SonarTask\n";
}
SonarTask::~SonarTask() 
{
	std::cout << "destructor SonarTask\n";
}

void SonarTask::_sonar_cb (const sensor_msgs::LaserScan::ConstPtr &msg)
{
	CommBasicObjects::CommMobileLaserScan commMobileLaserScan;

	timeval _receive_time;
	::gettimeofday(&_receive_time, NULL);
	commMobileLaserScan.set_scan_time_stamp(CommBasicObjects::CommTimeStamp(_receive_time));

	CommBasicObjects::CommBasePose pose = COMP->state->getBaseState().get_base_position();

	commMobileLaserScan.set_scanner_x(pose.get_x());
	commMobileLaserScan.set_scanner_y(pose.get_y());
	commMobileLaserScan.set_scanner_z(pose.get_z());

	commMobileLaserScan.set_scanner_azimuth(pose.get_base_azimuth());

	CommBasicObjects::CommPose3d SensorOffset(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	commMobileLaserScan.set_sensor_pose(SensorOffset);

	commMobileLaserScan.set_scan_length_unit(1);

	int count = sizeof(msg->ranges)/sizeof(float);

	double openingAngle = (msg->angle_max - msg->angle_min) * 180.0 / M_PI;
	double resolution = msg->angle_increment * 180.0 / M_PI;

	commMobileLaserScan.set_scan_double_field_of_view(msg->angle_min*180.0/M_PI, resolution);

	commMobileLaserScan.set_max_scan_size(count);

	commMobileLaserScan.set_min_distance(msg->range_min, 1);
	commMobileLaserScan.set_max_distance(msg->range_max, 1);

	if (count == 0) {
		commMobileLaserScan.set_scan_valid(false);
		commMobileLaserScan.set_scan_size(count);
	}

	else {
		commMobileLaserScan.set_scan_valid(true);
		commMobileLaserScan.set_scan_size(count);

		for (int i = 0; i < count; i++) {

			if (std::isinf(msg->ranges[i])) {
				commMobileLaserScan.set_scan_distance(i, msg->range_max,1);
			}
			else {
				commMobileLaserScan.set_scan_distance(i, msg->ranges[i],1);
			}
			commMobileLaserScan.set_scan_index(i, i);
		}

		for (int i = 0; i < count; i++) {
			commMobileLaserScan.set_scan_intensity(i, msg->intensities[i]);
		}
	}

	std::unique_lock<std::mutex> lock(m_mtx);
	m_commMobileLaserScan = commMobileLaserScan;
	m_queue->addEntry(m_commMobileLaserScan);
	m_mtx.unlock();
}


int SonarTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	if (m_queue == nullptr)
	{
		m_queue = new Queue();
	}
	return 0;
}
int SonarTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	// to get the incoming data, use this methods:
	Smart::StatusCode status;

	CommBasicObjects::CommBaseState commCurrentBaseState;

	std::unique_lock<std::mutex> lock(m_mtx);
	CommBasicObjects::CommMobileLaserScan commMobileLaserScan = m_queue->removeEntry();
	m_mtx.unlock();

	commCurrentBaseState.set_base_position(COMP->state->getBaseState().get_base_position());
	commCurrentBaseState.set_base_raw_position(COMP->state->getBaseState().get_base_raw_position());
	commCurrentBaseState.set_base_velocity(COMP->state->getBaseState().get_base_velocity());

	commMobileLaserScan.set_base_state(commCurrentBaseState);
	commMobileLaserScan.set_scan_update_count(m_counter++);

	this->laserServiceOutPut(commMobileLaserScan);

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int SonarTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	if (m_queue != nullptr)
	{
		delete(m_queue);
		m_queue = nullptr;
	}
	return 0;
}
