//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#include "BaseStateTask.hh"
#include "ComponentUUVSimulator.hh"

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

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int BaseStateTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
