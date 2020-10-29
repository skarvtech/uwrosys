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

USR          := uwrosys
TAG          := uwrosys_image
VERSION      := 2020.10.0
DOCKER_DIR   := $(realpath .)
SOURCE_DIR   := $(realpath ..)
USER_ID      := $(shell id -u)
GROUP_ID     := $(shell id -g)

build:
	echo $(USER_ID)
	echo $(GROUP_ID)
	docker build -t $(TAG):$(VERSION) \
			--build-arg USER_ID=$(USER_ID) \
			--build-arg GROUP_ID=$(GROUP_ID) .
	
interactive: 
	xhost +local:root
	docker run -it --rm --net=host --privileged -u $(USR) \
			-e DISPLAY=$(DISPLAY) \
			-v /tmp/.X11-unix:/tmp/.X11-unix \
			-v $(SOURCE_DIR):/home/$(USR)/SOFTWARE/$(USR) \
			--entrypoint entrypoint.sh \
			--name $(TAG) $(TAG):$(VERSION)

toolchain:
	xhost +local:root
	docker run -it --rm --net=host --privileged -u $(USR) \
			-e DISPLAY=$(DISPLAY) \
			-v /tmp/.X11-unix:/tmp/.X11-unix \
			-v $(SOURCE_DIR)/repos:/home/$(USR)/SOFTWARE/$(USR) \
			--name $(TAG) $(TAG):$(VERSION)

nvidia-interactive:
	xhost +local:root
	nvidia-docker run -it --rm --net=host --privileged -u $(USR) \
			-e DISPLAY=$(DISPLAY) \
      			-e NVIDIA_DRIVER_CAPABILITIES=compute,utility,graphics \
			-v /tmp/.X11-unix:/tmp/.X11-unix \
			-v $(SOURCE_DIR):/home/$(USR)/SOFTWARE/$(TAG) \
      			--entrypoint entrypoint.sh \
			--name $(TAG) $(TAG):$(VERSION)

nvidia-toolchain:
	xhost +local:root
	nvidia-docker run -it --rm --net=host --privileged -u $(USR) \
			-e DISPLAY=$(DISPLAY) \
      			-e NVIDIA_DRIVER_CAPABILITIES=compute,utility,graphics \
			-v /tmp/.X11-unix:/tmp/.X11-unix \
			-v $(SOURCE_DIR)/repos:/home/$(USR)/SOFTWARE/$(USR) \
			--name $(TAG) $(TAG):$(VERSION)

shell:
	docker exec -it $(TAG) /bin/bash

filebrowser:
	docker exec -it $(TAG) nautilus --browser /home/$(USR)/SOFTWARE

clean:
	docker container prune
	
clean_all: 
	docker system prune --volumes
