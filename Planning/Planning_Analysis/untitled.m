clear;
clc;
% origindatatest1 = readcell("1.csv");
% origindata = importdata("planning.log");

log_file = 'holo_planning.log';
fid_log = fopen(log_file,'r');
R = [];

path_info_group = 0;
slot_info_group = 0;
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'INFO]i :';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 60);   %在完整log中找到指定行
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

        index_info = strtok(index_info);  % [token, remainder] = strtok(string, delimiters)
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
slot_info_group = 0;
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

fid_log = fclose(fid_log);
choose_index_1 = size(path_info_array);
choose_index_1 = choose_index_1(2);
choose_index_2 = size(slot_info.slotworld0);
choose_index_2 = choose_index_2(2);
choose_index = min(choose_index_1, choose_index_2);

figure(1);
for i =1 : 50 : choose_index
    plot(path_info_array(i).x, path_info_array(i).y, 'r-', 'LineWidth',3); hold on; grid on;
    txt = ['\leftarrow i = ' , num2str(i)];  %strcat ('\leftarrow i = ' , num2str(i))
    size_tag = round(max(size(path_info_array(i).x)) / 2);
    if size_tag > 0
        text(path_info_array(i).x(size_tag),path_info_array(i).y(size_tag),txt)   
    end
end
plot(vehicle_position_array.x, vehicle_position_array.y, 'k*--', 'linewidth',1);hold on; grid on;

% legend({'y = sin(x)','y = cos(x)'},'Location','southwest')  % 添加图例
% xlabel('-2\pi < x < 2\pi')  
% ylabel('Sine and Cosine Values')   % x y坐标标签
% ax = gca;
% ax.FontSize = 13;  %更改字体大小
% title('Line Plot of Sine and Cosine Between -2\pi and 2\pi')  %添加标题
% k = sin(pi/2);
% title(['sin(\pi/2) = ' num2str(k)])   %添加带有变量名称的标题
% txt = '\leftarrow sin(\pi) = 0';
% text(pi,sin(pi),txt)    

% 
% plot(slot_info.slot0(choose_index).x, slot_info.slot0(choose_index).y, 'ro', 'linewidth',3); hold on;
% plot(slot_info.slot1(choose_index).x, slot_info.slot1(choose_index).y, 'ro', 'linewidth',3); hold on;
% plot(slot_info.slot2(choose_index).x, slot_info.slot2(choose_index).y, 'ro', 'linewidth',3); hold on;
% plot(slot_info.slot3(choose_index).x, slot_info.slot3(choose_index).y, 'ro', 'linewidth',3); hold on;
% line([slot_info.slot0(choose_index).x,slot_info.slot1(choose_index).x],[slot_info.slot0(choose_index).y, slot_info.slot1(choose_index).y]);
% line([slot_info.slot1(choose_index).x,slot_info.slot2(choose_index).x],[slot_info.slot1(choose_index).y, slot_info.slot2(choose_index).y]);
% line([slot_info.slot2(choose_index).x,slot_info.slot3(choose_index).x],[slot_info.slot2(choose_index).y, slot_info.slot3(choose_index).y]);
% line([slot_info.slot3(choose_index).x,slot_info.slot0(choose_index).x],[slot_info.slot3(choose_index).y, slot_info.slot0(choose_index).y]);

plot(slot_info.slotworld0(choose_index).x, slot_info.slotworld0(choose_index).y, 'bo', 'linewidth',3); hold on;
plot(slot_info.slotworld1(choose_index).x, slot_info.slotworld1(choose_index).y, 'bo', 'linewidth',3); hold on;
plot(slot_info.slotworld2(choose_index).x, slot_info.slotworld2(choose_index).y, 'bo', 'linewidth',3); hold on;
plot(slot_info.slotworld3(choose_index).x, slot_info.slotworld3(choose_index).y, 'bo', 'linewidth',3); hold on;
line([slot_info.slotworld0(choose_index).x,slot_info.slotworld1(choose_index).x],[slot_info.slotworld0(choose_index).y, slot_info.slotworld1(choose_index).y]);
line([slot_info.slotworld1(choose_index).x,slot_info.slotworld2(choose_index).x],[slot_info.slotworld1(choose_index).y, slot_info.slotworld2(choose_index).y]);
line([slot_info.slotworld2(choose_index).x,slot_info.slotworld3(choose_index).x],[slot_info.slotworld2(choose_index).y, slot_info.slotworld3(choose_index).y]);
line([slot_info.slotworld3(choose_index).x,slot_info.slotworld0(choose_index).x],[slot_info.slotworld3(choose_index).y, slot_info.slotworld0(choose_index).y]);


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
