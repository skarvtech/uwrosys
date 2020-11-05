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

#include "BaseStateTask.hh"
#include "ComponentUUVSimulator.hh"

#include <geometry_msgs/Twist.h>

#include <iostream>

BaseStateTask::BaseStateTask(SmartACE::SmartComponent *comp) 
:	BaseStateTaskCore(comp)
{
	std::cout << "constructor BaseStateTask\n";
}
BaseStateTask::~BaseStateTask() 
{
	std::cout << "destructor BaseStateTask\n";
}

int BaseStateTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	return 0;
}
int BaseStateTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	CommBasicObjects::CommBaseState commCurrentBaseState;

	// get base pose and velocity from ROS
	if (COMP->state != NULL) {
		commCurrentBaseState.set_base_position(COMP->state->getBasePose());
		commCurrentBaseState.set_base_raw_position(COMP->state->getBasePose());
		commCurrentBaseState.set_base_velocity(COMP->state->getBaseVelocity());
	}
	else {
		std::cout << "Simulator has not yet started !" << std::endl;
	}

	// add timestamp
	CommBasicObjects::CommTimeStamp time_stamp;
	time_stamp.set_now();
	commCurrentBaseState.set_time_stamp(time_stamp);

	Smart::StatusCode status = this->baseStateServiceOutPut(commCurrentBaseState);

	std::cout << "Position: " << commCurrentBaseState.get_base_position() << std::endl;
	std::cout << "Velocity: " << commCurrentBaseState.get_base_velocity() << std::endl;

	CommBasicObjects::CommNavigationVelocity navvel;

	// get velocity command and publish
	if (COMP->navvel != NULL)
	{
		navvel = COMP->navvel->getNavigationVelocity();
		geometry_msgs::Twist cmd;
		cmd.linear.x = navvel.get_vX()/1000.0;
		cmd.linear.y = navvel.get_vY()/1000.0;
		cmd.linear.z = navvel.get_vZ()/1000.0;
		cmd.angular.x = 0;
		cmd.angular.y = 0;
		cmd.angular.z = navvel.get_omega();

		COMP->rosPorts->_cmd_vel.publish(cmd);
	}

	std::cout << "Commanded Velocity: " << navvel << std::endl;

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int BaseStateTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
