# `uwrosys`: Source code for the UWROSYS ITP of RobMoSys

This repository contains the source code for running Skarv Technologies' UWROSYS project based on UUVSimulator. UWROSYS is an ITP supported through RobMoSys - a Horizon 2020 project.

# Installation

**Install docker:**
```
sudo apt-get install docker.io
```

# Useful make commands for running docker image

**Build docker image:**
```
cd <docker_directory>
make build
```

**Start terminal with possibility for GUI programs**
```
cd <docker_directory>
make interactive
```

**Run SmartMDSDD toolchain**
```
cd <docker_directory>
make toolchain
```

**Connect additional terminal to container (only works when container is running)**
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

# Set up toolchain
First run the make command for starting the toolchain. Once started, select:
File -> Import. Then select General -> Existing Projects into Workspace.
- Select folder containing RobMoSys-repos (~/SOFTWARE/smartsoft/repos)
- Select folder containing UWROSYS-repos (~/SOFTWARE/uwrosys)
