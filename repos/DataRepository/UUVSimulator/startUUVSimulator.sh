#!/bin/bash

FROM=$(pwd)

if [ $# -eq 0 ]
  then
    	echo -n "
	Please choose a world to load:
	(0) Empty
	(1) UWROSYS BOP
	> "

	read WORLD

	case "$WORLD" in
		0)
		        echo "Selected empty world"
		        WORLD="ocean_waves.launch"
		        ;;
		1)
		        echo "Selected UWROSYS BOP world"
		        WORLD="uwrosys_underwater_world.launch"
		        ;;
		*)
		        echo "Unknown World: '$WORLD'"
		        exit
		        ;;
	esac

	echo -n "
	Please choose a robot to load:
	(0) RexRov
  (1) RexRov with manipulator arms
	> "

	read ROBOT

	case "$ROBOT" in
		0)
		        echo "Selected RexRov"
            ROBOT="rexrov_default.launch"
		        ;;
    1)
		        echo "Selected RexRov with manipulator arms"
            ROBOT="uwrosys_rexrov_oberon_arms.launch"
		        ;;
		*)
		        echo "Unknown Robot: '$ROBOT'"
		        exit
		        ;;
	esac
	
else
  WORLD=$1
  ROBOT=$2
fi

echo -e "Starting UUVSimulator...\n"
xterm -title "Gazebo Terminal" -e "pwd; roslaunch --wait uuv_gazebo_worlds $WORLD; exit || bash; sleep 30; exit" &

echo -e "Waiting for simulator to start... \n"
sleep 10

echo -e "Spawning RexROV...\n"
xterm -title "RexROV Terminal" -e "pwd; roslaunch --wait uuv_gazebo $ROBOT; sleep 30; exit || bash; sleep 30; exit" &

cd $FROM
