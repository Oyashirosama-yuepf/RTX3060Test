clear;
clc;

% p = parpool('local',4);   % 多核计算
% delete(gcp('nocreate'));  % 关闭多核计算
% origindatatest1 = readcell("1.csv");
% origindata = importdata("planning.log");

tic;
log_file = 'holo_planning.log';
fid_log = fopen(log_file,'r');
R = [];

path_info_group = 0;
slot_info_group = 0;
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

        index = str2num(log_content(index_index+3 : x_index - 3));      % 摘取索引值
        x = str2num(log_content(x_index+2 : y_index - 3));
        y = str2num(log_content(y_index+2 : theta_index - 3));
        theta = str2num(log_content(theta_index+7 : kappa_index - 3));
        kappa = str2num(log_content(kappa_index+7 : speed_index - 3));
        speed = str2num(log_content(speed_index+7 : end));

        path_info.index(index+1) = index;
        path_info.x(index+1) = x;
        path_info.y(index+1) = y;
        path_info.theta(index+1) = theta;
        path_info.kappa(index+1) = kappa;
        path_info.speed(index+1) = speed;
        if index == 0
            path_info.path_info_group = path_info_group;
            path_info_group = path_info_group + 1;
            path_info_array(path_info_group+1) = path_info;
        end
    end
end

fid_log = fopen(log_file,'r');
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'slot.vertices 0';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
    if status == 1
        slot_info_group = slot_info_group +1;
        feature_content = 'x :';
        [status, x_info, x_index] = find_info(log_content, feature_content, 2, 2);
        feature_content = 'y:';
        [status, y_info, y_index] = find_info(log_content, feature_content, 2, 2);

        slot.vertices0.x = str2num(log_content(x_index+5 : y_index - 2));
        slot.vertices0.y = str2num(log_content(y_index+3 : end));

        slot_info.slot_info_group(slot_info_group) = slot_info_group;
        slot_info.slot0(slot_info_group) = slot.vertices0;
    end

    feature_content = 'slot.vertices 1';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
    if status == 1
        feature_content = 'x :';
        [status, x_info, x_index] = find_info(log_content, feature_content, 2, 2);
        feature_content = 'y:';
        [status, y_info, y_index] = find_info(log_content, feature_content, 2, 2);

        slot.vertices1.x = str2num(log_content(x_index+5 : y_index - 2));
        slot.vertices1.y = str2num(log_content(y_index+3 : end));

        slot_info.slot1(slot_info_group) = slot.vertices1;
    end

    feature_content = 'slot.vertices 2';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
    if status == 1
        feature_content = 'x :';
        [status, x_info, x_index] = find_info(log_content, feature_content, 2, 2);
        feature_content = 'y:';
        [status, y_info, y_index] = find_info(log_content, feature_content, 2, 2);

        slot.vertices2.x = str2num(log_content(x_index+5 : y_index - 2));
        slot.vertices2.y = str2num(log_content(y_index+3 : end));

        slot_info.slot2(slot_info_group) = slot.vertices2;
    end

    feature_content = 'slot.vertices 3';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
    if status == 1
        feature_content = 'x :';
        [status, x_info, x_index] = find_info(log_content, feature_content, 2, 2);
        feature_content = 'y:';
        [status, y_info, y_index] = find_info(log_content, feature_content, 2, 2);

        slot.vertices3.x = str2num(log_content(x_index+5 : y_index - 2));
        slot.vertices3.y = str2num(log_content(y_index+3 : end));

        slot_info.slot3(slot_info_group) = slot.vertices3;
    end
end

fid_log = fopen(log_file,'r');
slot_info_group = 1;
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = '0before transfer : point3';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
    if status == 1
        slot_info_group = slot_info_group +1;
        feature_content = ': (';
        [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
        feature_content = ', ';
        [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);

        slot.worldvertices0.x = str2num(log_content(x_index + 3 : y_index - 1));
        slot.worldvertices0.y = str2num(log_content(y_index + 2 : end - 3));

        slot_info.slot_info_group(slot_info_group) = slot_info_group;
        slot_info.slotworld0(slot_info_group) = slot.worldvertices0;
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

        slot_info.slotworld1(slot_info_group) = slot.worldvertices1;
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

        slot_info.slotworld2(slot_info_group) = slot.worldvertices2;
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

        slot_info.slotworld3(slot_info_group) = slot.worldvertices3;
    end
end

fid_log = fopen(log_file,'r');
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

fid_log = fopen(log_file,'r');
%车身尺寸 先随便写一个，取后轴中心为原点，然后向四个方向延展开。
vehicle_pose_group = 0;
vehicle_pose_array.verticle0 = [3.58;-0.9];
vehicle_pose_array.verticle1 = [3.58;0.9];
vehicle_pose_array.verticle2 = [-1;0.9];
vehicle_pose_array.verticle3 = [-1;-0.9];
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'odometryd: pose3: (';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 10);   %在完整log中找到指定行
    if status == 1
        vehicle_pose_group = vehicle_pose_group +1;
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
        verticle0_transit = vehicle_pose_rotate * vehicle_pose_array.verticle0;
        verticle1_transit = vehicle_pose_rotate * vehicle_pose_array.verticle1;
        verticle2_transit = vehicle_pose_rotate * vehicle_pose_array.verticle2;
        verticle3_transit = vehicle_pose_rotate * vehicle_pose_array.verticle3;

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
%车辆的四个角点
vehicle_position_array.x0 = vehicle_position_array.x+vehicle_pose_array.verticle0_t.x;
vehicle_position_array.y0 = vehicle_position_array.y+vehicle_pose_array.verticle0_t.y;
vehicle_position_array.x1 = vehicle_position_array.x+vehicle_pose_array.verticle1_t.x;
vehicle_position_array.y1 = vehicle_position_array.y+vehicle_pose_array.verticle1_t.y;
vehicle_position_array.x2 = vehicle_position_array.x+vehicle_pose_array.verticle2_t.x;
vehicle_position_array.y2 = vehicle_position_array.y+vehicle_pose_array.verticle2_t.y;
vehicle_position_array.x3 = vehicle_position_array.x+vehicle_pose_array.verticle3_t.x;
vehicle_position_array.y3 = vehicle_position_array.y+vehicle_pose_array.verticle3_t.y;

fid_log = fclose(fid_log);
choose_index_1 = size(path_info_array);
choose_index_1 = choose_index_1(2);
choose_index_2 = size(slot_info.slotworld0);
choose_index_2 = choose_index_2(2);
choose_index = min(choose_index_1, choose_index_2);

%摘取零速度段
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

fid_log = fopen(log_file,'r');
collision_point_num = 0;
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'collision point: point2: ';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
    if status == 1
        collision_point_num = collision_point_num +1;
        feature_content = ': (';
        [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
        feature_content = ', ';
        [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);

        collision_point.point1.x = str2num(log_content(x_index + 3 : y_index - 1));
        collision_point.point1.y = str2num(log_content(y_index + 2 : end - 1));
        collision_point_array.point1.x(collision_point_num) = collision_point.point1.x;
        collision_point_array.point1.y(collision_point_num) = collision_point.point1.y;
        collision_point_array.point1world.x(collision_point_num) = collision_point.point1.x + vehicle_position.x;
        collision_point_array.point1world.y(collision_point_num) = collision_point.point1.y + vehicle_position.y;
    end

    feature_content = 'last: point2: ';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
    if status == 1
        feature_content = ': (';
        [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
        feature_content = ', ';
        [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);

        collision_point.point2.x = str2num(log_content(x_index + 3 : y_index - 1));
        collision_point.point2.y = str2num(log_content(y_index + 2 : end - 1));
        collision_point_array.point2.x(collision_point_num) = collision_point.point2.x;
        collision_point_array.point2.y(collision_point_num) = collision_point.point2.y;
        collision_point_array.point2world.x(collision_point_num) = collision_point.point2.x + vehicle_position.x;
        collision_point_array.point2world.y(collision_point_num) = collision_point.point2.y + vehicle_position.y;
    end
end


fid_log = fopen(log_file,'r');
obstacle_point_num = 0;
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'obstacle in world: point2: ';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
    if status == 1
        obstacle_point_num = obstacle_point_num +1;
        feature_content = ' (';
        [status, x_info, x_index] = find_info(log_content, feature_content, 0, 0);
        feature_content = ', ';
        [status, y_info, y_index] = find_info(log_content, feature_content, 0, 0);

        obstacle_point.x = str2num(log_content(x_index + 2 : y_index - 1));
        obstacle_point.y = str2num(log_content(y_index + 2 : end - 3));
        obstacle_point_array.x(obstacle_point_num) = obstacle_point.x;
        obstacle_point_array.y(obstacle_point_num) = obstacle_point.y;
    end
end

fid_log = fopen(log_file,'r');
obstacle_point_num = 0;
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'detect distance: ';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 20);   %在完整log中找到指定行
    if status == 1
        obstacle_point_num = obstacle_point_num +1;
        feature_content = ': ';
        [status, d_info, d_index] = find_info(log_content, feature_content, 0, 0);
        obstacle_point.distance = str2num(log_content(d_index + 2 : end - 1));
        obstacle_point_array.distance(obstacle_point_num) = obstacle_point.distance;
    end
end

fid_log = fclose(fid_log);
figure(1);
for i =1 : 50 : choose_index
    plot(path_info_array(i).x, path_info_array(i).y, 'r-', 'LineWidth',3); hold on; grid on;
%     txt = ['\leftarrow i = ' , num2str(i)];  %strcat ('\leftarrow i = ' , num2str(i))
%     size_tag = round(max(size(path_info_array(i).x)) / 2);
%     if size_tag > 0
%         text(path_info_array(i).x(size_tag),path_info_array(i).y(size_tag),txt)
%     end
end
for i =1 : 50 : choose_index
    plot(path_info_array(i).x_zv, path_info_array(i).y_zv, 'b-', 'LineWidth',3); hold on; grid on;
end
figure(1)
%plot(x,y,'color',[R G B]);
for i = 1 : 1 : max(size(obstacle_point_array.x))
    red_degree = obstacle_point_array.distance(i) / max(obstacle_point_array.distance);
    plot(obstacle_point_array.x(i),obstacle_point_array.y(i), ".",'linewidth',3,'color', [1 - red_degree,0,red_degree]); hold on;
end
plot(vehicle_position_array.x, vehicle_position_array.y, 'k-', 'linewidth',3);hold on; grid on;
plot(vehicle_position_array.x0, vehicle_position_array.y0, 'm--', 'linewidth',1);hold on; grid on;
plot(vehicle_position_array.x1, vehicle_position_array.y1, 'm--', 'linewidth',1);hold on; grid on;
plot(vehicle_position_array.x2, vehicle_position_array.y2, 'm--', 'linewidth',1);hold on; grid on;
plot(vehicle_position_array.x3, vehicle_position_array.y3, 'm--', 'linewidth',1);hold on; grid on;
find_position = max(size(vehicle_position_array.x));
line([vehicle_position_array.x0(find_position),vehicle_position_array.x1(find_position)],[vehicle_position_array.y0(find_position), vehicle_position_array.y1(find_position)]);
line([vehicle_position_array.x1(find_position),vehicle_position_array.x2(find_position)],[vehicle_position_array.y1(find_position), vehicle_position_array.y2(find_position)]);
line([vehicle_position_array.x2(find_position),vehicle_position_array.x3(find_position)],[vehicle_position_array.y2(find_position), vehicle_position_array.y3(find_position)]);
line([vehicle_position_array.x3(find_position),vehicle_position_array.x0(find_position)],[vehicle_position_array.y3(find_position), vehicle_position_array.y0(find_position)]);

plot(slot_info.slotworld0(choose_index).x, slot_info.slotworld0(choose_index).y, 'bo', 'linewidth',3); hold on;
plot(slot_info.slotworld1(choose_index).x, slot_info.slotworld1(choose_index).y, 'bo', 'linewidth',3); hold on;
plot(slot_info.slotworld2(choose_index).x, slot_info.slotworld2(choose_index).y, 'bo', 'linewidth',3); hold on;
plot(slot_info.slotworld3(choose_index).x, slot_info.slotworld3(choose_index).y, 'bo', 'linewidth',3); hold on;
line([slot_info.slotworld0(choose_index).x,slot_info.slotworld1(choose_index).x],[slot_info.slotworld0(choose_index).y, slot_info.slotworld1(choose_index).y]);
line([slot_info.slotworld1(choose_index).x,slot_info.slotworld2(choose_index).x],[slot_info.slotworld1(choose_index).y, slot_info.slotworld2(choose_index).y]);
line([slot_info.slotworld2(choose_index).x,slot_info.slotworld3(choose_index).x],[slot_info.slotworld2(choose_index).y, slot_info.slotworld3(choose_index).y]);
line([slot_info.slotworld3(choose_index).x,slot_info.slotworld0(choose_index).x],[slot_info.slotworld3(choose_index).y, slot_info.slotworld0(choose_index).y]);

p1 = plot(0,0,'m*', 'linewidth',3); hold on;
p2 = plot(0,0,'m*', 'linewidth',3); hold on;
p3 = plot(0,0,'m*', 'linewidth',3); hold on;
p4 = plot(0,0,'m*', 'linewidth',3); hold on;
p0 = plot(0,0,'ks', 'linewidth',4); hold on; grid on;
for k = 1:length(vehicle_position_array.x)
    % first line
    v_center_x = vehicle_position_array.x(k);
    v_center_y = vehicle_position_array.y(k);
    v1x = vehicle_position_array.x0(k);
    v1y = vehicle_position_array.y0(k);
    v2x = vehicle_position_array.x1(k);
    v2y = vehicle_position_array.y1(k);
    v3x = vehicle_position_array.x2(k);
    v3y = vehicle_position_array.y2(k);
    v4x = vehicle_position_array.x3(k);
    v4y = vehicle_position_array.y3(k);
    set( p1, 'Xdata', v1x, 'Ydata', v1y );
    set( p2, 'Xdata', v2x, 'Ydata', v2y );
    set( p3, 'Xdata', v3x, 'Ydata', v3y );
    set( p4, 'Xdata', v4x, 'Ydata', v4y );
    set( p0, 'Xdata', v_center_x, 'Ydata', v_center_y );
    pause(0.001);
    axis equal;
    % update screen
end
%axis square;
toc;


% figure(1);
% plot(time, err_dist, "r-", "LineWidth",3);
% hold on; grid on;
% plot(time, control_angle / 1000, "m-", "LineWidth",3);
% hold on; grid on;
%axis([0 26 -1 1]);
