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

#include "NavigationVelocity.hh"
#include "ComponentUUVSimulator.hh"


NavigationVelocity::NavigationVelocity() {}

NavigationVelocity::~NavigationVelocity() {
	std::unique_lock<std::mutex> lck (m_mtx);
	std::cout << "Destroyed NavigationVelocity" << std::endl;
}

void NavigationVelocity::OnMsg(const CommBasicObjects::CommNavigationVelocity &msg) {

	// !!! Do not use cout or sleep within this callback function !!!

	std::unique_lock<std::mutex> lck (m_mtx);
	this->m_commVelocity = msg;
}

CommBasicObjects::CommNavigationVelocity NavigationVelocity::getNavigationVelocity() {
	std::unique_lock<std::mutex> lck (m_mtx);
	return this->m_commVelocity;
}

void NavigationVelocity::init() {
	std::cout << "Initialized NavigationVelocity" << std::endl;
}
