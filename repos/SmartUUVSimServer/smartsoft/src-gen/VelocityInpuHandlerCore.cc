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
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#include "VelocityInpuHandlerCore.hh"
#include "VelocityInpuHandler.hh"

VelocityInpuHandlerCore::VelocityInpuHandlerCore(
	Smart::InputSubject<CommBasicObjects::CommNavigationVelocity> *subject,
	const int &prescaleFactor)
	:	Smart::InputTaskTrigger<CommBasicObjects::CommNavigationVelocity>(subject, prescaleFactor)
{  
	updateStatus = Smart::SMART_NODATA;
}
VelocityInpuHandlerCore::~VelocityInpuHandlerCore()
{  }

void VelocityInpuHandlerCore::updateAllCommObjects() {
}

void VelocityInpuHandlerCore::notify_all_interaction_observers() {
	std::unique_lock<std::mutex> lock(interaction_observers_mutex);
	// try dynamically down-casting this class to the derived class 
	// (we can do it safely here as we exactly know the derived class)
	if(const VelocityInpuHandler* velocityInpuHandler = dynamic_cast<const VelocityInpuHandler*>(this)) {
		for(auto it=interaction_observers.begin(); it!=interaction_observers.end(); it++) {
			(*it)->on_update_from(velocityInpuHandler);
		}
	}
}

void VelocityInpuHandlerCore::attach_interaction_observer(VelocityInpuHandlerObserverInterface *observer) {
	std::unique_lock<std::mutex> lock(interaction_observers_mutex);
	interaction_observers.push_back(observer);
}

void VelocityInpuHandlerCore::detach_interaction_observer(VelocityInpuHandlerObserverInterface *observer) {
	std::unique_lock<std::mutex> lock(interaction_observers_mutex);
	interaction_observers.remove(observer);
}
