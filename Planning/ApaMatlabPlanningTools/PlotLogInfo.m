figure(1);
% path的所有帧绘制
% if flag_plot_path == 1
%     choose_index = max(size(path_info_array));
%     for i =1 : 1 : choose_index
%         plot(path_info_array(i).x, path_info_array(i).y, 'r-', 'LineWidth',1); hold on; grid on;
%     end
%     for i =1 : 1 : choose_index
%         plot(path_info_array(i).x_zv, path_info_array(i).y_zv, 'b-', 'LineWidth',1); hold on; grid on;
%     end
% end

% 障碍物的所有帧绘制
% if  flag_plot_obstacle == 1
%     for i = 1 : 1 : max(size(obstacle_point_array)) - 1
%         red_degree = min(obstacle_point_array(i).distance / 10, 1);
%         plot(obstacle_point_array(i).x,obstacle_point_array(i).y, ".",'linewidth',3,'color', [1 - red_degree,0,red_degree]); hold on;  %plot(x,y,'color',[R G B]);
%     end
% end

% 车辆全轨迹信息
if flag_plot_odo_and_vehicle == 1
    plot(vehicle_position_array.x, vehicle_position_array.y, 'k-', 'linewidth',1);hold on; grid on;
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
    p_slot0 = plot(slot_info(1).slotworld0.x, slot_info(1).slotworld0.y, 'ko-', 'linewidth',3); hold on;
    p_slot1 = plot(slot_info(1).slotworld1.x, slot_info(1).slotworld1.y, 'ko-', 'linewidth',3); hold on;
    p_slot2 = plot(slot_info(1).slotworld2.x, slot_info(1).slotworld2.y, 'ko-', 'linewidth',3); hold on;
    p_slot3 = plot(slot_info(1).slotworld3.x, slot_info(1).slotworld3.y, 'ko-', 'linewidth',3); hold on;
    line1 = line([slot_info(j).slotworld0.x,slot_info(j).slotworld1.x],[slot_info(j).slotworld0.y, slot_info(j).slotworld1.y], 'linestyle','-','color','k');
    line2 = line([slot_info(j).slotworld1.x,slot_info(j).slotworld2.x],[slot_info(j).slotworld1.y, slot_info(j).slotworld2.y], 'linestyle','-','color','k');
    line3 = line([slot_info(j).slotworld2.x,slot_info(j).slotworld3.x],[slot_info(j).slotworld2.y, slot_info(j).slotworld3.y], 'linestyle','-','color','k');
    line4 = line([slot_info(j).slotworld3.x,slot_info(j).slotworld0.x],[slot_info(j).slotworld3.y, slot_info(j).slotworld0.y], 'linestyle','-','color','k');
end

%车位内停车点信息
if flag_plot_slot_stopper == 1
    p_stopper0 = plot(stopper_array(1).x0, stopper_array(1).y0, 'ks-', 'linewidth',3); hold on;
    p_stopper1 = plot(stopper_array(1).x1, stopper_array(1).y1, 'ks-', 'linewidth',3); hold on;
    line_stopper = line([stopper_array(1).x0,stopper_array(1).x1],[stopper_array(1).y0, stopper_array(1).y1],'linestyle','--','color','k');
end
% 车辆位置信息
if flag_plot_odo_and_vehicle == 1
    p1 = plot(0,0,'m*', 'linewidth',3); hold on;
    p2 = plot(0,0,'m*', 'linewidth',3); hold on;
    p3 = plot(0,0,'m*', 'linewidth',3); hold on;
    p4 = plot(0,0,'m*', 'linewidth',3); hold on;
    p0 = plot(0,0,'ks', 'linewidth',4); hold on; grid on;
end
% freespace信息
if flag_plot_freespace == 1
    p_freespace = plot(vehicle_position_array.x(1),vehicle_position_array.y(1),'k--', 'linewidth',1); hold on;
end
% 障碍物信息
if flag_plot_obstacle == 1
    p_obs = plot(vehicle_position_array.x(1),vehicle_position_array.y(1), 's', 'linewidth',1 ,'color', [1 - 0.5,0.3,0.5]); hold on;
end
%path信息
if flag_plot_path == 1
    plot_path = plot(path_info_array(1).x, path_info_array(1).y, 'r-', 'LineWidth',3); hold on; grid on;
    plot_path_zero = plot(path_info_array(1).x, path_info_array(1).y, 'b-', 'LineWidth',3); hold on; grid on;
end
for k = 1:length(vehicle_position_array.x)
    % first line
    if flag_plot_odo_and_vehicle == 1
        set( p1, 'Xdata', vehicle_position_array.x0(k), 'Ydata',  vehicle_position_array.y0(k) );
        set( p2, 'Xdata', vehicle_position_array.x1(k), 'Ydata',  vehicle_position_array.y1(k) );
        set( p3, 'Xdata', vehicle_position_array.x2(k), 'Ydata',  vehicle_position_array.y2(k) );
        set( p4, 'Xdata', vehicle_position_array.x3(k), 'Ydata',  vehicle_position_array.y3(k) );
        set( p0, 'Xdata', vehicle_position_array.x(k), 'Ydata', vehicle_position_array.y(k) );        
%         plot(vehicle_position_array.x0(k), vehicle_position_array.y0(k), 'm--.', 'linewidth',1);hold on; grid on;
%         plot(vehicle_position_array.x1(k), vehicle_position_array.y1(k), 'm--.', 'linewidth',1);hold on; grid on;
%         plot(vehicle_position_array.x2(k), vehicle_position_array.y2(k), 'm--.', 'linewidth',1);hold on; grid on;
%         plot(vehicle_position_array.x3(k), vehicle_position_array.y3(k), 'm--.', 'linewidth',1);hold on; grid on;
%         plot(vehicle_position_array.x(k), vehicle_position_array.y(k), 'k--.', 'linewidth',1);hold on; grid on;
%         if k == length(vehicle_position_array.x)
%             find_position = length(vehicle_position_array.x);
%             line([vehicle_position_array.x0(find_position),vehicle_position_array.x1(find_position)],[vehicle_position_array.y0(find_position), vehicle_position_array.y1(find_position)]);
%             line([vehicle_position_array.x1(find_position),vehicle_position_array.x2(find_position)],[vehicle_position_array.y1(find_position), vehicle_position_array.y2(find_position)]);
%             line([vehicle_position_array.x2(find_position),vehicle_position_array.x3(find_position)],[vehicle_position_array.y2(find_position), vehicle_position_array.y3(find_position)]);
%             line([vehicle_position_array.x3(find_position),vehicle_position_array.x0(find_position)],[vehicle_position_array.y3(find_position), vehicle_position_array.y0(find_position)]);
%         end
    end
    if flag_plot_freespace == 1
        for j = 1:length(freespace_point_group)   %判断当前点时刻的freespace信息
            if abs(freespace_point_group(j).single_frame.timestamp - vehicle_pose_array.timeinfo.timestamp(k)) <= 0.02 
                single_frame_freespace.x = freespace_point_group(j).single_frame.x;
                single_frame_freespace.y = freespace_point_group(j).single_frame.y;
                set(p_freespace, 'Xdata', single_frame_freespace.x, 'Ydata', single_frame_freespace.y);
                break;
            end
        end
    end
    if flag_plot_obstacle == 1
        for j = 1:obstacle_point_group_frame_num  %判断当前点时刻的障碍物信息
            if abs(obstacle_point_group(j).single_frame.timestamp - vehicle_pose_array.timeinfo.timestamp(k)) <= 0.02 
                single_frame_obs.x = obstacle_point_group(j).single_frame.x;
                single_frame_obs.y = obstacle_point_group(j).single_frame.y;
                set(p_obs, 'Xdata', single_frame_obs.x, 'Ydata', single_frame_obs.y);     
                break;
            end
        end
    end
    % 车库位信息
    if flag_plot_slot == 1
        for j = 1 : length(slot_info)
            if abs(slot_info(j).timestamp - vehicle_pose_array.timeinfo.timestamp(k)) <= 0.02
                delete(line1);delete(line2);delete(line3);delete(line4);
                set(p_slot0, 'Xdata', slot_info(j).slotworld0.x, 'Ydata', slot_info(j).slotworld0.y);  
                set(p_slot1, 'Xdata', slot_info(j).slotworld1.x, 'Ydata', slot_info(j).slotworld1.y);  
                set(p_slot2, 'Xdata', slot_info(j).slotworld2.x, 'Ydata', slot_info(j).slotworld2.y);  
                set(p_slot3, 'Xdata', slot_info(j).slotworld3.x, 'Ydata', slot_info(j).slotworld3.y);  
                line1 = line([slot_info(j).slotworld0.x,slot_info(j).slotworld1.x],[slot_info(j).slotworld0.y, slot_info(j).slotworld1.y],'linestyle','-','color','k');
                line2 = line([slot_info(j).slotworld1.x,slot_info(j).slotworld2.x],[slot_info(j).slotworld1.y, slot_info(j).slotworld2.y],'linestyle','-','color','k');
                line3 = line([slot_info(j).slotworld2.x,slot_info(j).slotworld3.x],[slot_info(j).slotworld2.y, slot_info(j).slotworld3.y],'linestyle','-','color','k');
                line4 = line([slot_info(j).slotworld3.x,slot_info(j).slotworld0.x],[slot_info(j).slotworld3.y, slot_info(j).slotworld0.y],'linestyle','-','color','k');
                break;
            end
        end
    end
    
    %车位内停车点信息
    if flag_plot_slot_stopper == 1
        for j = 1 :length(stopper_array)
            if abs(stopper_array(j).timestamp - vehicle_pose_array.timeinfo.timestamp(k)) <= 0.02
                delete(line_stopper);
                set(p_stopper0, 'Xdata', stopper_array(j).x0, 'Ydata', stopper_array(j).y0); hold on;
                set(p_stopper1, 'Xdata', stopper_array(j).x1, 'Ydata', stopper_array(j).y1); hold on;
                line_stopper = line([stopper_array(j).x0,stopper_array(j).x1],[stopper_array(j).y0, stopper_array(j).y1],'linestyle','--','color','k');
                break;
            end
        end
    end

    %path信息
    if flag_plot_slot_stopper == 1
        for j = 1 :length(path_info_array)
            if abs(path_info_array(j).timestamp - vehicle_pose_array.timeinfo.timestamp(k)) <= 0.02
                set(plot_path, 'Xdata', path_info_array(j).x, 'Ydata', path_info_array(j).y); 
                set(plot_path_zero, 'Xdata', path_info_array(j).x_zv, 'Ydata', path_info_array(j).y_zv);
                plot(path_info_array(j).x, path_info_array(j).y, 'r-', 'LineWidth',1); hold on; grid on;
                plot(path_info_array(j).x_zv, path_info_array(j).y_zv, 'b-', 'LineWidth',1); hold on; grid on;
                break;
            end
        end
    end
    
    pause(0.000001);
    axis equal;
    % update screen
end