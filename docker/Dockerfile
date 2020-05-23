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

#Download base image ubuntu 16.04
FROM ubuntu:xenial

# Update Ubuntu Software repository
USER root
ENV DEBIAN_FRONTEND=noninteractive 
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get full-upgrade -y

# Install necessary packages
RUN apt-get install -y build-essential python-pip git lsb-release wget cmake apt-utils nano sudo

ENV USR=uwrosys
ENV HOME=/home/$USR
RUN adduser $USR --home $HOME --shell /bin/bash --gecos "RobMoSys UWROSYS, , , " \
		--disabled-password
RUN echo "$USR:$USR" | chpasswd
RUN usermod -aG sudo $USR
RUN echo "$USR ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
RUN chown -R $USR:$USR $HOME
WORKDIR $HOME

# Install RobMoSys environment
USER $USR
RUN sudo apt-get update -y
RUN sudo apt-get install -y openjdk-8-jre libtbb-dev gparted gnome-session-flashback \ 
			gconf-editor cmake-curses-gui inkscape gimp mplayer qiv \ 
			nautilus-compare ssh-askpass flex bison htop tree subversion sbcl \
			doxygen meld expect wmctrl libopencv-dev libboost-all-dev libftdi-dev \
			libcv-dev libcvaux-dev libhighgui-dev pkg-config freeglut3-dev \
			zlib1g-dev zlibc libusb-1.0-0-dev libdc1394-22-dev libavformat-dev \
			libswscale-dev lib3ds-dev libjpeg-dev libgtest-dev libeigen3-dev \ 
			libglew-dev vim vim-gnome libxml2-dev libxml++2.6-dev libmrpt-dev ssh \
			sshfs xterm libjansson-dev libopencv-dev libgeos++-dev ruby ruby-dev \
			swig libgsl-dev libgnomecanvas2-dev libxmu-dev libxi-dev fltk1.3-dev

# Export environmental variables
ENV SWDIR=$HOME/SOFTWARE
ENV ACE_ROOT=/opt/ACE_wrappers
ENV SMART_ROOT_ACE=$SWDIR/smartsoft
ENV SMART_PACKAGE_PATH=$SMART_ROOT_ACE/repos
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SMART_ROOT_ACE/lib
RUN /bin/bash -c "touch ~/.profile"
RUN echo "export ACE_ROOT=$ACE_ROOT" >> ~/.profile
RUN echo "export SMART_ROOT_ACE=$SMART_ROOT_ACE" >> ~/.profile
RUN echo "export SMART_PACKAGE_PATH=$SMART_PACKAGE_PATH" >> ~/.profile
RUN echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH" >> ~/.profile
RUN /bin/bash -c "source ~/.profile" 

# Set up folder structure
ENV SMARTSOFT=$SWDIR/smartsoft-ace-mdsd-v3
RUN mkdir -p $SMARTSOFT/repos && chown -R $USR:$USR $SMARTSOFT/repos
RUN mkdir -p $SMARTSOFT/include && chown -R $USR:$USR $SMARTSOFT/include
RUN mkdir -p $SMARTSOFT/modules && chown -R $USR:$USR $SMARTSOFT/modules
RUN mkdir -p $SMARTSOFT/lib && chown -R $USR:$USR $SMARTSOFT/lib
RUN mkdir -p $SMARTSOFT/CMakeMacros && chown -R $USR:$USR $SMARTSOFT/CMakeMacros
RUN mkdir -p $SMARTSOFT/bin && chown -R $USR:$USR $SMARTSOFT/bin
ENV REPOS=$SMARTSOFT/repos
WORKDIR $REPOS
RUN ln -s $SMARTSOFT $SWDIR/smartsoft

# Clone git repositories
RUN git clone https://github.com/Servicerobotics-Ulm/SmartSoftComponentDeveloperAPIcpp.git
RUN git clone https://github.com/Servicerobotics-Ulm/AceSmartSoftFramework.git
RUN git clone https://github.com/Servicerobotics-Ulm/UtilityRepository.git
RUN git clone https://github.com/Servicerobotics-Ulm/DataRepository.git
RUN git clone https://github.com/Servicerobotics-Ulm/DomainModelsRepositories.git
RUN git clone https://github.com/Servicerobotics-Ulm/ComponentRepository.git
RUN git clone https://github.com/Servicerobotics-Ulm/SystemRepository.git
RUN git clone https://github.com/Servicerobotics-Ulm/BehaviorRepository.git

# Install ACE
RUN wget -nv https://github.com/Servicerobotics-Ulm/AceSmartSoftFramework/raw/master/INSTALL-ACE-6.0.2.sh -O /tmp/INSTALL-ACE-6.0.2.sh
RUN chmod +x /tmp/INSTALL-ACE-6.0.2.sh
RUN sudo /tmp/INSTALL-ACE-6.0.2.sh /opt
RUN sudo bash -c 'echo "/opt/ACE_wrappers/lib" > /etc/ld.so.conf.d/ace.conf'
RUN sudo ldconfig

# Build SmartSoftComponentDeveloperAPIcpp
RUN mkdir -p $REPOS/SmartSoftComponentDeveloperAPIcpp/build \ 
	&& chown -R $USR:$USR $REPOS/SmartSoftComponentDeveloperAPIcpp/build
WORKDIR $REPOS/SmartSoftComponentDeveloperAPIcpp/build
RUN git reset --hard a5db675daa35bbac095b2e6bf31893fec7890185
RUN cmake ..
RUN make && sudo make install

# Build AceSmartSoftFramework
RUN mkdir -p $REPOS/AceSmartSoftFramework/build \ 
	&& chown -R $USR:$USR $REPOS/AceSmartSoftFramework/build
WORKDIR $REPOS/AceSmartSoftFramework/build
RUN git reset --hard 5d32d0c712da5414cf1d5cce5e0d88e993758783
RUN cmake ..
RUN make && sudo make install

# Build UtilityRepository
RUN mkdir -p $REPOS/UtilityRepository/build \ 
	&& chown -R $USR:$USR $REPOS/UtilityRepository/build
WORKDIR $REPOS/UtilityRepository/build
RUN git reset --hard 9e6e271b933785042daaf8fc67c6941e85b7f89a
RUN cmake ..
RUN make -j8

# Build DomainModelsRepositories
RUN chown -hR $USR:$USR $REPOS/DomainModelsRepositories/*
RUN mkdir -p $REPOS/DomainModelsRepositories/build \ 
	&& chown -R $USR:$USR $REPOS/DomainModelsRepositories/build
WORKDIR $REPOS/DomainModelsRepositories/build
RUN git reset --hard 4b7eb71da3028d7eaf291939316f67c59fb3ad37
RUN cmake ..
RUN make

# Build ComponentRepository
RUN chown -hR $USR:$USR $REPOS/ComponentRepository/*
RUN mkdir -p $REPOS/ComponentRepository/build \ 
	&& chown -R $USR:$USR $REPOS/ComponentRepository/build
WORKDIR $REPOS/ComponentRepository/build
RUN git reset --hard 5bf5a82aeafbf352627eb45a7885addcc02acc03
RUN cmake ..
RUN make -j8

WORKDIR $REPOS/DataRepository
RUN git reset --hard 3c7606d3e053838597c50880b1ff5ea9cb3bb830
WORKDIR $REPOS/SystemRepository
RUN git reset --hard 30cae74a27e8250ee599a3bbef3918dcd76f729b
WORKDIR $REPOS/BehaviorRepository
RUN git reset --hard da93f71a80b97d0b61db34036ddac8b61ae9b967

# Install SmartMDSD Toolchain
ENV TOOLCHAIN_NAME="SmartMDSD-Toolchain"
ENV TOOLCHAIN_VERSION="3.12"
ENV TOOLCHAIN_DIR=$SWDIR/$TOOLCHAIN_NAME-v$TOOLCHAIN_VERSION
ENV TOOLCHAIN_URL="https://github.com/Servicerobotics-Ulm/SmartMDSD-Toolchain/releases/download/v$TOOLCHAIN_VERSION/SmartMDSD-Toolchain-v$TOOLCHAIN_VERSION.tar.gz"
ENV TOOLCHAIN_LAUNCHER="$TOOLCHAIN_NAME.desktop"
RUN mkdir -p $TOOLCHAIN_DIR && chown -R $USR:$USR $TOOLCHAIN_DIR
RUN wget -nv $TOOLCHAIN_URL -P $SWDIR
RUN tar -xzf $SWDIR/$TOOLCHAIN_NAME-v$TOOLCHAIN_VERSION.tar.gz -C $SWDIR
RUN echo "export TOOLCHAIN_DIR=$TOOLCHAIN_DIR" >> ~/.profile

# Install ROS
RUN sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
RUN sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
RUN sudo apt-get update
RUN sudo apt-get install -y ros-kinetic-desktop-full
RUN echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
RUN /bin/bash -c "source ~/.bashrc"
RUN sudo apt-get install -y python-rosdep python-rosinstall python-rosinstall-generator \
		python-wstool python-catkin-tools
RUN sudo rosdep init
RUN rosdep update

# Install UUVSimulator
ENV CATKIN_WS_DIR=$SWDIR/catkin_ws
RUN mkdir -p $CATKIN_WS_DIR/src && chown -R $USR:$USR $CATKIN_WS_DIR/src
WORKDIR $CATKIN_WS_DIR
RUN catkin init
WORKDIR $CATKIN_WS_DIR/src
RUN git clone https://github.com/uuvsimulator/uuv_simulator.git
RUN echo "source /usr/share/gazebo-7/setup.sh" >> ~/.bashrc
RUN echo "source $CATKIN_WS_DIR/devel/setup.bash" >> ~/.bashrc
RUN /bin/bash -c "source ~/.bashrc"
WORKDIR $CATKIN_WS_DIR
RUN rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y
RUN /bin/bash -c ". /opt/ros/kinetic/setup.bash; cd $CATKIN_WS_DIR; catkin_make"
RUN /bin/bash -c ". /opt/ros/kinetic/setup.bash; cd $CATKIN_WS_DIR; catkin_make install"

# Expose ssh port
EXPOSE 22

# Set up RobMoSys entrypoint
WORKDIR $SWDIR
RUN sudo chown -HR $USR:$USR $SWDIR
COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN sudo ln -s /usr/local/bin/entrypoint.sh /bin/entrypoint.sh
ENTRYPOINT ["entrypoint.sh"]

