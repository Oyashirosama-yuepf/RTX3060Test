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
if(obstacle_point_num ~= 0)
    for i = 1 : 1 : max(size(obstacle_point_array.x))
        red_degree = obstacle_point_array.distance(i) / max(obstacle_point_array.distance);
        plot(obstacle_point_array.x(i),obstacle_point_array.y(i), ".",'linewidth',3,'color', [1 - red_degree,0,red_degree]); hold on;
    end
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

choose_index = max(size(slot_info.slotworld0));
plot(slot_info.slotworld0.x, slot_info.slotworld0.y, 'bo', 'linewidth',3); hold on;
plot(slot_info.slotworld1.x, slot_info.slotworld1.y, 'bo', 'linewidth',3); hold on;
plot(slot_info.slotworld2.x, slot_info.slotworld2.y, 'bo', 'linewidth',3); hold on;
plot(slot_info.slotworld3.x, slot_info.slotworld3.y, 'bo', 'linewidth',3); hold on;
line([slot_info.slotworld0.x(choose_index),slot_info.slotworld1.x(choose_index)],[slot_info.slotworld0.y(choose_index), slot_info.slotworld1.y(choose_index)]);
line([slot_info.slotworld1.x(choose_index),slot_info.slotworld2.x(choose_index)],[slot_info.slotworld1.y(choose_index), slot_info.slotworld2.y(choose_index)]);
line([slot_info.slotworld2.x(choose_index),slot_info.slotworld3.x(choose_index)],[slot_info.slotworld2.y(choose_index), slot_info.slotworld3.y(choose_index)]);
line([slot_info.slotworld3.x(choose_index),slot_info.slotworld0.x(choose_index)],[slot_info.slotworld3.y(choose_index), slot_info.slotworld0.y(choose_index)]);

plot(stopper_array.x0, stopper_array.y0, 'bs', 'linewidth',3); hold on;
plot(stopper_array.x1, stopper_array.y1, 'bs', 'linewidth',3); hold on;

p1 = plot(0,0,'m*', 'linewidth',3); hold on;
p2 = plot(0,0,'m*', 'linewidth',3); hold on;
p3 = plot(0,0,'m*', 'linewidth',3); hold on;
p4 = plot(0,0,'m*', 'linewidth',3); hold on;
p0 = plot(0,0,'ks', 'linewidth',4); hold on; grid on;

p_freespace = plot(0,0,'c-', 'linewidth',3); hold on;
p_obs = plot(0,0,'gs-', 'linewidth',1); hold on;
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
    
    for i = 1:1:max(size(freespace_point_group))
        if sqrt((v_center_x - freespace_point_group(i).single_frame.v_x) ^2 + (v_center_y - freespace_point_group(i).single_frame.v_y)) <= 0.01
            single_frame_freespace.x = freespace_point_group(i).single_frame.x;
            single_frame_freespace.y = freespace_point_group(i).single_frame.y;
            set( p_freespace, 'Xdata', single_frame_freespace.x, 'Ydata', single_frame_freespace.y);
            break;
        end
    end
    
    for i = 1:1:max(size(obstacle_point_group))
        if sqrt((v_center_x - obstacle_point_group(i).single_frame.v_x) ^2 + (v_center_y - obstacle_point_group(i).single_frame.v_y)) <= 0.01
            single_frame_obs.x = obstacle_point_group(i).single_frame.x;
            single_frame_obs.y = obstacle_point_group(i).single_frame.y;
            set( p_obs, 'Xdata', single_frame_obs.x, 'Ydata', single_frame_obs.y); 
            break;
        end
    end
    pause(0.001);
    axis equal;
    % update screen
end

