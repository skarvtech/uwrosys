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

#include "BaseState.hh"
#include "ComponentUUVSimulator.hh"


BaseState::BaseState() {}

BaseState::~BaseState() {
	std::unique_lock<std::mutex> lck (m_mtx);
	std::cout << "Destroyed BaseState" << std::endl;
}

void BaseState::OnMsg(const nav_msgs::Odometry::ConstPtr &msg) {

	// !!! Do not use cout or sleep within this callback function !!!

		// Set BasePose object
		CommBasicObjects::CommBasePose commBasePose;

		// Set position
		commBasePose.set_x(msg->pose.pose.position.x, 1);
		commBasePose.set_y(msg->pose.pose.position.y, 1);
		commBasePose.set_z(msg->pose.pose.position.z, 1);

		// See https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
		double xsqr = msg->pose.pose.orientation.x * msg->pose.pose.orientation.x;
		double ysqr = msg->pose.pose.orientation.y * msg->pose.pose.orientation.y;
		double zsqr = msg->pose.pose.orientation.z * msg->pose.pose.orientation.z;

		// Set yaw
		double siny_cosp = +2.0 * (msg->pose.pose.orientation.w * msg->pose.pose.orientation.z + msg->pose.pose.orientation.x * msg->pose.pose.orientation.y);
		double cosy_cosp = +1.0 - 2.0 * (ysqr + zsqr);
		double yaw = std::atan2(siny_cosp, cosy_cosp);
		commBasePose.set_base_azimuth(yaw);

		// Set pitch
		double theta;
		double sinp = +2.0 * (msg->pose.pose.orientation.w * msg->pose.pose.orientation.y - msg->pose.pose.orientation.z * msg->pose.pose.orientation.x);
		if(std::abs(sinp) >= 1)
			theta = std::copysign(M_PI / 2, sinp); // Use 90 degrees if out of range
		else
			theta = std::asin(sinp);
		commBasePose.set_base_elevation(theta);

		// Set roll
		double sinr_cosp = +2.0 * (msg->pose.pose.orientation.w * msg->pose.pose.orientation.x + msg->pose.pose.orientation.y * msg->pose.pose.orientation.z);
		double cosr_cosp = +1.0 - 2.0 * (xsqr + ysqr);
		double roll = std::atan2(sinr_cosp, cosr_cosp);
		commBasePose.set_base_roll(roll);

		// Set BaseVelocity object
		CommBasicObjects::CommBaseVelocity commBaseVelocity;

		// Set linear velocity
		commBaseVelocity.set_vX(msg->twist.twist.linear.x, 1);
		commBaseVelocity.set_vY(msg->twist.twist.linear.y, 1);
		commBaseVelocity.set_vZ(msg->twist.twist.linear.z, 1);

		// Set angular velocity
		commBaseVelocity.set_WX_base(msg->twist.twist.angular.x);
		commBaseVelocity.set_WY_base(msg->twist.twist.angular.y);
		commBaseVelocity.set_WZ_base(msg->twist.twist.angular.z);

		// Copy pose and velocity
		std::unique_lock<std::mutex> lck (m_mtx);
		this->m_commBasePose = commBasePose;
		this->m_commBaseVelocity = commBaseVelocity;
}

void BaseState::init() {
	std::cout << "Initialized BaseState" << std::endl;
}

CommBasicObjects::CommBasePose BaseState::getBasePose() {
	std::unique_lock<std::mutex> lck (m_mtx);
	return this->m_commBasePose;
}

CommBasicObjects::CommBaseVelocity BaseState::getBaseVelocity() {
	std::unique_lock<std::mutex> lck (m_mtx);
	return this->m_commBaseVelocity;
}
