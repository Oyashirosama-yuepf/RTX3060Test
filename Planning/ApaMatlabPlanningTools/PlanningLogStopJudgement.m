clear;
clc;

%%%%%%%%%%%%%%%%%%%%%% 泊入判断 %%%%%%%%%%%%%%%%%%%%%%%
log_file = 'holo_planning.log';
fid_log = fopen(log_file,'r');
R = [];

fid_log = fopen(log_file,'r');
parking_in_judge_count = 0;
status = 0;
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'current_parkinglot_->single_obj.lot_x + vehicle_cfg_.imu_to_back_edge :';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 10);   %在完整log中找到指定行
    if status == 1
        parking_in_judge_count = parking_in_judge_count +1;
        feature_content = ' : ';
        [status, info_, index_] = find_info(log_content, feature_content, 0, 0);
        parking_in_judge.single_obj_lot_x_plus_imu(parking_in_judge_count) = str2num(log_content(index_ + 3 : end));
    end
end
fid_log = fclose(fid_log);
fid_log = fopen(log_file,'r');
parking_in_judge_count = 0;
status = 0;
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'x_limit_ :';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 10);   %在完整log中找到指定行
    if status == 1
        parking_in_judge_count = parking_in_judge_count +1;
        feature_content = ' : ';
        [status, info_, index_] = find_info(log_content, feature_content, 0, 0);
        parking_in_judge.index(parking_in_judge_count) = parking_in_judge_count;
        parking_in_judge.x_limit_(parking_in_judge_count) = str2num(log_content(index_ + 3 : end));
        parking_in_judge.y_limit_(parking_in_judge_count) = 0.15;
        parking_in_judge.angle_limit_(parking_in_judge_count) = 0.07;
    end
end
fid_log = fclose(fid_log);
fid_log = fopen(log_file,'r');
parking_in_judge_count = 0;
status = 0;
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'INFO] y error:';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 10);   %在完整log中找到指定行
    if status == 1
        parking_in_judge_count = parking_in_judge_count +1;
        feature_content = ': ';
        [status, info_, index_] = find_info(log_content, feature_content, 0, 0);
        parking_in_judge.dist_to_middle(parking_in_judge_count) = str2num(log_content(index_ + 2 : end));
    end
end

fid_log = fclose(fid_log);
fid_log = fopen(log_file,'r');
parking_in_judge_count = 0;
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'current_parkinglot_->single_obj.lot_theta';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 10);   %在完整log中找到指定行
    if status == 1
        parking_in_judge_count = parking_in_judge_count +1;
        feature_content = ' : ';
        [status, info_, index_] = find_info(log_content, feature_content, 0, 0);
        parking_in_judge.single_obj_lot_theta(parking_in_judge_count) = str2num(log_content(index_ + 3 : end));
    end
end

figure(2);
plot(parking_in_judge.index + 1, parking_in_judge.dist_to_middle, 'r-','linewidth',3); hold on; grid on;
plot(parking_in_judge.index, parking_in_judge.single_obj_lot_theta, 'b-','linewidth',3); hold on; grid on;
plot(parking_in_judge.index, parking_in_judge.single_obj_lot_x_plus_imu, 'm-','linewidth',3); hold on; grid on;

plot(parking_in_judge.index, parking_in_judge.x_limit_ - 0.1, 'k--', 'linewidth',2); hold on; grid on;
plot(parking_in_judge.index, parking_in_judge.x_limit_ + 0.5, 'k--', 'linewidth',2); hold on; grid on;
plot(parking_in_judge.index, parking_in_judge.y_limit_, 'c--', 'linewidth',2); hold on; grid on;
plot(parking_in_judge.index, -parking_in_judge.y_limit_, 'c--', 'linewidth',2); hold on; grid on;
plot(parking_in_judge.index, parking_in_judge.angle_limit_, 'y--', 'linewidth',2); hold on; grid on;
plot(parking_in_judge.index, -parking_in_judge.angle_limit_, 'y--', 'linewidth',2); hold on; grid on;

legend({'dist_to_middle','single_obj_lot_theta-pi/2', 'lot_x+imu','x_limit - 0.1', 'xlimit + 0.5', 'y_limit', 'minus_y_limit' ...
    'angle_limit' 'minus_angle_limit'},'Location','southwest')  % 添加图例
%axis square;

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
