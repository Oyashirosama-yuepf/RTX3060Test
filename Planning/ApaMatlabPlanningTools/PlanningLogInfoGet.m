clear;
clc;

% p = parpool('local',4);   % 多核计算
% delete(gcp('nocreate'));  % 关闭多核计算
% origindatatest1 = readcell("1.csv");
% origindata = importdata("planning.log");
tic;
log_file = 'holo_planning.log';

%configure
flag_plot_path = 1;  %使能绘制path信息
flag_plot_slot = 1;  %使能绘制车位信息
flag_plot_slot_stopper = 1; %使能绘制车位内的停车点信息
flag_plot_freespace = 0;  %使能绘制freespace信息
flag_plot_obstacle = 1;   %使能绘制障碍物信息
flag_plot_odo_and_vehicle = 1;  %使能绘制车辆实时位置信息

%车身尺寸 取后轴中心为原点，然后向四个方向延展开。
vehicle.verticle0 = [3.58;-0.9];
vehicle.verticle1 = [3.58;0.9];
vehicle.verticle2 = [-1;0.9];
vehicle.verticle3 = [-1;-0.9];

%关键信息获取
if flag_plot_path == 1
    fid_log = fopen(log_file,'r');  %path信息
    [path_info_array] = path_info_get(fid_log);
    fid_log = fclose(fid_log);
end

if flag_plot_slot == 1
    fid_log = fopen(log_file,'r');  %车位信息
    [slot_info] = slot_info_get(fid_log);
    fid_log = fclose(fid_log);
end

if flag_plot_slot_stopper == 1
    fid_log = fopen(log_file,'r');  %车位内的stopper信息
    [stopper_array] = stopper_info_get(fid_log);
    fid_log = fclose(fid_log);
end

if flag_plot_obstacle == 1
    fid_log = fopen(log_file,'r');  %障碍物触发时的位置信息
    [obstacle_point_group] = obs_point_info_get(fid_log);
    fid_log = fclose(fid_log);
    fid_log = fopen(log_file,'r');  %障碍物的信息
    [obstacle_point_array] = obs_info_get(fid_log);
    fid_log = fclose(fid_log);
end

if flag_plot_freespace == 1
    fid_log = fopen(log_file,'r');  %freespace触发时的位置信息
    [freespace_point_group] = freespace_point_info_get(fid_log);
    fid_log = fclose(fid_log);
    fid_log = fopen(log_file,'r');  %freespace的信息
    [freespace_point_array] = freespace_info_get(fid_log);
    fid_log = fclose(fid_log);
end

if flag_plot_odo_and_vehicle == 1
    fid_log = fopen(log_file,'r');  %车辆位置信息
    [vehicle_position_array] = vehicle_position_info_get(fid_log);
    fid_log = fclose(fid_log);
    
    fid_log = fopen(log_file, 'r'); %车辆姿态信息
    [vehicle_pose_array] = vehicle_pose_info_get(fid_log,vehicle);
    fid_log = fclose(fid_log);
end

%车辆的四个角点
vehicle_position_array.x0 = vehicle_position_array.x+vehicle_pose_array.verticle0_t.x;
vehicle_position_array.y0 = vehicle_position_array.y+vehicle_pose_array.verticle0_t.y;
vehicle_position_array.x1 = vehicle_position_array.x+vehicle_pose_array.verticle1_t.x;
vehicle_position_array.y1 = vehicle_position_array.y+vehicle_pose_array.verticle1_t.y;
vehicle_position_array.x2 = vehicle_position_array.x+vehicle_pose_array.verticle2_t.x;
vehicle_position_array.y2 = vehicle_position_array.y+vehicle_pose_array.verticle2_t.y;
vehicle_position_array.x3 = vehicle_position_array.x+vehicle_pose_array.verticle3_t.x;
vehicle_position_array.y3 = vehicle_position_array.y+vehicle_pose_array.verticle3_t.y;

if flag_plot_path == 1
    choose_index_1 = size(path_info_array);
    choose_index_1 = choose_index_1(2);
    choose_index_2 = size(slot_info);
    choose_index_2 = choose_index_2(2);
    choose_index = min(choose_index_1, choose_index_2);
    %path info摘取零速度段
    zv_i = 1;      % 记录零速度段的索引
    for i = 1 : choose_index
        for j = 1 : size(path_info_array(i).x,2)
            if path_info_array(i).speed(j) == 0
                path_info_array(i).x_zv(zv_i) = path_info_array(i).x(j);
                path_info_array(i).y_zv(zv_i) = path_info_array(i).y(j);
                zv_i = zv_i +1;
            end
        end
        zv_i = 1;
    end
end

if flag_plot_obstacle == 1
    %区分每一个障碍物的信息，但是单帧可能存在多个障碍物，此处筛选出不同的障碍物
    j = 1;
    k = 1;
    for i = 1 : 1 : max(max(size(obstacle_point_array))) - 1
        obstacle_point_group(j).single_obs.x(k) = obstacle_point_array(i).x;
        obstacle_point_group(j).single_obs.y(k) = obstacle_point_array(i).y;
        obstacle_point_group(j).single_obs.distance(k) = obstacle_point_array(i).distance;
        k = k + 1;
        if obstacle_point_array(i + 1).count == 1   % 下一个count是1 说明已经到了当前obs的最后一个点,那么障碍物号+1
           j = j + 1;
           k = 1;
        end
    end
    %将同一帧内的不同障碍物汇总,用于后续单帧绘制
    j = 1;
    obstacle_point_group(j).single_frame.x = [];
    obstacle_point_group(j).single_frame.y = [];
    for i = 1 : 1 : max(max(size(obstacle_point_group))) - 1
        obstacle_point_group(j).single_frame.x = [obstacle_point_group(j).single_frame.x, obstacle_point_group(i).single_obs.x];
        obstacle_point_group(j).single_frame.y = [obstacle_point_group(j).single_frame.y, obstacle_point_group(i).single_obs.y];
         obstacle_point_group(j).single_frame.timestamp = obstacle_point_group(j).single_obs.timestamp;
        if abs(obstacle_point_group(i + 1).single_obs.timestamp - obstacle_point_group(i).single_obs.timestamp) >= 0.09   %打印时间戳超过90ms 认为已经到了下一帧
            j = j + 1;
            obstacle_point_group(j).single_frame.x = [];
            obstacle_point_group(j).single_frame.y = [];
        end
    end
    obstacle_point_group_frame_num = j - 1;
end


if flag_plot_freespace == 1
    %区分每一帧的freespace信息
    total_frame_num =  max(size(freespace_point_array.count)) / max(freespace_point_array.count); %判断一共输入了多少帧freespace
    single_frame_point_num = max(freespace_point_array.count); % 单帧有多少个点
    for j = 1 : 1 : total_frame_num
        for i = 1 : 1 : single_frame_point_num  %单帧区分
            freespace_point_group(j).single_frame.x(i) = freespace_point_array.x((j - 1) * single_frame_point_num + i);
            freespace_point_group(j).single_frame.y(i) = freespace_point_array.y((j - 1) * single_frame_point_num + i);
        end
    end
end

%axis square;
toc;

%获取车辆姿态信息
function [vehicle_pose_array] = vehicle_pose_info_get(fid_log,vehicle)
    vehicle_pose_group = 0;
    while ~feof(fid_log)
        log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
        feature_content = 'odometryd: pose3: (';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 10);   %在完整log中找到指定行
        if status == 1
            vehicle_pose_group = vehicle_pose_group +1;
            feature_content = '0726 ';
            [status, time_s_info, time_s_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = 'PID:';
            [status, time_e_info, time_e_index] = find_info(log_content, feature_content, 0, 0);
            time_info = log_content(time_s_index + 4 : time_e_index - 1);
            feature_content = ': (rot3: (';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ', 1)';
            [status, z_info, z_index] = find_info(log_content, feature_content, 0, 0);
            xyposition = log_content(x_index + 10 : z_index + 2);    % 摘取x y坐标，以字符串摘出，此时两数之间以"，"为间隔
            [vehicle_pose.r11, xyposition] = strtok(xyposition,',');  % [token, remainder] = strtok(string, delimiters)
            [vehicle_pose.r12, xyposition] = strtok(xyposition,',');  % [token, remainder] = strtok(string, delimiters)
            [vehicle_pose.r13, xyposition] = strtok(xyposition,',');  % [token, remainder] = strtok(string, delimiters)
            [vehicle_pose.r21, xyposition] = strtok(xyposition,',');  % [token, remainder] = strtok(string, delimiters)
            [vehicle_pose.r22, xyposition] = strtok(xyposition,',');  % [token, remainder] = strtok(string, delimiters)
            [vehicle_pose.r23, xyposition] = strtok(xyposition,',');  % [token, remainder] = strtok(string, delimiters)
            [vehicle_pose.r31, xyposition] = strtok(xyposition,',');  % [token, remainder] = strtok(string, delimiters)
            [vehicle_pose.r32, vehicle_pose.r33] = strtok(xyposition,',');  % [token, remainder] = strtok(string, delimiters)
            vehicle_pose.r11 = str2num(vehicle_pose.r11);
            vehicle_pose.r12 = str2num(vehicle_pose.r12);
            vehicle_pose.r13 = str2num(vehicle_pose.r13);
            vehicle_pose.r21 = str2num(vehicle_pose.r21);
            vehicle_pose.r22 = str2num(vehicle_pose.r22);
            vehicle_pose.r23 = str2num(vehicle_pose.r23);
            vehicle_pose.r31 = str2num(vehicle_pose.r31);
            vehicle_pose.r32 = str2num(vehicle_pose.r32);
            vehicle_pose.r33 = str2num(vehicle_pose.r33);
    
            theta1 = acosd(vehicle_pose.r11);
            theta2 = asind(vehicle_pose.r12);
            vehicle_pose_array.vehicle_pose_group(vehicle_pose_group) = vehicle_pose_group;
            vehicle_pose_array.theta(vehicle_pose_group) = (theta2 + theta1) / 2 - 90;
            %计算车辆四个角点的位置变化，即车辆的旋转情况，后面再在绘制图像时加上odometry的平移情况，可以得到车辆的四个角点信息
            vehicle_pose_rotate = [vehicle_pose.r11, vehicle_pose.r12; vehicle_pose.r21, vehicle_pose.r22];
            verticle0_transit = vehicle_pose_rotate * vehicle.verticle0;
            verticle1_transit = vehicle_pose_rotate * vehicle.verticle1;
            verticle2_transit = vehicle_pose_rotate * vehicle.verticle2;
            verticle3_transit = vehicle_pose_rotate * vehicle.verticle3;
            
            vehicle_pose_array.timeinfo.hour(vehicle_pose_group) = str2num(time_info(2:3));
            vehicle_pose_array.timeinfo.minute(vehicle_pose_group) = str2num(time_info(5:6));
            vehicle_pose_array.timeinfo.second(vehicle_pose_group) = str2num(time_info(8:9));
            vehicle_pose_array.timeinfo.millisecond(vehicle_pose_group) = str2num(time_info(11:end));
            vehicle_pose_array.timeinfo.timestamp(vehicle_pose_group) = 3600 * vehicle_pose_array.timeinfo.hour(vehicle_pose_group) + ...
                                                                        60 * vehicle_pose_array.timeinfo.minute(vehicle_pose_group) + ...
                                                                        vehicle_pose_array.timeinfo.second(vehicle_pose_group) + ...
                                                                        10^-6 * vehicle_pose_array.timeinfo.millisecond(vehicle_pose_group);
            vehicle_pose_array.verticle0_t.x(vehicle_pose_group) = verticle0_transit(1);
            vehicle_pose_array.verticle0_t.y(vehicle_pose_group) = verticle0_transit(2);
            vehicle_pose_array.verticle1_t.x(vehicle_pose_group) = verticle1_transit(1);
            vehicle_pose_array.verticle1_t.y(vehicle_pose_group) = verticle1_transit(2);
            vehicle_pose_array.verticle2_t.x(vehicle_pose_group) = verticle2_transit(1);
            vehicle_pose_array.verticle2_t.y(vehicle_pose_group) = verticle2_transit(2);
            vehicle_pose_array.verticle3_t.x(vehicle_pose_group) = verticle3_transit(1);
            vehicle_pose_array.verticle3_t.y(vehicle_pose_group) = verticle3_transit(2);
        end
    end
end

%获取车辆位置信息
function[vehicle_position_array] = vehicle_position_info_get(fid_log)
    vehicle_position_group = 0;
    while ~feof(fid_log)
        log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
        feature_content = ', point3: (';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 10);   %在完整log中找到指定行
        if status == 1
            vehicle_position_group = vehicle_position_group +1;
            feature_content = ', point3: (';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ',0';
            [status, z_info, z_index] = find_info(log_content, feature_content, 0, 0);
            xyposition = log_content(x_index + 11 : z_index - 1);    % 摘取x y坐标，以字符串摘出，此时两数之间以"，"为间隔
            [vehicle_position.x, vehicle_position.y] = strtok(xyposition,',');  % [token, remainder] = strtok(string, delimiters)
            vehicle_position.x = str2num(vehicle_position.x);
            vehicle_position.y = str2num(vehicle_position.y);
    
            vehicle_position_array.vehicle_position_group(vehicle_position_group) = vehicle_position_group;
            vehicle_position_array.x(vehicle_position_group) = vehicle_position.x;
            vehicle_position_array.y(vehicle_position_group) = vehicle_position.y;
        end
    end
end

%获取freespace信息
function[freespace_point_array] = freespace_info_get(fid_log)
    freespace_point_num = 0;
    while ~feof(fid_log)
        log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
        feature_content = '  INFO]count: ';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
        if status == 1
            freespace_point_num = freespace_point_num +1;
            feature_content = 'count: ';
            [status, fr_point_info, fr_point_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = 'point2: (';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ', ';
            [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);
    
            freespace_point.count = str2num(log_content(fr_point_index + 7: x_index - 22));
            freespace_point.x = str2num(log_content(x_index + 9 : y_index - 1));
            freespace_point.y = str2num(log_content(y_index + 2 : end - 1));
            freespace_point_array.x(freespace_point_num) = freespace_point.x;
            freespace_point_array.y(freespace_point_num) = freespace_point.y;
            freespace_point_array.count(freespace_point_num) = freespace_point.count;
        end
    end
end

%获取障碍物信息信息
function[obstacle_point_array] = obs_info_get(fid_log)
    obstacle_point_num = 0;
    while ~feof(fid_log)
        log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
        feature_content = 'INFO]detect distance: ';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
        if status == 1
            obstacle_point_num = obstacle_point_num +1;
            feature_content = 'distance: ';
            [status, d_info, d_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = 'obstacle count: ';
            [status, obs_point_info, obs_point_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = 'obstacle in world: point2: (';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ', ';
            [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);
            
            obstacle_point.distance = str2num(log_content(d_index + 10: obs_point_index - 3));
            obstacle_point.count = str2num(log_content(obs_point_index + 16: x_index - 3));
            obstacle_point.x = str2num(log_content(x_index + 28 : y_index - 1));
            obstacle_point.y = str2num(log_content(y_index + 2 : end - 1));
            obstacle_point_array(obstacle_point_num).x = obstacle_point.x;
            obstacle_point_array(obstacle_point_num).y = obstacle_point.y;
            obstacle_point_array(obstacle_point_num).distance = obstacle_point.distance;
            obstacle_point_array(obstacle_point_num).count = obstacle_point.count;
        end
    end
    obstacle_point_array(obstacle_point_num + 1).count = 1;  % 为下面摘取障碍物单帧信息的判断，在最后面补偿一个1
end

%obs关键信息，obs接收到时的车位坐标信息，用于在指定位置时更新周边的环境信息
function [obstacle_point_group] = obs_point_info_get(fid_log)
    obstacle_point_num = 0;
    while ~feof(fid_log)
        log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content 
        feature_content = 'INFO]point for obs:';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
        if status == 1
            obstacle_point_num = obstacle_point_num + 1;
            feature_content = '0726 ';
            [status, time_info, time_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ' PID:';
            [status, pid_info, pid_index] = find_info(log_content, feature_content, 0, 0);
            obstacle_point_group(obstacle_point_num).time_info = log_content(time_index + 5 : pid_index);
            
            %提取当前帧对应的系统时间
            [obstacle_point_group(obstacle_point_num).single_obs.hour, last] = strtok(obstacle_point_group(obstacle_point_num).time_info,':');  % [token, remainder] = strtok(string, delimiters)
            [obstacle_point_group(obstacle_point_num).single_obs.min, last] = strtok(last,':');  % [token, remainder] = strtok(string, delimiters)
            [obstacle_point_group(obstacle_point_num).single_obs.s, obstacle_point_group(obstacle_point_num).single_obs.ms] = strtok(last,'.');
            obstacle_point_group(obstacle_point_num).single_obs.hour = str2num(obstacle_point_group(obstacle_point_num).single_obs.hour(1:end));
            obstacle_point_group(obstacle_point_num).single_obs.min = str2num(obstacle_point_group(obstacle_point_num).single_obs.min(1:end));
            obstacle_point_group(obstacle_point_num).single_obs.s = str2num(obstacle_point_group(obstacle_point_num).single_obs.s(2:end));
            obstacle_point_group(obstacle_point_num).single_obs.ms = str2num(obstacle_point_group(obstacle_point_num).single_obs.ms(2:end));
            obstacle_point_group(obstacle_point_num).single_obs.timestamp = 3600 * obstacle_point_group(obstacle_point_num).single_obs.hour + ...
                                                                        60 * obstacle_point_group(obstacle_point_num).single_obs.min + ...
                                                                        obstacle_point_group(obstacle_point_num).single_obs.s + ...
                                                                        10^-6 * obstacle_point_group(obstacle_point_num).single_obs.ms;

            feature_content = 'obs';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ',  ';
            [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);
            obstacle_point_group(obstacle_point_num).single_obs.v_x = str2num(log_content(x_index + 5 : y_index - 1));
            obstacle_point_group(obstacle_point_num).single_obs.v_y = str2num(log_content(y_index + 3 : end));
        end
    end
end

%freespace关键信息，是freespace接收到时的车位坐标信息，用于在指定位置时更新周边的环境信息
function [freespace_point_group] = freespace_point_info_get(fid_log)
    freespace_point_num = 0;
    while ~feof(fid_log)
        log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content 
        feature_content = 'INFO]point for freespace:';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
        if status == 1
            freespace_point_num = freespace_point_num + 1;
            feature_content = '0726 ';
            [status, time_info, time_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ' PID:';
            [status, pid_info, pid_index] = find_info(log_content, feature_content, 0, 0);
            freespace_point_group(freespace_point_num).time_info = log_content(time_index + 5 : pid_index);
            
            %提取当前帧对应的系统时间
            [freespace_point_group(freespace_point_num).single_frame.hour, last] = strtok(freespace_point_group(freespace_point_num).time_info,':');  % [token, remainder] = strtok(string, delimiters)
            [freespace_point_group(freespace_point_num).single_frame.min, last] = strtok(last,':');  % [token, remainder] = strtok(string, delimiters)
            [freespace_point_group(freespace_point_num).single_frame.s, freespace_point_group(freespace_point_num).single_frame.ms] = strtok(last,'.');
            freespace_point_group(freespace_point_num).single_frame.hour = str2num(freespace_point_group(freespace_point_num).single_frame.hour(1:end));
            freespace_point_group(freespace_point_num).single_frame.min = str2num(freespace_point_group(freespace_point_num).single_frame.min(1:end));
            freespace_point_group(freespace_point_num).single_frame.s = str2num(freespace_point_group(freespace_point_num).single_frame.s(2:end));
            freespace_point_group(freespace_point_num).single_frame.ms = str2num(freespace_point_group(freespace_point_num).single_frame.ms(2:end));
            freespace_point_group(freespace_point_num).single_frame.timestamp = 3600 * freespace_point_group(freespace_point_num).single_frame.hour + ...
                                                                        60 * freespace_point_group(freespace_point_num).single_frame.min + ...
                                                                        freespace_point_group(freespace_point_num).single_frame.s + ...
                                                                        10^-6 * freespace_point_group(freespace_point_num).single_frame.ms;
            %提取对应的信息
            feature_content = 'freespace:';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ',  ';
            [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);
            freespace_point_group(freespace_point_num).single_frame.v_x = str2num(log_content(x_index + 11 : y_index - 1));
            freespace_point_group(freespace_point_num).single_frame.v_y = str2num(log_content(y_index + 3 : end ));
        end
    end
end

%摘取停车点关键字
function [stopper_array] = stopper_info_get(fid_log)
    stopper_point_num = 0;
    while ~feof(fid_log)
        log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
        feature_content = 'stopper_vertices 0 before transfer : point3: ';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
        if status == 1
            stopper_point_num = stopper_point_num +1;
            feature_content = '0726 ';
            [status, time_info, time_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ' PID:';
            [status, pid_info, pid_index] = find_info(log_content, feature_content, 0, 0);
            stopper_array(stopper_point_num).time_info = log_content(time_index + 5 : pid_index);
            
            %提取当前帧对应的系统时间
            [stopper_array(stopper_point_num).hour, last] = strtok(stopper_array(stopper_point_num).time_info,':');  % [token, remainder] = strtok(string, delimiters)
            [stopper_array(stopper_point_num).min, last] = strtok(last,':');  % [token, remainder] = strtok(string, delimiters)
            [stopper_array(stopper_point_num).s, stopper_array(stopper_point_num).ms] = strtok(last,'.');
            stopper_array(stopper_point_num).hour = str2num(stopper_array(stopper_point_num).hour(1:end));
            stopper_array(stopper_point_num).min = str2num(stopper_array(stopper_point_num).min(1:end));
            stopper_array(stopper_point_num).s = str2num(stopper_array(stopper_point_num).s(2:end));
            stopper_array(stopper_point_num).ms = str2num(stopper_array(stopper_point_num).ms(2:end));
            stopper_array(stopper_point_num).timestamp = 3600 * stopper_array(stopper_point_num).hour + ...
                                                        60 * stopper_array(stopper_point_num).min + ...
                                                        stopper_array(stopper_point_num).s + ...
                                                        10^-6 * stopper_array(stopper_point_num).ms;
            feature_content = ' (';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ', ';
            [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ',0';
            [status, z_info, z_index] = find_info(log_content, feature_content, 0, 0);
    
            stopper.x = str2num(log_content(x_index + 2 : y_index - 1));
            stopper.y = str2num(log_content(y_index + 2 : z_index - 1));
            stopper_array(stopper_point_num).x0 = stopper.x;
            stopper_array(stopper_point_num).y0 = stopper.y;
        end
        feature_content = 'stopper_vertices 1 before transfer : point3: ';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
        if status == 1
            feature_content = ' (';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ', ';
            [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ',0';
            [status, z_info, z_index] = find_info(log_content, feature_content, 0, 0);
    
            stopper.x = str2num(log_content(x_index + 2 : y_index - 1));
            stopper.y = str2num(log_content(y_index + 2 : z_index - 1));
            stopper_array(stopper_point_num).x1 = stopper.x;
            stopper_array(stopper_point_num).y1 = stopper.y;
        end
    end
end

%摘取车位信息关键字
function [slot_info] = slot_info_get(fid_log)
    slot_info_group = 0;
    while ~feof(fid_log)
        log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
        feature_content = '0before transfer : point3';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
        if status == 1
            slot_info_group = slot_info_group +1;
            feature_content = '0726 ';
            [status, time_info, time_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ' PID:';
            [status, pid_info, pid_index] = find_info(log_content, feature_content, 0, 0);
            slot_info(slot_info_group).time_info = log_content(time_index + 5 : pid_index);
            
            %提取当前帧对应的系统时间
            [slot_info(slot_info_group).hour, last] = strtok(slot_info(slot_info_group).time_info,':');  % [token, remainder] = strtok(string, delimiters)
            [slot_info(slot_info_group).min, last] = strtok(last,':');  % [token, remainder] = strtok(string, delimiters)
            [slot_info(slot_info_group).s, slot_info(slot_info_group).ms] = strtok(last,'.');
            slot_info(slot_info_group).hour = str2num(slot_info(slot_info_group).hour(1:end));
            slot_info(slot_info_group).min = str2num(slot_info(slot_info_group).min(1:end));
            slot_info(slot_info_group).s = str2num(slot_info(slot_info_group).s(2:end));
            slot_info(slot_info_group).ms = str2num(slot_info(slot_info_group).ms(2:end));
            slot_info(slot_info_group).timestamp = 3600 * slot_info(slot_info_group).hour + ...
                                                    60 * slot_info(slot_info_group).min + ...
                                                    slot_info(slot_info_group).s + ...
                                                    10^-6 * slot_info(slot_info_group).ms;
            feature_content = ': (';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ', ';
            [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);
    
            slot.worldvertices0.x = str2num(log_content(x_index + 3 : y_index - 1));
            slot.worldvertices0.y = str2num(log_content(y_index + 2 : end - 3));
    
            slot_info(slot_info_group).slot_info_group = slot_info_group;
            slot_info(slot_info_group).slotworld0.x = slot.worldvertices0.x;
            slot_info(slot_info_group).slotworld0.y = slot.worldvertices0.y;
        end
    
        feature_content = '1before transfer : point3';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
        if status == 1
            feature_content = ': (';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ', ';
            [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);
    
            slot.worldvertices1.x = str2num(log_content(x_index + 3 : y_index - 1));
            slot.worldvertices1.y = str2num(log_content(y_index + 2 : end - 3));
    
            slot_info(slot_info_group).slotworld1.x = slot.worldvertices1.x;
            slot_info(slot_info_group).slotworld1.y = slot.worldvertices1.y;
        end
    
        feature_content = '2before transfer : point3';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
        if status == 1
            feature_content = ': (';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ', ';
            [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);
    
            slot.worldvertices2.x = str2num(log_content(x_index + 3 : y_index - 1));
            slot.worldvertices2.y = str2num(log_content(y_index + 2 : end - 3));
    
            slot_info(slot_info_group).slotworld2.x = slot.worldvertices2.x;
            slot_info(slot_info_group).slotworld2.y = slot.worldvertices2.y;
        end
    
        feature_content = '3before transfer : point3';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
        if status == 1
            feature_content = ': (';
            [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
            feature_content = ', ';
            [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);
    
            slot.worldvertices3.x = str2num(log_content(x_index + 3 : y_index - 1));
            slot.worldvertices3.y = str2num(log_content(y_index + 2 : end - 3));
    
            slot_info(slot_info_group).slotworld3.x = slot.worldvertices3.x;
            slot_info(slot_info_group).slotworld3.y = slot.worldvertices3.y;
        end
    end
end

%摘取规划路径关键字
function [path_info_array] = path_info_get(fid_log)
    path_info_group = 0;
    while ~feof(fid_log)
        log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
        feature_content = 'INFO]i :';
        [status, section_info, section_index] = find_info(log_content, feature_content, 0, 50);   %在完整log中找到指定行
        if status == 1
            feature_content = 'i :';
            [status, index_info, index_index] = find_info(log_content, feature_content, 3, 4);
            feature_content = 'x:';
            [status, x_info, x_index] = find_info(log_content, feature_content, 2, 10);
            feature_content = 'y:';
            [status, y_info, y_index] = find_info(log_content, feature_content, 2, 10);
            feature_content = 'theta:';
            [status, theta_info, theta_index] = find_info(log_content, feature_content, 7,15);
            feature_content = 'kappa:';
            [status, kappa_info, kappa_index] = find_info(log_content, feature_content, 7,10);
            feature_content = 'speed:';
            [status, speed_info, speed_index] = find_info(log_content, feature_content, 7,7);
            feature_content = 's: ';
            [status, speed_info, s_index] = find_info(log_content, feature_content, 3,3);
    
            index_info = strtok(index_info);  % [token, remainder] = strtok(string, delimiters)
            index = str2num(log_content(index_index+3 : x_index - 3));      % 摘取索引值
            x = str2num(log_content(x_index+2 : y_index - 3));
            y = str2num(log_content(y_index+2 : theta_index - 3));
            theta = str2num(log_content(theta_index+7 : kappa_index - 3));
            kappa = str2num(log_content(kappa_index+7 : speed_index - 3));
            speed = str2num(log_content(speed_index+7 : s_index - 3));
            s     = str2num(log_content(s_index + 3 : end));
    
            path_info.index(index+1) = index;
            path_info.x(index+1) = x;
            path_info.y(index+1) = y;
            path_info.theta(index+1) = theta;
            path_info.kappa(index+1) = kappa;
            path_info.speed(index+1) = speed;
            path_info.s(index+1) = s;
            if index == 0    % index是0 说明是path上的第一个点，那么提取这个点的时间戳
                feature_content = '0726 ';
                [status, time_info, time_index] = find_info(log_content, feature_content, 0, 0);
                feature_content = ' PID:';
                [status, pid_info, pid_index] = find_info(log_content, feature_content, 0, 0);
                path_info.time_info = log_content(time_index + 5 : pid_index);

                [path_info.hour, last] = strtok(path_info.time_info,':');  % [token, remainder] = strtok(string, delimiters)
                [path_info.min, last] = strtok(last,':');  % [token, remainder] = strtok(string, delimiters)
                [path_info.s, path_info.ms] = strtok(last,'.');
                path_info.hour = str2num(path_info.hour(1:end));
                path_info.min = str2num(path_info.min(1:end));
                path_info.s = str2num(path_info.s(2:end));
                path_info.ms = str2num(path_info.ms(2:end));
                path_info.timestamp = 3600 * path_info.hour + ...
                                        60 * path_info.min + ...
                                        path_info.s + ...
                                        10^-6 * path_info.ms;
                
                path_info.path_info_group = path_info_group;
                path_info_group = path_info_group + 1;
                path_info_array(path_info_group) = path_info;
            end
        end
    end
end


function [status, section_info, section_index] = find_info(input_content, feature_content, return_length_start, return_length_end)
    feature_content_index = findstr(input_content, feature_content);                      %在log_content中查找关键字，并返回索引给path_info_start_position
    section_index = feature_content_index;
    if isempty(feature_content_index)
        status = 0;
        section_info = 0;
    else
        status = 1;
        section_info = input_content(feature_content_index + return_length_start: feature_content_index + return_length_end);  %摘取索引开始 到目标位置之间的内容
%         disp(section_info);
    end
end

% figure(1);
% plot(time, err_dist, "r-", "LineWidth",3);
% hold on; grid on;
% plot(time, control_angle / 1000, "m-", "LineWidth",3);
% hold on; grid on;
%axis([0 26 -1 1]);