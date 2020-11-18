smartsoft_dir=$(dirname "$0")/repos/SystemUwrosysDemo/smartsoft
cd smartsoft_dir
bash ./src-gen/deployment/deploy-all.sh
bash ./src-gen/deployment/start-all.sh
exit 0
