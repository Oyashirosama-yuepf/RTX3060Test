#input: $1 input directory which contains depth image & rgb image & ground truth pose
#       $2 config file
#       $3 output directory
#       $4 new folder name in the output directory, all evaluated result will be copied to this folder

export HOLO_LOG_ROOT_LOCALIZATION_VISION=$HOLO_ROOT/log/holo_localization_vision/

GroundTruthPoseFile="pose.txt"
DepthSubDir="dep/"
DepthImageList="dep.txt"
RGBSubDir="rgb/"
RGBImageList="rgb.txt"

mkdir $3
mkdir $HOLO_LOG_ROOT_LOCALIZATION_VISION
$HOLO_ROOT/bin/holo_localization_vision/benchmark_tracker \
    --file_pose $1/$GroundTruthPoseFile \
    --dir_depth $1/$DepthSubDir \
    --file_depth_list $1/$DepthImageList \
    --dir_rgb $1/$RGBSubDir \
    --file_rgb_list $1/$RGBImageList \
    --config_file $2

cp $1/*.txt $HOLO_LOG_ROOT_LOCALIZATION_VISION

matlab  -nosplash -nodesktop -r "run('matlab/benchmark_tracker.m'); exit;"

mkdir $3/$4
cp $HOLO_LOG_ROOT_LOCALIZATION_VISION*.* $3/$4
rm $HOLO_LOG_ROOT_LOCALIZATION_VISION*
