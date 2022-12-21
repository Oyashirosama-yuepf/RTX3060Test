clc;
close all;

if 1
    clear;
    history_cache    = 0;
else
    history_cache    = 1;
end


GH01 = 0;


if GH01 ~= 1

    fs_hdl          = 1;
    
    ori_hdl         = 1;
    opt_hdl         = 1;
    
    navi_hdl        = 1;
    
    obj_hdl         = 1;
    
    path_odo_hdl    = 1;
        odo_hdl          = 1;
        brake_hdl        = 1;
        ref_path_hdl     = 1;
        ctrl_err_hdl     = 1;
    
%         path_predict_hdl = 0;
%         path_parking_hdl = 0;


    map_path        = 'C:\Users\baiying\Desktop\距离障碍物1米以上杀停11_20221122_172038\map_1\route_1';
    file_path       = 'C:\Users\baiying\Desktop\距离障碍物1米以上杀停11_20221122_172038';
    
    fs_log          = [map_path,'\global_freespace_readable.txt'];
    ori_log         = [map_path,'\path_original.txt'];
    opt_log         = [map_path,'\path_optimize.txt'];
    navi_log        = [file_path,'\holo_map\holo_parking_map.log'];
    obj_log         = [file_path,'\holo_planning_parking\holo_planning_app.log'];
    path_odo_log    = [file_path,'\holo_planning_parking\holo_planning_app.log'];

else

    fs_hdl          = 1;
    
    ori_hdl         = 1;
    opt_hdl         = 0;
    
    navi_hdl        = 0;
    
    obj_hdl         = 0;
    
    path_odo_hdl    = 1;
        odo_hdl          = 1;
        brake_hdl        = 0;
        ref_path_hdl     = 1;
        pub_path_hdl     = 0;
        ctrl_err_hdl     = 1;
    
        path_predict_hdl = 0;
        path_parking_hdl = 0;


    map_path        = 'C:\Users\baiying\Desktop\距离障碍物1米以上杀停11_20221122_172038\map_1\route_1';
    file_path       = 'C:\Users\baiying\Desktop\距离障碍物1米以上杀停11_20221122_172038';
    
    fs_log          = [map_path,'\global_freespace_readable.txt'];
    ori_log         = [map_path,'\path_original.txt'];
    opt_log         = [map_path,'\path_optimize.txt'];
    navi_log        = [file_path,'\holo_map\navigator_parking_cmw_1179697_0_2022-11-08-150617.txt'];
    obj_log         = [file_path,'\holo_planning_parking\planning_hpp_app_1179695_0_2022-11-08-150617.txt'];
    path_odo_log    = [file_path,'\holo_planning_parking\planning_hpp_app_1179695_0_2022-11-08-150617.txt'];

end



diff_lateral_average = 0;
diff_yaw_average = 0;
pub_pathpoint_x=[];
pub_pathpoint_y=[];
pub_pathpoint_yaw=[];
pathpoint_x=[];
pathpoint_y=[];


veh_width=2.011;
veh_half_width = veh_width/2;
veh_length=4.785;
veh_front_edge=3.646;
veh_back_edge=1.146;

veh_fl_body = [veh_front_edge veh_half_width];
veh_fr_body = [veh_front_edge -veh_half_width];
veh_rl_body = [-veh_back_edge veh_half_width];
veh_rr_body = [-veh_back_edge -veh_half_width];


main_fig = figure('NumberTitle', 'off', "Name", "main");
plot([0 0], [0 0],'oy');
daspect([1 1 1]);
title("1b");
xlabel('X  unit: m');
ylabel('Y  unit: m');
hold on;


if fs_hdl == 1
    if history_cache == 0
        freespace_file = readtable(fs_log);
        freespace_size = size(freespace_file,1);
        freespace_file = freespace_file(2:end, :);
        freespace_str  = string(freespace_file{:,:});
        
        fs_path_point_x = str2double(freespace_str(:,1));
        fs_path_point_y = str2double(freespace_str(:,2));
        fs_left_point_x = str2double(freespace_str(:,3));
        fs_left_point_y = str2double(freespace_str(:,4));
        fs_right_point_x = str2double(freespace_str(:,5));
        fs_right_point_y = str2double(freespace_str(:,6));
    end

    if 1
%         plot(fs_path_point_x(:,1), fs_path_point_y(:,1), '-b');
        plot(fs_left_point_x(:,1), fs_left_point_y(:,1), '-r');
        plot(fs_right_point_x(:,1), fs_right_point_y(:,1), '-r');
    else
        for i = 1 : size(fs_path_point_x(:,1))
%             plot(fs_path_point_x(i,1), fs_path_point_y(i,1), '*b');
            plot(fs_left_point_x(i,1), fs_left_point_y(i,1), '.r');
            plot(fs_right_point_x(i,1), fs_right_point_y(i,1), '.r');
            pause(0.05);
        end
    end
end


% original path
if ori_hdl == 1
    if history_cache == 0
        ori_file = readtable(ori_log);
        ori_size = size(ori_file,1);
        ori_str  = string(ori_file{:,1:13});
        
        ori_path_point_x    = str2double(ori_str(:,2)).';
        ori_path_point_y    = str2double(ori_str(:,3)).';
        ori_path_point_yaw  = str2double(ori_str(:,5)).';

        if(size(ori_path_point_x)~=0)
            ori_odo_left_x = 0 - sin(ori_path_point_yaw(1,:)) * veh_half_width + ori_path_point_x(1,:);
            ori_odo_left_y = 0 + cos(ori_path_point_yaw(1,:)) * veh_half_width + ori_path_point_y(1,:);
    
            ori_odo_right_x = 0 - sin(ori_path_point_yaw(1,:)) * -veh_half_width + ori_path_point_x(1,:);
            ori_odo_right_y = 0 + cos(ori_path_point_yaw(1,:)) * -veh_half_width + ori_path_point_y(1,:);
        end
    end

    plot(ori_path_point_x(1,:), ori_path_point_y(1,:), '--k');
    plot(ori_odo_left_x(1,:), ori_odo_left_y(1,:), '--k');
    plot(ori_odo_right_x(1,:), ori_odo_right_y(1,:), '--k');
   
end


% optimize path
if opt_hdl == 1
    if history_cache == 0
        opt_file = readtable(opt_log);
        opt_size = size(opt_file,1);
        opt_str  = string(opt_file{:,1:13});
        
        op_path_point_x      = str2double(opt_str(:,2)).';
        op_path_point_y      = str2double(opt_str(:,3)).';
        op_path_point_yaw    = str2double(opt_str(:,5)).';
        op_left_point_x      = str2double(opt_str(:,8)).';
        op_left_point_y      = str2double(opt_str(:,9)).';
        op_right_point_x     = str2double(opt_str(:,10)).';
        op_right_point_y     = str2double(opt_str(:,11)).';
        op_left_type         = str2double(opt_str(:,12)).';
        op_right_type        = str2double(opt_str(:,13)).';
        
        if(size(op_path_point_x)~=0)
            op_odo_left_x = 0 - sin(op_path_point_yaw(1,:)) * veh_half_width + op_path_point_x(1,:);
            op_odo_left_y = 0 + cos(op_path_point_yaw(1,:)) * veh_half_width + op_path_point_y(1,:);
    
            op_odo_right_x = 0 - sin(op_path_point_yaw(1,:)) * -veh_half_width + op_path_point_x(1,:);
            op_odo_right_y = 0 + cos(op_path_point_yaw(1,:)) * -veh_half_width + op_path_point_y(1,:);
        end

        op_left_dynamic = [];
        op_right_dynamic = [];
        for i = 1 : opt_size
            if op_left_type(1, i) == 2
                op_left_dynamic = [op_left_dynamic, [op_left_point_x(1, i); op_left_point_y(1, i)]];
            end
    
            if op_right_type(1, i) == 2
                op_right_dynamic = [op_right_dynamic, [op_right_point_x(1, i); op_right_point_y(1, i)]];
            end
        end
    end

    plot(op_path_point_x(1,:), op_path_point_y(1,:), '-b', 'MarkerSize', 3);

    plot(op_odo_left_x(1,:), op_odo_left_y(1,:), '-b', 'MarkerSize', 3);
    plot(op_odo_right_x(1,:), op_odo_right_y(1,:), '-b', 'MarkerSize', 3);

    plot(op_left_point_x(1,:), op_left_point_y(1,:), '*b', 'MarkerSize', 3);
    plot(op_right_point_x(1,:), op_right_point_y(1,:), '*b', 'MarkerSize', 3);

    plot(op_right_point_x(1,:), op_right_point_y(1,:), '*b', 'MarkerSize', 3);
    plot(op_right_point_x(1,:), op_right_point_y(1,:), '*b', 'MarkerSize', 3);

    plot(op_left_dynamic(1,:), op_left_dynamic(2,:), 'oy', 'MarkerSize', 2, "LineWidth", 2);
    plot(op_right_dynamic(1,:), op_right_dynamic(2,:), 'oy', 'MarkerSize', 2, "LineWidth", 2);
end


% map
if navi_hdl == 1
    if history_cache == 0
        % map_file = importdata(navi_log);
        map_file = fopen(navi_log,'r');
        map_pathpoint_x = {};
        map_pathpoint_y = {};
        orig_pathpoint_x = [];
        orig_pathpoint_y = [];
        if map_file ~= -1
            map_pathpoint_count = 1;
            obj_cnt=0;
            obj_flag=0;

            while ~feof(map_file)
                tline = fgetl(map_file);
            
                Is_map_pathpoint=contains(tline,"INFO]idx=");
                if Is_map_pathpoint
                    map_pathpoint = split(tline,"point=");
                    map_pathpoint = split(map_pathpoint(2,1),",");
                    map_pathpoint_x(map_pathpoint_count,:) = map_pathpoint(1,1);
                    map_pathpoint_y(map_pathpoint_count,:) = map_pathpoint(2,1);
            
                    map_pathpoint_count=map_pathpoint_count+1;
                end
            end
        end

        if size(map_pathpoint_x, 1) ~= 0
            orig_pathpoint_x(1,:)=(str2double(map_pathpoint_x(:,1)));
            orig_pathpoint_y(1,:)=(str2double(map_pathpoint_y(:,1)));
        end
    end

    if size(orig_pathpoint_y, 1) ~= 0
        plot(orig_pathpoint_x(1,:), orig_pathpoint_y(1,:), '-g');
    end
end


% obj & brake
if obj_hdl == 1
    if history_cache == 0
        planning_obj_file = fopen(obj_log,'r');
    
        brake_inx=0;
        obj_cnt=0;
        brake_cnt=0;
        obj_point_cnt=0;
        obj_flag=0;
        fs_cnt = 0;
        freespace_collision = [0, 0];
        brake_obj_index = [];

        while ~feof(planning_obj_file)
            tline = fgetl(planning_obj_file);

            if obj_flag
                obj_point_cnt=obj_point_cnt+1;
        
                obj_point = split(tline,"]");
                obj_cnt = obj_cnt+1;
        
                obj_point = split(obj_point(2,1));
                obj_x(1,obj_cnt)=obj_point(1,1);
                obj_y(1,obj_cnt)=obj_point(2,1);
        
                if obj_point_cnt == 4
                    obj_flag=0;
                    obj_point_cnt=0;
                end
            end
        
            Is_obj_start = contains(tline, "obs position:");
    
            if Is_obj_start
                obj_flag=1;
            end
    
            if ( contains(tline, "foaDis,") )
                brakeStatus = split(tline,": ");
                brakeStatus = split(brakeStatus(2,:), "  ");
                brake_inx = brake_inx + 1;
                brake_status = str2double(brakeStatus(5,1));
                steering_wheel = str2double(brakeStatus(8,1));
    
                brake_p(brake_inx, 1) = num2cell(brake_inx);
                brake_p(brake_inx, 2) = num2cell(brake_status);

                steering_wheel_p(brake_inx, 1) = num2cell(brake_inx);
                steering_wheel_p(brake_inx, 2) = num2cell(steering_wheel*57.3);

                if ( brake_status ~= 0 )
                    brake_cnt = brake_cnt + 1;
                    brake_obj_index(1, brake_cnt) = obj_cnt / 4;
                end
            end

            if ( contains(tline, "freespace:	") )
                fs_cnt = fs_cnt+ 1;
                freespace = split(tline, "freespace:	");
                freespace = split(freespace(2,1), ", ");
                freespace = str2double(freespace).';
                freespace_collision(fs_cnt, 1)= freespace(1, 1);
                freespace_collision(fs_cnt, 2)= freespace(1, 2);
                freespace_collision(fs_cnt, 3)= freespace(1, 3);
            end
        end
        
        brake_p = cell2mat( brake_p.');
        steering_wheel_p = cell2mat( steering_wheel_p.');

        if(obj_cnt > 0)
            obj_list_x(1,:)=(str2double(obj_x(1,:)));
            obj_list_y(1,:)=(str2double(obj_y(1,:)));
        else
            obj_list_x = 0;
            obj_list_y = 0;
        end

        j = 0;
        obj_num = 0;
        nan_flag = 0;
        obj_list_p = 0;

        brake_obj = cell(obj_cnt / 4, 3);

        obj_x_p = [];
        for i = 1 : obj_cnt
            if isnan(obj_list_x(1, i))
                if nan_flag ~= 1 && size(obj_x_p, 1) ~= 0
                    obj_x_p(1,j+1) = obj_x_p(1, 1);
                    obj_y_p(1,j+1) = obj_y_p(1, 1);
                    
                    obj_num = obj_num + 1;
                    brake_obj(obj_num, 1) = {j+1};
                    brake_obj(obj_num, 2) = {obj_x_p};
                    brake_obj(obj_num, 3) = {obj_y_p};

                    obj_x_p = 0;
                    obj_y_p = 0;
                    j = 0;
                    nan_flag = 1;
                end
            else
                j = j + 1;

                obj_x_p(1,j) = obj_list_x(1, i);
                obj_y_p(1,j) = obj_list_y(1, i);

                nan_flag = 0;

                if (j == 4)
                    obj_x_p(1,j+1) = obj_x_p(1, 1);
                    obj_y_p(1,j+1) = obj_y_p(1, 1);
                    
                    obj_num = obj_num + 1;
                    brake_obj(obj_num, 1) = {j+1};
                    brake_obj(obj_num, 2) = {obj_x_p};
                    brake_obj(obj_num, 3) = {obj_y_p};

                    obj_x_p = 0;
                    obj_y_p = 0;
                    j = 0;
                end
            end
        end
    end

    plot(freespace_collision(:,1), freespace_collision(:,2), 'pr', "MarkerSize", 6, "LineWidth", 2);
    
    if 1
        brake_obj_index = round(brake_obj_index(brake_obj_index>0));
        brake_size = size(brake_obj_index, 2);
        if size(brake_obj, 1) ~= 0
            for i = 1 : brake_size
                obj_x_p = cell2mat(brake_obj(brake_obj_index(i), 2));
                obj_y_p = cell2mat(brake_obj(brake_obj_index(i), 3));
                line(obj_x_p, obj_y_p, 'Color','red','LineWidth', 2);
            end
    
            plot(obj_list_x(1,:),obj_list_y(1,:),'xk');
        end
    else
        plot(obj_list_x(1,:),obj_list_y(1,:),'xk');
    end

    brake_fig = figure('NumberTitle', 'off', "Name","brake status");
    plot(brake_p(1,:), brake_p(2,:),'-b');
    title("fakeman");
    xlabel('X: index');
    ylabel('Y: brake status');
    legend({'index', 'brake status'},'Location','northeast');

    steering_wheel_fig = figure('NumberTitle', 'off', "Name", "steering wheel angle");
    plot(steering_wheel_p(1,:), steering_wheel_p(2,:),'-b');
    xlabel('X: index');
    ylabel('Y: steering wheel angle');
    legend({'index', 'steering wheel angle'},'Location','northeast');
    
    figure(main_fig);
end


% odo & ref_path & outline
if path_odo_hdl == 1
    if history_cache == 0
        path_odo_file = fopen(path_odo_log,'r');

        Gp_count = 0;
        refer_pathpoint_count = 0;
        pub_pathpoint_count = 0;
        ga_size=size(path_odo_file,1);
    
        while ~feof(path_odo_file)
            str = fgetl(path_odo_file);
        
            IsGPGGA=contains(str,"odometry position:");
            if IsGPGGA
                Gp_count = Gp_count + 1;
                str = split(str,"odometry position:");
                GP(:, Gp_count) = split(str(2,1), ",");
            end
     
            Is_pub_pathpoint=contains(str, "Refer point :");
            if Is_pub_pathpoint
                refer_pathpoint_count = refer_pathpoint_count + 1;
    
                refer_pathpoint = split(str, "Refer point : ");
                refer_pathpoint = split(refer_pathpoint(2, :), ",").';
    
                refer_pathpoint_x(:,refer_pathpoint_count) = refer_pathpoint(1, 1);
                refer_pathpoint_y(:,refer_pathpoint_count) = refer_pathpoint(1, 2);
                refer_pathpoint_yaw(:,refer_pathpoint_count) = refer_pathpoint(1, 4);
            end
            
            Is_pub_pathpoint=contains(str,"Fix_Conv_pathpoint(0)");
            if Is_pub_pathpoint
                pub_pathpoint_count=pub_pathpoint_count+1;
                
                pub_pathpoint = split(str,",");
        
                pub_pathpoint_x(:,pub_pathpoint_count)=split(pub_pathpoint(2,1),"=");
                pub_pathpoint_y(:,pub_pathpoint_count)=split(pub_pathpoint(3,1),"=");
                pub_pathpoint_yaw(:,pub_pathpoint_count)=split(pub_pathpoint(5,1),"=");
            end
        end

        GP = str2double(GP(1:3,:));
    end


%     odo
    if odo_hdl ~= 0
        pos_x(1,:) = (GP(1,:));
        pos_y(1,:) = (GP(2,:));
        pos_yaw(1,:) = (GP(3,:));
    
        if size(pos_x, 1)~=0
            plot(pos_x(1,1), pos_y(1,1), 'ok');
            plot(pos_x(1,:), pos_y(1,:), '.-k');
    
            if 1
                odo_left_x = 0 - sin(pos_yaw(1,:))* veh_half_width + pos_x(1,:);
                odo_left_y = 0 + cos(pos_yaw(1,:))* veh_half_width + pos_y(1,:);
                plot(odo_left_x(1,:), odo_left_y(1,:), '.-k');
        
                odo_right_x = 0 - sin(pos_yaw(1,:))*-veh_half_width + pos_x(1,:);
                odo_right_y = 0 + cos(pos_yaw(1,:))*-veh_half_width + pos_y(1,:);
                plot(odo_right_x(1,:), odo_right_y(1,:), '.-k');
            end
        end
    end


%     brake situation
    if brake_hdl == 1
        size_brake = size(brake_p,2);
        size_pos = size(pos_x,2);
        diff_inx = size_pos - size_brake;
        brake_cnt = 0;
        for( i = 1 : size_brake)
            if(brake_p(2,i) ~= 0)
                brake_cnt = brake_cnt + 1;
                brake_x(brake_cnt,:) = pos_x(1, i+diff_inx);
                brake_y(brake_cnt,:) = pos_y(1, i+diff_inx);
                brake_yaw(brake_cnt,:) = pos_yaw(1, i+diff_inx);
            end
        end
    
        if brake_cnt ~= 0
            plot(brake_x(:,1), brake_y(:,1), 'dr',"MarkerSize", 10, "LineWidth", 2);
            
            brake_x = brake_x.';
            brake_y = brake_y.';
            brake_yaw = brake_yaw.';
    
            veh_fl_body_x = cos(brake_yaw(1,:))*veh_fl_body(1,1) - sin(brake_yaw(1,:)) * veh_fl_body(1,2) + brake_x(1,:);
            veh_fl_body_y = cos(brake_yaw(1,:))*veh_fl_body(1,2) + sin(brake_yaw(1,:)) * veh_fl_body(1,1) + brake_y(1,:);
            plot(veh_fl_body_x(1,:), veh_fl_body_y(1,:), '*r',"MarkerSize", 5);
        
            veh_fr_body_x = cos(brake_yaw(1,:))*veh_fr_body(1,1) - sin(brake_yaw(1,:)) * veh_fr_body(1,2) + brake_x(1,:);
            veh_fr_body_y = cos(brake_yaw(1,:))*veh_fr_body(1,2) + sin(brake_yaw(1,:)) * veh_fr_body(1,1) + brake_y(1,:);
            plot(veh_fr_body_x(1,:), veh_fr_body_y(1,:), '*r',"MarkerSize", 5);
        
            veh_rl_body_x = cos(brake_yaw(1,:))*veh_rl_body(1,1) - sin(brake_yaw(1,:)) * veh_rl_body(1,2) + brake_x(1,:);
            veh_rl_body_y = cos(brake_yaw(1,:))*veh_rl_body(1,2) + sin(brake_yaw(1,:)) * veh_rl_body(1,1) + brake_y(1,:);
            plot(veh_rl_body_x(1,:), veh_rl_body_y(1,:), '*r',"MarkerSize", 5);
        
            veh_rr_body_x = cos(brake_yaw(1,:))*veh_rr_body(1,1) - sin(brake_yaw(1,:)) * veh_rr_body(1,2) + brake_x(1,:);
            veh_rr_body_y = cos(brake_yaw(1,:))*veh_rr_body(1,2) + sin(brake_yaw(1,:)) * veh_rr_body(1,1) + brake_y(1,:);
            plot(veh_rr_body_x(1,:), veh_rr_body_y(1,:), '*r',"MarkerSize", 5);
        
            for(i = 1 : brake_cnt )
                a = [veh_fl_body_x(1,i) veh_fr_body_x(1,i) veh_rr_body_x(1,i) veh_rl_body_x(1,i) veh_fl_body_x(1,i)];
                b = [veh_fl_body_y(1,i) veh_fr_body_y(1,i) veh_rr_body_y(1,i) veh_rl_body_y(1,i) veh_fl_body_y(1,i)];
                line(a, b, 'Color','blue','LineWidth', 2);
            end
        end
    end


%   refer path
    if ref_path_hdl ~= 0
        if size(refer_pathpoint_x, 1) ~= 0
            referpoint_x(1,:) = (str2double(refer_pathpoint_x(1,:)));
            referpoint_y(1,:) = (str2double(refer_pathpoint_y(1,:)));
            referpoint_yaw(1,:) = (str2double(refer_pathpoint_yaw(1,:)));
            plot(referpoint_x(1,:), referpoint_y(1,:), '--y', "LineWidth", 3);
        end
    end


% ctrl_err_hdl
    if ctrl_err_hdl ~= 0 
        size_ref_point = size(referpoint_x, 2);
        size_odo_point = size(GP, 2);

        odo_x = GP(1, :);
        odo_y = GP(2, :);
        odo_yaw = GP(3, :);

        if size_odo_point > size_ref_point
            diff_inx = size_odo_point - size_ref_point + 1;
            odo_x = odo_x(1, diff_inx : size_odo_point);
            odo_y = odo_y(1, diff_inx : size_odo_point);
            odo_yaw = odo_yaw(1, diff_inx : size_odo_point);
        else
            diff_inx = size_ref_point - size_odo_point + 1;
            referpoint_x = referpoint_x(1, diff_inx : size_ref_point);
            referpoint_y = referpoint_y(1, diff_inx : size_ref_point);
            referpoint_yaw = referpoint_yaw(1, diff_inx : size_ref_point);
        end
        
        referpoint_x_pt = referpoint_x(2:end); 
        referpoint_y_pt = referpoint_y(2:end);
        referpoint_yaw_deg = mod( (referpoint_yaw(2:end) * 57.3) + 360, 360);
        odo_x = odo_x(2:end);
        odo_y = odo_y(2:end);
        odo_yaw_deg = mod( (odo_yaw(2:end) * 57.3) + 360, 360);

        diff_lateral = sind(referpoint_yaw_deg).* (odo_x - referpoint_x_pt) - cosd(referpoint_yaw_deg).* (odo_y - referpoint_y_pt);
        diff_lateral_abs = abs(diff_lateral);
        diff_dist = sqrt((odo_x - referpoint_x_pt).^2 + (odo_y - referpoint_y_pt).^2);
        diff_yaw = odo_yaw_deg - referpoint_yaw_deg;

        k = size(diff_yaw, 2);
        for i=1:k
            if diff_yaw(1,i) > 300
                diff_yaw(1,i) = diff_yaw(1,i) - 360;
            elseif diff_yaw(1,i) < -300
                diff_yaw(1,i) = 360 + diff_yaw(1,i);
            end
        end
        diff_yaw = abs(diff_yaw);

        diff_lateral_average = sum(diff_lateral_abs) / size_ref_point;
        diff_yaw_average = sum(diff_yaw) / size_ref_point;
        diff_dist_average = sum(diff_dist) / size_ref_point;

    if 1
        odo_error_fig = figure('NumberTitle', 'off', "Name","lateral error");
        plot(diff_lateral, '-b');
        xlabel('X: index');
        ylabel('Y: lateral error');
        legend({'index', 'lateral error: m'},'Location','northeast');
        
        yaw_error_fig = figure('NumberTitle', 'off', "Name","yaw angle error");
        plot(diff_yaw, '-b');
        xlabel('X: index');
        ylabel('Y: yaw angle error');
        legend({'index', 'yaw angle error'},'Location','northeast');
    else
        ctrl_error_fig = figure('NumberTitle', 'off', "Name", "ctrl error");
%         plot(diff_dist_percent, '-b');
%         plot(diff_yaw_percent, '-r');
        xlabel('X: index');
        ylabel('Y: unit: %');
        hold on;
        legend({'index', 'dist error', 'yaw error'},'Location','northeast');
    end

        figure(main_fig);
    end
end


legend({'none', 'none', 'none','none','none'},'Location','northeast');


figure(main_fig);

if obj_hdl ~= 0
    figure(brake_fig);
    figure(steering_wheel_fig);
end

if path_odo_hdl ~= 0 && ctrl_err_hdl ~= 0
    if 1
        figure(odo_error_fig);
        figure(yaw_error_fig);
    else
        figure(ctrl_error_fig);
    end
end


fprintf("diff_lateral = %f cm \n", diff_lateral_average*100 );
fprintf("diff_yaw_average = %f ° \n", diff_yaw_average );
% fprintf("diff_dist_average = %f \n", diff_dist_average );




% figure(main_fig);
% hold on;
% predict_path = [5.528624232 7.353584443 7.353584443 -1.326868086;
% 5.552775869 7.256544791 7.256544791 -1.324123518;
% 5.577193743 7.159571811 7.159571811 -1.320408702;
% 5.601971676 7.062690238 7.062690238 -1.315725819;
% 5.627203012 6.965925794 6.965925794 -1.309602341;
% 5.65302638 6.869317763 6.869317763 -1.302129481;
% 5.679570946 6.772905447 6.772905447 -1.293978548;
% 5.706900461 6.676712734 6.676712734 -1.28573541;
% 5.735021977 6.580748539 6.580748539 -1.277413603;
% 5.763941093 6.485021726 6.485021726 -1.268542826;
% 5.79370822 6.389555246 6.389555246 -1.258731234;
% 5.824410544 6.294385527 6.294385527 -1.248038058;
% 5.856128748 6.19954958 6.19954958 -1.237007065;
% 5.888891127 6.105069305 6.105069305 -1.225721507;
% 5.922717652 6.010964799 6.010964799 -1.214258079;
% 5.957620688 5.917254248 5.917254248 -1.202687151;
% 5.993605678 5.823953829 5.823953829 -1.191073008;
% 6.03067182 5.731077629 5.731077629 -1.179474107;
% 6.068812709 5.63863759 5.63863759 -1.16794333;
% 6.108016947 5.546643471 5.546643471 -1.156528243;
% 6.148268735 5.455102845 5.455102845 -1.145271366;
% 6.189548418 5.364021102 5.364021102 -1.134210437;
% 6.231833014 5.273401496 5.273401496 -1.123378674;
% 6.275096689 5.183245194 5.183245194 -1.11280504;
% 6.319311218 5.093551356 5.093551356 -1.102514505;
% 6.364446399 5.004317227 5.004317227 -1.092528302;
% 6.410470437 4.915538247 4.915538247 -1.082864179;
% 6.457350296 4.827208163 4.827208163 -1.073536643;
% 6.505052018 4.739319166 4.739319166 -1.064557204;
% 6.553541013 4.651862018 4.651862018 -1.055934598;
% 6.602782318 4.564826194 4.564826194 -1.047713824;
% 6.652737467 4.478198083 4.478198083 -1.039883903;
% 6.703369381 4.391963749 4.391963749 -1.032395181;
% 6.754645665 4.306110979 4.306110979 -1.025251772;
% 6.806533928 4.220626666 4.220626666 -1.018455662;
% 6.859001959 4.135496946 4.135496946 -1.01200691;
% 6.912017885 4.050707332 4.050707332 -1.005903828;
% 6.965550309 3.96624284 3.96624284 -1.000143166;
% 7.019568422 3.882088117 3.882088117 -0.9947450312;
% 7.074040033 3.798226201 3.798226201 -0.9896762507;
% 7.128936027 3.714641456 3.714641456 -0.9849387073;
% 7.184227398 3.631317708 3.631317708 -0.9805150107;
% 7.239886831 3.548239358 3.548239358 -0.9763631417;
% 7.295890719 3.465392807 3.465392807 -0.9725107615;
% 7.352213353 3.382762609 3.382762609 -0.9689478692;
% 7.408830036 3.300333601 3.300333601 -0.9656639933;
% 7.465717104 3.218090952 3.218090952 -0.9626956331;
% 7.522848052 3.13601752 3.13601752 -0.960027697;
% 7.580197766 3.054096797 3.054096797 -0.9575486157;
% 7.637750394 2.972318498 2.972318498 -0.9552514386;
% 7.695490731 2.890672619 2.890672619 -0.9531780935;
% 7.753400226 2.809146628 2.809146628 -0.9513170805;
% 7.811461344 2.727728547 2.727728547 -0.9496569631;
% 7.869657547 2.646406963 2.646406963 -0.9481864187;
% 7.927973275 2.565171046 2.565171046 -0.946941176;
% 7.986390118 2.484007806 2.484007806 -0.9459044903;
% 8.044891071 2.402905169 2.402905169 -0.9449683805;
% 8.103467919 2.321857331 2.321857331 -0.9441286758;
% 8.162112804 2.240858707 2.240858707 -0.9434260716;
% 8.220814585 2.159901308 2.159901308 -0.9428506972;
% 8.279562937 2.078977696 2.078977696 -0.9423930112;
% 8.338348321 1.998080981 1.998080981 -0.9420438165;
% 8.39716195 1.917204798 1.917204798 -0.9418306557;
% 8.455992818 1.836341154 1.836341154 -0.9417397462;
% 8.514831036 1.755482858 1.755482858 -0.9417133952;
% 8.573671386 1.674626112 1.674626112 -0.9417133952;
% 8.632511735 1.593769367 1.593769367 -0.9417556813;
% 8.691348665 1.512910133 1.512910133 -0.9418695439;
% 8.750176388 1.432044201 1.432044201 -0.9420387753;
% 8.808990425 1.351168315 1.351168315 -0.9422571346;
% 8.867786801 1.270279588 1.270279588 -0.942518745;
% 8.926562013 1.189375481 1.189375481 -0.9428403652;
% 8.985311201 1.108452477 1.108452477 -0.9432130824;
% 9.044030225 1.02750758 1.02750758 -0.943586965;
% 9.10271898 0.9465407359 0.9465407359 -0.9439614999;
% 9.161377406 0.8655519161 0.8655519161 -0.9443555767;
% 9.220003911 0.7845399867 0.7845399867 -0.9447653288;
% 9.278597217 0.7035040419 0.7035040419 -0.9451871889;
% 9.337156332 0.6224433861 0.6224433861 -0.945617877;
% 9.39568053 0.5413575171 0.5413575171 -0.9460662532;
% 9.454168364 0.4602454155 0.4602454155 -0.9465272809;
% 9.512618798 0.379106358 0.379106358 -0.9469845421;
% 9.571032123 0.2979405819 0.2979405819 -0.9474362369;
% 9.629408781 0.216748429 0.216748429 -0.9478729015;
% 9.687749979 0.1355307928 0.1355307928 -0.9482948007;
% 9.746056907 0.05428854966 0.05428854966 -0.94871006;
% 9.804330092 -0.02697789896 -0.02697789896 -0.9491172603;
% 9.862570182 -0.1082680697 -0.1082680697 -0.9495151612;
% 9.920777921 -0.1895814079 -0.1895814079 -0.949906707;
% 9.978953818 -0.2709175308 -0.2709175308 -0.9502899414;
% 10.03709854 -0.3522759428 -0.3522759428 -0.9506591677;
% 10.09521322 -0.4336558178 -0.4336558178 -0.9510140032;
% 10.15329902 -0.5150563089 -0.5150563089 -0.9513523989;
% 10.21135727 -0.5964764513 -0.5964764513 -0.9516748129;
% 10.26938926 -0.6779153084 -0.6779153084 -0.9519834678;
% 10.32739612 -0.7593720735 -0.7593720735 -0.9522781695;
% 10.38537896 -0.8408459297 -0.8408459297 -0.9525589771;
% 10.44333893 -0.9223360648 -0.9223360648 -0.9528255333;
% 10.50127718 -1.003841647 -1.003841647 -0.9530774529;
% 10.55919488 -1.085361822 -1.085361822 -0.9533149706;
% 10.61709323 -1.166895751 -1.166895751 -0.9535392786;
% 10.67497328 -1.248442665 -1.248442665 -0.9537508025;
% 10.73283609 -1.330001821 -1.330001821 -0.9539490497;
% 10.79068272 -1.411572446 -1.411572446 -0.9541343282;
% 10.84851424 -1.493153787 -1.493153787 -0.9543069808;
% 10.90633168 -1.574745112 -1.574745112 -0.9544657055;
% 10.96413616 -1.656345613 -1.656345613 -0.9546109807;
% 11.02192879 -1.737954511 -1.737954511 -0.9547468326;
% 11.07971033 -1.819571259 -1.819571259 -0.9548735938;
% 11.13748152 -1.901195331 -1.901195331 -0.9549897564;
% 11.19524323 -1.982826113 -1.982826113 -0.9550957756;
% 11.25299629 -2.064463019 -2.064463019 -0.9551921131;
% 11.31074148 -2.146105488 -2.146105488 -0.9552772508;
% 11.36847972 -2.227752873 -2.227752873 -0.9553518629;
% 11.42621187 -2.309404566 -2.309404566 -0.955418602;
% 11.48393857 -2.391060112 -2.391060112 -0.9554779202;
% 11.54166043 -2.472719082 -2.472719082 -0.9555321712;
% 11.59937785 -2.554381183 -2.554381183 -0.9555815565;
% 11.65709125 -2.636046134 -2.636046134 -0.9556243651;
% 11.71480114 -2.717713556 -2.717713556 -0.9556610253;
% 11.77250805 -2.799383094 -2.799383094 -0.9556919542;
% 11.83021242 -2.881054416 -2.881054416 -0.9557175568;
% 11.88791471 -2.962727216 -2.962727216 -0.9557290763;
% 11.94561605 -3.04440068 -3.04440068 -0.9557290763;
% 12.0033174 -3.126074145 -3.126074145 -0.9557290763;
% 12.06101874 -3.207747609 -3.207747609 -0.9557290763;
% 12.11872009 -3.289421074 -3.289421074 -0.9557290763;
% 12.17642143 -3.371094538 -3.371094538 -0.9557290763;
% 12.23412278 -3.452768003 -3.452768003 -0.9557290763;
% 12.29182412 -3.534441467 -3.534441467 -0.9557290763;
% 12.34952547 -3.616114931 -3.616114931 -0.9557290763;
% 12.40722681 -3.697788396 -3.697788396 -0.9557290763;
% 12.46492816 -3.77946186 -3.77946186 -0.9557290763;
% 12.5226295 -3.861135325 -3.861135325 -0.9557290763;
% 12.58033085 -3.942808789 -3.942808789 -0.9557290763;
% 12.63803219 -4.024482254 -4.024482254 -0.9557290763;
% 12.69573354 -4.106155718 -4.106155718 -0.9557290763;
% 12.75343488 -4.187829182 -4.187829182 -0.9557195115;
% 12.81113701 -4.269502095 -4.269502095 -0.9557001145;
% 12.86884072 -4.351173888 -4.351173888 -0.9556796367;
% 12.9265461 -4.4328445 -4.4328445 -0.9556583386;
% 12.98425322 -4.514513882 -4.514513882 -0.9556375955;
% 13.04196204 -4.596182068 -4.596182068 -0.9556174032;
% 13.09967251 -4.677849088 -4.677849088 -0.9555972404;
% 13.15738462 -4.759514945 -4.759514945 -0.9555772047;
% 13.21509837 -4.841179645 -4.841179645 -0.9555573833;
% 13.27281373 -4.922843201 -4.922843201 -0.9555375549;
% 13.33053072 -5.004505613 -5.004505613 -0.9555178552;
% 13.38824931 -5.086166888 -5.086166888 -0.9554987033;
% 13.44596947 -5.167827058 -5.167827058 -0.9554801364;
% 13.50369115 -5.249486155 -5.249486155 -0.9554710034;
% 13.56141357 -5.331144726 -5.331144726 -0.9554617466;
% 13.61913675 -5.412802762 -5.412802762 -0.9554524897;
% 13.67686068 -5.494460264 -5.494460264 -0.9554429329;
% 13.73458539 -5.576117214 -5.576117214 -0.9554242649;
% 13.79231163 -5.657773087 -5.657773087 -0.9554151535;
% 13.85003861 -5.739428433 -5.739428433 -0.955406043;
% 13.90776633 -5.821083254 -5.821083254 -0.9553969325;
% 13.9654948 -5.902737549 -5.902737549 -0.9553879091;
% 14.02322401 -5.984391323 -5.984391323 -0.9553788857;
% 14.08095395 -6.066044576 -6.066044576 -0.9553788857;
% 14.13868389 -6.147697829 -6.147697829 -0.955369668;
% 14.19641459 -6.22935055 -6.22935055 -0.9553604504;
% 14.25414604 -6.311002738 -6.311002738 -0.9553513883;
% 14.31187823 -6.392654404 -6.392654404 -0.9553423263;
% 14.36961115 -6.474305546 -6.474305546 -0.9553423263;
% 14.42734408 -6.555956688 -6.555956688 -0.9553332921;
% 14.48507775 -6.637607309 -6.637607309 -0.9553242579;
% 14.54281215 -6.719257408 -6.719257408 -0.9553242579;
% 14.60054655 -6.800907508 -6.800907508 -0.9553242579;
% 14.65828096 -6.882557607 -6.882557607 -0.9553151433;
% 14.7160161 -6.96420718 -6.96420718 -0.9553060288;
% 14.773752 -7.045856226 -7.045856226 -0.9553060288;
% 14.83148789 -7.127505273 -7.127505273 -0.9553060288;
% 14.88922378 -7.20915432 -7.20915432 -0.9552970232;
% 14.94696041 -7.290802847 -7.290802847 -0.9552880176;
% 15.00469777 -7.372450853 -7.372450853 -0.9552880176;
% 15.06243513 -7.45409886 -7.45409886 -0.9552880176;
% 15.12017249 -7.535746867 -7.535746867 -0.9552880176;
% 15.17790985 -7.617394874 -7.617394874 -0.9552880176;
% 15.23564722 -7.699042881 -7.699042881 -0.9552880176;
% 15.29338458 -7.780690887 -7.780690887 -0.9552880176;
% 15.35112194 -7.862338894 -7.862338894 -0.9552789882;
% 15.40886004 -7.94398638 -7.94398638 -0.9552699587;
% 15.46659888 -8.025633344 -8.025633344 -0.9552699587;
% 15.52433771 -8.107280308 -8.107280308 -0.9552699587;
% 15.58207655 -8.188927272 -8.188927272 -0.9552699587;
% 15.63981539 -8.270574236 -8.270574236 -0.9552699587;
% 15.69755422 -8.3522212 -8.3522212 -0.9552699587;
% 15.75529306 -8.433868164 -8.433868164 -0.9552607741;
% 15.81303265 -8.515514598 -8.515514598 -0.9552515895;
% 15.87077298 -8.597160502 -8.597160502 -0.9552515895;
% 15.92851332 -8.678806405 -8.678806405 -0.9552515895;
% 15.98625365 -8.760452309 -8.760452309 -0.9552515895;
% 16.04399399 -8.842098212 -8.842098212 -0.9552515895;
% 16.10173433 -8.923744116 -8.923744116 -0.9552515895;
% 16.15947466 -9.005390019 -9.005390019 -0.9552515895;
% 16.217215 -9.087035923 -9.087035923 -0.9552515895;
% 16.27495534 -9.168681826 -9.168681826 -0.9552515895;
% 16.33269567 -9.25032773 -9.25032773 -0.9552515895;
% 16.39043601 -9.331973633 -9.331973633 -0.9552515895;
% 16.44817635 -9.413619537 -9.413619537 -0.9552515895;
% 16.50591668 -9.49526544 -9.49526544 -0.9552425268;
% 16.56365776 -9.57691082 -9.57691082 -0.9552334642;
% 16.62139957 -9.658555677 -9.658555677 -0.9552334642];
% 
% plot(predict_path(:,1), predict_path(:,2), '.-k');