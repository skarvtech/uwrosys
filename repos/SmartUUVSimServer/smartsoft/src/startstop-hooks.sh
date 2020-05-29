#!/bin/bash

case "$1" in

pre-start)
	echo "Triggering pre-start hooks FROM COMPONENT SmartUUVSimServer ..."
	# Insert commands you want to call prior to starting the components
	
	echo -e "\n\n\n"
	bash $SMART_ROOT_ACE/repos/CustomRepository/DataRepository/gazebo/startGazebo.sh

	echo "Wait for Simulator to start..."
	sleep 10
	
;;

post-start)
	echo "Triggering post-start hooks FROM COMPONENT SmartUUVSimServer ..."
	# Insert commands you want to call after all components were started
;;

pre-stop)
	echo "Triggering pre-stop hooks FROM COMPONENT SmartUUVSimServer ..."
	# Insert commands you want to call before stopping all components
;;

post-stop)
	echo "Triggering post-stop hooks FROM COMPONENT SmartUUVSimServer ..."
	# Insert commands you want to call after all components were stopped
	
	killall gzserver
	killall gzclient
	
;;

*)
	echo "ERROR in $0: no such hook '$1'. Usage: $0 pre-start|post-start|pre-stop|post-stop"
;;

esac
