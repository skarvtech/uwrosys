#!/bin/bash

smartsoft_dir=$(dirname "$0")/repos/SystemUwrosysDemo/smartsoft
cd $smartsoft_dir
#chmod +rx ./src-gen/deployment/combine_ini_files.sh
#chmod +rx ./src-gen/deployment/deploy-PC1.sh
chmod +x ./src-gen/deployment/start-all.sh
bash ./src-gen/deployment/combine_ini_files.sh
bash ./src-gen/deployment/deploy-PC1.sh
#bash -c './src-gen/deployment/start-all.sh menu-start'
xterm -title "Global Scenario Control" -e "cd src-gen/deployment; pwd; bash start-all.sh menu;echo;echo;echo;echo 'You can close this window now.'; echo; echo;bash --login"
exit 0
