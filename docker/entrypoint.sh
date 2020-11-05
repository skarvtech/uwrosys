#!/bin/bash
# Copyright (c) 2020 Skarv Technologies AS
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Project: UWROSYS
#          RobMoSys, Horizon 2020
#
# Author: Petter Norgren
#

# Source environmental variables
source ~/.bashrc
source ~/.profile

#sudo /etc/init.d/dbus start
#dbus-daemon --session --fork

# Connect local repositories
mkdir -p $REPOS/CustomRepositories
ln -s /home/$(id -un)/SOFTWARE/$(id -un)/* $REPOS/CustomRepositories

# Fix git pull on start of docker
cd $CATKIN_WS_DIR/src/uuv_simulator
git pull
cd $CATKIN_WS_DIR
. /opt/ros/melodic/setup.bash
catkin_make && catkin_make install
cd $SWDIR

# Clean build on shared volume
/home/$(id -un)/SOFTWARE/$(id -un)/CleanBuild.sh

# Patch required component libaries
sed -i 's#FIND_PACKAGE(AceSmartSoft PATHS $ENV{SMART_ROOT_ACE}/build)#FIND_PACKAGE(AceSmartSoft PATHS $ENV{SMART_ROOT_ACE}/modules)#g' $SMART_ROOT_ACE/repos/ComponentRepository/SmartJoystickNavigation/smartsoft/CMakeLists.txt
sed -i 's#FIND_PACKAGE(AceSmartSoft PATHS $ENV{SMART_ROOT_ACE}/build)#FIND_PACKAGE(AceSmartSoft PATHS $ENV{SMART_ROOT_ACE}/modules)#g' $SMART_ROOT_ACE/repos/ComponentRepository/SmartPlannerBreadthFirstSearch/smartsoft/CMakeLists.txt
sed -i 's#FIND_PACKAGE(AceSmartSoft PATHS $ENV{SMART_ROOT_ACE}/build)#FIND_PACKAGE(AceSmartSoft PATHS $ENV{SMART_ROOT_ACE}/modules)#g' $SMART_ROOT_ACE/repos/ComponentRepository/SmartCdlServer/smartsoft/CMakeLists.txt
sed -i 's#FIND_PACKAGE(AceSmartSoft PATHS $ENV{SMART_ROOT_ACE}/build)#FIND_PACKAGE(AceSmartSoft PATHS $ENV{SMART_ROOT_ACE}/modules)#g' $SMART_ROOT_ACE/repos/ComponentRepository/SmartMapperGridMap/smartsoft/CMakeLists.txt

# Launch Eclipse
if [ "$1" == "toolchain" ] 
then
	$TOOLCHAIN_DIR/eclipse
else
	/bin/bash
fi
    
# Exit
exit 0
