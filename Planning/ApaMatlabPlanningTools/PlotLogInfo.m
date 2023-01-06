figure(1);
if flag_plot_path == 1
    choose_index = max(size(path_info_array));
    for i =1 : 1 : choose_index
        plot(path_info_array(i).x, path_info_array(i).y, 'r-', 'LineWidth',3); hold on; grid on;
    end
    for i =1 : 1 : choose_index
        plot(path_info_array(i).x_zv, path_info_array(i).y_zv, 'b-', 'LineWidth',3); hold on; grid on;
    end
end

% 障碍物的所有帧绘制
% if  flag_plot_obstacle == 1
%     for i = 1 : 1 : max(size(obstacle_point_array)) - 1
%         red_degree = min(obstacle_point_array(i).distance / 10, 1);
%         plot(obstacle_point_array(i).x,obstacle_point_array(i).y, ".",'linewidth',3,'color', [1 - red_degree,0,red_degree]); hold on;  %plot(x,y,'color',[R G B]);
%     end
% end

% 车辆全轨迹信息
if flag_plot_odo_and_vehicle == 1
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
end

% 车库位信息
if flag_plot_slot == 1
    choose_index = max(size(slot_info.slotworld0));
    plot(slot_info.slotworld0.x, slot_info.slotworld0.y, 'bo', 'linewidth',3); hold on;
    plot(slot_info.slotworld1.x, slot_info.slotworld1.y, 'bo', 'linewidth',3); hold on;
    plot(slot_info.slotworld2.x, slot_info.slotworld2.y, 'bo', 'linewidth',3); hold on;
    plot(slot_info.slotworld3.x, slot_info.slotworld3.y, 'bo', 'linewidth',3); hold on;
    line([slot_info.slotworld0.x(choose_index),slot_info.slotworld1.x(choose_index)],[slot_info.slotworld0.y(choose_index), slot_info.slotworld1.y(choose_index)]);
    line([slot_info.slotworld1.x(choose_index),slot_info.slotworld2.x(choose_index)],[slot_info.slotworld1.y(choose_index), slot_info.slotworld2.y(choose_index)]);
    line([slot_info.slotworld2.x(choose_index),slot_info.slotworld3.x(choose_index)],[slot_info.slotworld2.y(choose_index), slot_info.slotworld3.y(choose_index)]);
    line([slot_info.slotworld3.x(choose_index),slot_info.slotworld0.x(choose_index)],[slot_info.slotworld3.y(choose_index), slot_info.slotworld0.y(choose_index)]);
end

%车位内停车点信息
if flag_plot_slot_stopper == 1
    plot(stopper_array.x0, stopper_array.y0, 'bs', 'linewidth',3); hold on;
    plot(stopper_array.x1, stopper_array.y1, 'bs', 'linewidth',3); hold on;
end

if flag_plot_odo_and_vehicle == 1
    p1 = plot(0,0,'m*', 'linewidth',3); hold on;
    p2 = plot(0,0,'m*', 'linewidth',3); hold on;
    p3 = plot(0,0,'m*', 'linewidth',3); hold on;
    p4 = plot(0,0,'m*', 'linewidth',3); hold on;
    p0 = plot(0,0,'ks', 'linewidth',4); hold on; grid on;
end
if flag_plot_freespace == 1
      p_freespace = plot(vehicle_position_array.x(1),vehicle_position_array.y(1),'k--', 'linewidth',1); hold on;
end
if flag_plot_obstacle == 1
    p_obs = plot(vehicle_position_array.x(1),vehicle_position_array.y(1), 's', 'linewidth',1 ,'color', [1 - 0.5,0.3,0.5]); hold on;
end
for k = 1:length(vehicle_position_array.x)
    % first line
    if flag_plot_odo_and_vehicle == 1
        set( p1, 'Xdata', vehicle_position_array.x0(k), 'Ydata',  vehicle_position_array.y0(k) );
        set( p2, 'Xdata', vehicle_position_array.x1(k), 'Ydata',  vehicle_position_array.y1(k) );
        set( p3, 'Xdata', vehicle_position_array.x2(k), 'Ydata',  vehicle_position_array.y2(k) );
        set( p4, 'Xdata', vehicle_position_array.x3(k), 'Ydata',  vehicle_position_array.y3(k) );
        set( p0, 'Xdata', vehicle_position_array.x(k), 'Ydata', vehicle_position_array.y(k) );
    end
    if flag_plot_freespace == 1
        for j = 1:length(freespace_point_group)   %判断当前点时刻的freespace信息
            if abs(freespace_point_group(j).single_frame.timestamp - vehicle_pose_array.timeinfo.timestamp(k)) <= 0.02 
                single_frame_freespace.x = freespace_point_group(j).single_frame.x;
                single_frame_freespace.y = freespace_point_group(j).single_frame.y;
                set( p_freespace, 'Xdata', single_frame_freespace.x, 'Ydata', single_frame_freespace.y);
            end
        end
    end
    if flag_plot_obstacle == 1
        for j = 1:obstacle_point_group_frame_num  %判断当前点时刻的障碍物信息
            if abs(obstacle_point_group(j).single_frame.timestamp - vehicle_pose_array.timeinfo.timestamp(k)) <= 0.02 
                single_frame_obs.x = obstacle_point_group(j).single_frame.x;
                single_frame_obs.y = obstacle_point_group(j).single_frame.y;
                set(p_obs, 'Xdata', single_frame_obs.x, 'Ydata', single_frame_obs.y);               
            end
        end
    end
    
    pause(0.001);
    axis equal;
    % update screen
end