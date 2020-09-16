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
#ifndef _RGBIMAGEPUSHSERVICEINHANDLER_HH
#define _RGBIMAGEPUSHSERVICEINHANDLER_HH

#include "RGBImagePushServiceInHandlerCore.hh"
	
class RGBImagePushServiceInHandler  : public RGBImagePushServiceInHandlerCore
{		
public:
	RGBImagePushServiceInHandler(Smart::InputSubject<DomainVision::CommVideoImage> *subject, const int &prescaleFactor=1);
	virtual ~RGBImagePushServiceInHandler();
	
	virtual void on_RGBImagePushServiceIn(const DomainVision::CommVideoImage &input);
};

#endif