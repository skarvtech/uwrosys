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

#Download base image ubuntu 18.04 with Nvidia OpenGL support
FROM nvidia/opengl:1.0-glvnd-devel-ubuntu18.04

# Update Ubuntu Software repository
USER root
ENV DEBIAN_FRONTEND=noninteractive 
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get full-upgrade -y

# Install necessary packages
ENV TZ=Europe/Oslo
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get install -y apt-utils tzdata build-essential python-pip git lsb-release wget cmake nano sudo

ARG USER_ID
ARG GROUP_ID
ENV USR=uwrosys
ENV HOME=/home/$USR
RUN addgroup --gid $GROUP_ID $USR
RUN adduser $USR --uid $USER_ID --gid $GROUP_ID --home $HOME --shell /bin/bash \
		--gecos "RobMoSys UWROSYS, , , " --disabled-password
RUN echo "$USR:$USR" | chpasswd
RUN usermod -aG sudo $USR
RUN echo "$USR ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
RUN chown -R $USR:$USR $HOME
WORKDIR $HOME
USER $USR

# Install RobMoSys environment
RUN sudo apt-get update -y
RUN sudo apt-get install -y openjdk-8-jre libtbb-dev gparted gnome-session-flashback \ 
			gconf-editor cmake-curses-gui inkscape gimp mplayer qiv pkg-config freeglut3-dev \ 
			nautilus-compare ssh-askpass flex bison htop tree subversion sbcl \
			doxygen meld expect wmctrl libopencv-dev libboost-all-dev libftdi-dev \
			zlib1g-dev zlibc libusb-1.0-0-dev libdc1394-22-dev libavformat-dev \
			libswscale-dev lib3ds-dev libjpeg-dev libgtest-dev libeigen3-dev \ 
			libglew-dev vim vim-gnome libxml2-dev libxml++2.6-dev libmrpt-dev ssh \
			sshfs xterm libjansson-dev libopencv-dev libgeos++-dev ruby ruby-dev \
			swig libgsl-dev libgnomecanvas2-dev libxmu-dev libxi-dev fltk1.3-dev \
      			libmrpt-dev mrpt-apps libopencv-dev

# Export environmental variables
ENV SWDIR=$HOME/SOFTWARE
ENV SMART_ROOT_ACE=$SWDIR/smartsoft
ENV SMART_PACKAGE_PATH=$SMART_ROOT_ACE/repos
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SMART_ROOT_ACE/lib
RUN /bin/bash -c "touch ~/.profile"
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
RUN git clone https://github.com/skarvtech/DomainModelsRepositories.git
RUN git clone https://github.com/skarvtech/ComponentRepository.git
RUN git clone https://github.com/Servicerobotics-Ulm/SystemRepository.git
RUN git clone https://github.com/Servicerobotics-Ulm/BehaviorRepository.git

# Install ACE
RUN sudo apt-get install -y ace libace-dev
RUN sudo /bin/bash -c 'source ~/.profile && echo $SMART_ROOT_ACE/lib >> /etc/ld.so.conf.d/smartsoft.conf'
RUN sudo ldconfig

# Build SmartSoftComponentDeveloperAPIcpp
RUN mkdir -p $REPOS/SmartSoftComponentDeveloperAPIcpp/build \ 
	&& chown -R $USR:$USR $REPOS/SmartSoftComponentDeveloperAPIcpp/build
WORKDIR $REPOS/SmartSoftComponentDeveloperAPIcpp/build
RUN git reset --hard 888378e8fde5ae042691d15be20f0c94de91d2db
RUN cmake ..
RUN make && sudo make install

# Build AceSmartSoftFramework
RUN mkdir -p $REPOS/AceSmartSoftFramework/build \ 
	&& chown -R $USR:$USR $REPOS/AceSmartSoftFramework/build
WORKDIR $REPOS/AceSmartSoftFramework/build
RUN git reset --hard 4ea12710364679af33550a4dc405391211a6c632
RUN cmake ..
RUN make && sudo make install

# Build UtilityRepository
RUN mkdir -p $REPOS/UtilityRepository/build \ 
	&& chown -R $USR:$USR $REPOS/UtilityRepository/build
WORKDIR $REPOS/UtilityRepository/build
RUN git reset --hard aa17765a833403145e62938ff3652a2dd73a451a
RUN cmake ..
RUN make -j8

# Build DomainModelsRepositories
RUN chown -hR $USR:$USR $REPOS/DomainModelsRepositories/*
RUN mkdir -p $REPOS/DomainModelsRepositories/build \ 
	&& chown -R $USR:$USR $REPOS/DomainModelsRepositories/build
WORKDIR $REPOS/DomainModelsRepositories/build
RUN cmake ..
RUN make

# Build ComponentRepository
RUN chown -hR $USR:$USR $REPOS/ComponentRepository/*
RUN mkdir -p $REPOS/ComponentRepository/build \ 
	&& chown -R $USR:$USR $REPOS/ComponentRepository/build
WORKDIR $REPOS/ComponentRepository/build
RUN cmake ..
RUN make -j8

WORKDIR $REPOS/DataRepository
RUN git reset --hard 3c7606d3e053838597c50880b1ff5ea9cb3bb830
WORKDIR $REPOS/SystemRepository
RUN git reset --hard 3a67adb450e619baf844a7a5df079d3c9113928e
WORKDIR $REPOS/BehaviorRepository
RUN git reset --hard af3b9cb4743e78744a12f73d98fde830b9d51be0

# Install SmartMDSD Toolchain
RUN sudo apt-get install -y curl
ENV TOOLCHAIN_NAME="SmartMDSD-Toolchain"
ENV TOOLCHAIN_VERSION="3.13"
ENV TOOLCHAIN_DIR=$SWDIR/$TOOLCHAIN_NAME-v$TOOLCHAIN_VERSION
ENV TOOLCHAIN_URL="https://github.com/Servicerobotics-Ulm/SmartMDSD-Toolchain/releases/download/v$TOOLCHAIN_VERSION/SmartMDSD-Toolchain-v$TOOLCHAIN_VERSION.tar.gz"
ENV TOOLCHAIN_LAUNCHER="$TOOLCHAIN_NAME.desktop"
RUN mkdir -p $TOOLCHAIN_DIR && chown -R $USR:$USR $TOOLCHAIN_DIR
ENV TOOLCHAIN_FILENAME=$SWDIR/$TOOLCHAIN_NAME-v$TOOLCHAIN_VERSION.tar.gz
RUN curl "${TOOLCHAIN_URL}" -L -o "${TOOLCHAIN_FILENAME}"
RUN tar -xzf $TOOLCHAIN_FILENAME -C $SWDIR
RUN echo "export TOOLCHAIN_DIR=$TOOLCHAIN_DIR" >> ~/.profile

# Install ROS
ENV ROS_DISTRO=melodic
ENV GAZEBO_VERSION=9
RUN sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
RUN sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
RUN sudo apt-get update
RUN sudo apt-get install -y ros-$ROS_DISTRO-desktop-full
RUN echo "source /opt/ros/$ROS_DISTRO/setup.bash" >> ~/.bashrc
RUN /bin/bash -c "source ~/.bashrc"
RUN sudo apt-get install -y python-rosdep python-rosinstall python-rosinstall-generator \
		python-wstool python-catkin-tools jstest-gtk ros-$ROS_DISTRO-kdl-parser-py ros-$ROS_DISTRO-effort-controllers
RUN sudo rosdep init
RUN rosdep update

# Install UUVSimulator
ENV CATKIN_WS_DIR=$SWDIR/catkin_ws
RUN mkdir -p $CATKIN_WS_DIR/src && chown -R $USR:$USR $CATKIN_WS_DIR/src
WORKDIR $CATKIN_WS_DIR
RUN catkin init
WORKDIR $CATKIN_WS_DIR/src
RUN git clone https://github.com/uuvsimulator/uuv_manipulators.git
RUN git clone https://github.com/skarvtech/uuv_simulator.git
WORKDIR $CATKIN_WS_DIR/src/uuv_simulator
RUN git checkout projects/uwrosys
RUN echo "source /usr/share/gazebo-$GAZEBO_VERSION/setup.sh" >> ~/.bashrc
RUN echo "source $CATKIN_WS_DIR/devel/setup.bash" >> ~/.bashrc
RUN /bin/bash -c "source ~/.bashrc"
WORKDIR $CATKIN_WS_DIR
RUN rosdep install --from-paths src --ignore-src --rosdistro=$ROS_DISTRO -y
RUN /bin/bash -c ". /opt/ros/$ROS_DISTRO/setup.bash; cd $CATKIN_WS_DIR; catkin_make"
RUN /bin/bash -c ". /opt/ros/$ROS_DISTRO/setup.bash; cd $CATKIN_WS_DIR; catkin_make install"

# Make sure correct permissions are set for SWDIR
RUN sudo chown -HR $USR:$USR $SWDIR

# Expose ssh port
EXPOSE 22

# Fix Gazebo drawing bug
RUN echo "export QT_X11_NO_MITSHM=1" >> ~/.bashrc

# Set default keyboard
RUN sudo /bin/bash -c 'echo -e "\x23 KEYBOARD CONFIGURATION FILE\n" >> /etc/default/keyboard'
RUN sudo /bin/bash -c 'echo -e "\x23 Consult the keyboard\x285\x29 manual page.\n" >> /etc/default/keyboard'
RUN sudo /bin/bash -c 'echo -e "XKBMODEL=\x22pc105\x22" >> /etc/default/keyboard'
RUN sudo /bin/bash -c 'echo -e "XKBLAYOUT=\x22no\x22" >> /etc/default/keyboard'
RUN sudo /bin/bash -c 'echo -e "XKBVARIANT=\x22\x22" >> /etc/default/keyboard'
RUN sudo /bin/bash -c 'echo -e "XKBOPTIONS=\x22\x22\n" >> /etc/default/keyboard'
RUN sudo /bin/bash -c 'echo -e "BACKSPACE=\x22guess\x22" >> /etc/default/keyboard'

# Install convenient tools
RUN sudo apt-get update
RUN sudo apt-get install -y gedit xterm rsync

# Color support in terminal
ENV TERM=xterm-256color

# Cleanup
RUN rm $SWDIR/SmartMDSD-Toolchain-v$TOOLCHAIN_VERSION.tar.gz

# Set up RobMoSys entrypoint
WORKDIR $SWDIR
COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN sudo ln -s /usr/local/bin/entrypoint.sh /bin/entrypoint.sh
ENTRYPOINT ["entrypoint.sh", "toolchain"]

