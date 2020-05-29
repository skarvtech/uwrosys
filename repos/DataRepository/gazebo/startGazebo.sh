#!/bin/bash

FROM=$(pwd)

if [ $# -eq 0 ]
  then
    	echo -n "
	Please choose a world to load:
	(0) Empty
	(1) Subsea BOP
	> "

	read WORLD

	case "$WORLD" in
		0)
		        echo "Selected empty world"
		        WORLD=0
		        ;;
		1)
		        echo "Selected Subsea BOP world"
		        WORLD=1
		        ;;
		*)
		        echo "Unknown World: '$WORLD'"
		        exit
		        ;;
	esac

	echo -n "
	Please choose a robot to load:
	(0) RexRov
	> "

	read ROBOT

	case "$ROBOT" in
		0)
		        echo "Selected RexRov"
		        if [ $WORLD -eq 0 ]; then
		        LAUNCH="uwros_empty_demo.launch"
		        elif [ $WORLD -eq 1 ]; then
		        LAUNCH="uwros_bop_demo.launch"
		        fi
		        ;;
		*)
		        echo "Unknown Robot: '$ROBOT'"
		        exit
		        ;;
	esac
	xterm -title "Gazebo Terminal" -e "pwd; roslaunch uuv_gazebo $LAUNCH || bash; sleep 5" &
  else
    xterm -title "Gazebo Terminal" -e "pwd; roslaunch uuv_gazebo $1 || bash; sleep 5" &
fi

cd $FROM
