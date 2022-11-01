clc;
clear;
log_file = 'parkposition.log';
fid_log = fopen(log_file,'r');
park_position_count = 0;
while ~feof(fid_log)
    log_content = fgetl(fid_log);   % 根据句柄打开文件，内容写入log_content
    feature_content = 'frameid:';
    [status, section_info, section_index] = find_info(log_content, feature_content, 0, 0);   %在完整log中找到指定行
    if status == 1
        park_position_count = park_position_count +1;
        feature_content = ' : ';
        [status, info_, index_] = find_info(log_content, feature_content, 0, 0);
        parking_in_judge.single_obj_lot_theta(park_position_count) = str2num(log_content(index_ + 3 : end));
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
