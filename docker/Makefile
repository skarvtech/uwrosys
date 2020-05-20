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

USER         := uwrosys
TAG          := uwrosys
VERSION      := 2020.05.1

build:
	docker build -t $(TAG):$(VERSION) .
	
interactive:
	xhost +local:root
	docker run -it --rm --net=host --privileged -u $(USER) \
			-e DISPLAY=$(DISPLAY) \
			-v /tmp/.X11-unix:/tmp/.X11-unix \
			--name $(TAG) $(TAG):$(VERSION)
			
connect:
	docker exec -it $(TAG) /bin/bash
	
clean:
	docker container prune
	
clean_all: 
	docker system prune --volumes
