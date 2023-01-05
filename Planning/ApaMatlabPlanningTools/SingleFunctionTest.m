
log_file = 'holo_planning.log';
fid_log = fopen(log_file,'r');  %障碍物触发时的位置信息
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
        
        obstacle_point.distance = str2num(log_content(d_index + 10: obs_point_index - 2));
        obstacle_point.count = str2num(log_content(obs_point_index + 16: x_index - 3));
        obstacle_point.x = str2num(log_content(x_index + 28 : y_index - 1));
        obstacle_point.y = str2num(log_content(y_index + 2 : end - 1));
        obstacle_point_array.x(obstacle_point_num) = obstacle_point.x;
        obstacle_point_array.y(obstacle_point_num) = obstacle_point.y;
                    disp(obstacle_point.distance);
        obstacle_point_array.distance(obstacle_point_num) = obstacle_point.distance;
        disp(obstacle_point.distance);
        obstacle_point_array.count(obstacle_point_num) = obstacle_point.count;
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