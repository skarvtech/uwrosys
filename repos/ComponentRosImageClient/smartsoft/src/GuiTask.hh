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

#ifndef _GUITASK_HH
#define _GUITASK_HH

#include "GuiTaskCore.hh"

#include <mrpt/gui/CDisplayWindow.h>

class GuiTask  : public GuiTaskCore
{
private:
	mrpt::gui::CDisplayWindow* m_window;
public:
	GuiTask(SmartACE::SmartComponent *comp);
	virtual ~GuiTask();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();
};

#endif
