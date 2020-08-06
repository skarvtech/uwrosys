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
#include "RGBImagePushServiceInHandler.hh"
#include "ComponentRosImageClient.hh"

#include <iostream>

RGBImagePushServiceInHandler::RGBImagePushServiceInHandler(Smart::InputSubject<DomainVision::CommVideoImage> *subject, const int &prescaleFactor)
:	RGBImagePushServiceInHandlerCore(subject, prescaleFactor)
{
	std::cout << "constructor RGBImagePushServiceInHandler\n";
}
RGBImagePushServiceInHandler::~RGBImagePushServiceInHandler() 
{
	std::cout << "destructor RGBImagePushServiceInHandler\n";
}

void RGBImagePushServiceInHandler::on_RGBImagePushServiceIn(const DomainVision::CommVideoImage &input)
{
	// implement business logic here
	// (do not use blocking calls here, otherwise this might block the InputPort RGBImagePushServiceIn)
	COMP->guiTask->rgb_image_cb(input);
}
