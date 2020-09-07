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

#include "GuiTask.hh"
#include "ComponentRosImageClient.hh"

#include "ImageBuffer.hh"

#include <iostream>

GuiTask::GuiTask(SmartACE::SmartComponent *comp) 
:	GuiTaskCore(comp)
, 	m_window(NULL)
{
	std::cout << "constructor GuiTask\n";
}
GuiTask::~GuiTask() 
{
	std::cout << "destructor GuiTask\n";
}

int GuiTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	m_window = new mrpt::gui::CDisplayWindow("ROV Operator Viewer");
	return 0;
}
int GuiTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	// to get the incoming data, use this methods:
	Smart::StatusCode status;
	mrpt::utils::CImage image;

	if(COMP->image->getImage(image))
	{
		m_window->showImage(image);
	}

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int GuiTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	if (m_window != NULL)
	{
		delete m_window;
		m_window = NULL;
	}
	return 0;
}
