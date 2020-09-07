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

#ifndef BASESTATE_HH_
#define BASESTATE_HH_

#include <aceSmartSoft.hh>

#include <CommBasicObjects/CommBaseState.hh>

#include <mutex>

class BaseState {
private:
	std::mutex m_mtx;
	CommBasicObjects::CommBaseState m_commBaseState;

public:
	BaseState();
	virtual ~BaseState();
	void init();
	void OnMsg(const CommBasicObjects::CommBaseState &msg);

	CommBasicObjects::CommBaseState getBaseState();
};

#endif /* BASESTATE_HH_ */
