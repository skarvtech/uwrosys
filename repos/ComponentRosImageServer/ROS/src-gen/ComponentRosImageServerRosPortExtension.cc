//--------------------------------------------------------------------------
// This file is generated by the SeRoNet Tooling. The SeRoNet Tooling is 
// developed by the SeRoNet Project consortium: 
// http://www.seronet-projekt.de
//
// The ROS Mixed-Port Component is developed by:
// Service Robotics Research Center of Ulm University of Applied Sciences
// Fraunhofer Institute for Manufacturing Engineering and Automation IPA
//
// This code-generator uses infrastructure of the SmartMDSD Toolchain on
// which the SeRoNet Tooling is based on.
//
// CAUTION: 
// This software is a preview for the purpose of technology demonstration. 
// It is experimental and comes with no support. Use at your own risk.
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------

#include "ComponentRosImageServerRosPortExtension.hh"

// statically create a global PlainOpcUaComponentRosImageServerExtension instance
static ComponentRosImageServerRosPortExtension ros_port_extension;

ComponentRosImageServerRosPortExtension::ComponentRosImageServerRosPortExtension()
:	ComponentRosImageServerExtension("ComponentRosImageServerRosPortExtension")
{
	nh = 0;
	callbacksPtr = 0;
}

ComponentRosImageServerRosPortExtension::~ComponentRosImageServerRosPortExtension()
{  }

void ComponentRosImageServerRosPortExtension::loadParameters(const SmartACE::SmartIniParameter &parameter)
{  }

void ComponentRosImageServerRosPortExtension::initialize(ComponentRosImageServer *component, int argc, char* argv[])
{
	ros::init(argc, argv, "ComponentRosImageServer", ros::init_options::NoSigintHandler);
	nh = new ros::NodeHandle();
	callbacksPtr = new ComponentRosImageServerRosPortCallbacks();
	component->rosPorts = this;
	
	_camera_image = nh->subscribe("/rexrov/rexrov/camera/camera_image", 10, &ComponentRosImageServerRosPortCallbacks::_camera_image_cb, callbacksPtr);
}


int ComponentRosImageServerRosPortExtension::onStartup()
{
	return startExtensionThread();
}

int ComponentRosImageServerRosPortExtension::extensionExecution()
{
	ros::spin();
	return 0;
}

int ComponentRosImageServerRosPortExtension::onShutdown(const std::chrono::steady_clock::duration &timeoutTime)
{
	ros::shutdown();
	return stopExtensionThread(timeoutTime);
}

void ComponentRosImageServerRosPortExtension::destroy()
{
	delete nh;
	delete callbacksPtr;
}
