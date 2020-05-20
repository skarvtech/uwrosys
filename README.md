# `uwrosys`: Source code for the UWROSYS ITP of RobMoSys

This repository contains the source code for running Skarv Technologies' UWROSYS project based on UUVSimulator. UWROSYS is an ITP supported through RobMoSys - a Horizon 2020 project.

# Installation

**Install docker:**
```
sudo apt-get install docker.io
```

**Build docker image:**
```
cd <docker_directory>
make build
```

**Run SmartMDSDD toolchain on local computer**
```
cd <docker_directory>
make toolchain
```

**Connect additional terminal to image (only works when container is running)**
```
cd <docker_directory>
make shell
```

**Clean stopped docker containers**
```
cd <docker_directory>
make clean
```

**Clean docker system (requires full rebuild of all images)**
```
cd <docker_directory>
make clean_system
```
