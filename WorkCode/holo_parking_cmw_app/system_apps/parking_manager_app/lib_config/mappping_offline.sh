#! /bin/bash
#source /opt/ros/melodic/setup.bash
#export ROS_MASTER_URI=http://192.168.1.3:11311
#export ROS_IP=192.168.1.3
#export HOLO_ROOT=/home/nvidia/holo_ws/output/native/relwithdebinfo/target
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HOLO_ROOT}/3rdparty/bazel-bin/tensorflow:${HOLO_ROOT}/3rdparty/torch/lib:/usr/local/cuda-10.0/lib64:${HOLO_ROOT}/3rdparty/lib:/opt/ros/melodic/lib:/usr/local/lib

# change offline mapping route_id
cd $HOLO_ROOT/config/holo_localization_parking/lib_config/app &&
offline_route_id=`cat visual_mapping.yaml | grep -oE "route_.*" | awk -F '"' '{print $1}' | head -n1 | awk -F '_' '{print $2}'` &&
sed -i "s/route_$offline_route_id/route_$1/g" visual_mapping.yaml &&
echo "Route id change to $1"


# mapping offline
cd $HOLO_ROOT ;source setup.bash;
HOLO_ROOT=$PWD ./bin/holo_localization_parking/visual_mapping -c config/holo_localization_parking/lib_config/app/visual_mapping.yaml
echo "success mapping offline"

# move map
#path=$HOLO_ROOT/config/holo_localization_vision/vslam
#mv $path/frames.bin $path/mappoints.bin $path/pcd.ply $path/vehicle_odometry.txt $path/front_wheel_angle.txt /home/nvidia/hpp/route_$1

sleep 3
path=/root
# echo $path

sshpass -p root scp -r root@192.168.1.2:/opt/holo/hpp/route_$1 /root
sleep 1

file_name=`date +%F-%H-%M-%S`
date=`date`

if [ -d "/opt/holo/hpp/route_$1" ]
then
#    file_name=`date +%F-%H-%M-%S`
#    date=`date`
    echo "This filder is exist!!!"
    mv /opt/holo/hpp/route_$1 /opt/holo/hpp/route_$1-$file_name
    echo "modify the original file name to route_$1-$file_name"
    # mkdir /opt/holo/hpp/route_$1
    # mv $path/frames.bin $path/mappoints.bin $path/pcd.ply $path/vehicle_odometry.txt $path/front_wheel_angle.txt /opt/holo/hpp/route_$1
#	rm -r $path/route_$1/features
	mv $path/route_$1 /opt/holo/hpp
    echo "Create mapping time is $file_name"
else
    echo "Create route_$1 folder"
    # mkdir /opt/holo/hpp/route_$1
    # mv $path/frames.bin $path/mappoints.bin $path/pcd.ply $path/vehicle_odometry.txt $path/front_wheel_angle.txt /opt/holo/hpp/route_$1
#	rm -r $path/route_$1/features
 	mv $path/route_$1 /opt/holo/hpp
    echo "Create mapping time is $file_name"
fi


echo "move_map suceess"


