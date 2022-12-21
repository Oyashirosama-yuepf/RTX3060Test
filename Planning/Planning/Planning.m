clc;
clear;

% for i = 0 : 1 : 1 %size(square,2)
k = 4;
% current_parkinglot_.single_lot.topleft.x = square(k).xy2t(1) + 2;
% current_parkinglot_.single_lot.topleft.y = square(k).xy2t(2);
% current_parkinglot_.single_lot.topright.x = square(k).xy1t(1) + 2;
% current_parkinglot_.single_lot.topright.y = square(k).xy1t(2);
% current_parkinglot_.single_lot.btmleft.x = square(k).xy4t(1);
% current_parkinglot_.single_lot.btmleft.y = square(k).xy4t(2);
% current_parkinglot_.single_lot.btmright.x = square(k).xy3t(1);
% current_parkinglot_.single_lot.btmright.y = square(k).xy3t(2);

current_parkinglot_.single_lot.topleft.x = 7.15862;
current_parkinglot_.single_lot.topleft.y = 3.66571;
current_parkinglot_.single_lot.topright.x = 6.87611;
current_parkinglot_.single_lot.topright.y = 9.40409;
current_parkinglot_.single_lot.btmleft.x = 4.36356;
current_parkinglot_.single_lot.btmleft.y = 3.5281;
current_parkinglot_.single_lot.btmright.x = 4.0501;
current_parkinglot_.single_lot.btmright.y = 9.26463;

ax = (current_parkinglot_.single_lot.topright.x + current_parkinglot_.single_lot.btmright.x) / 2;
ay = (current_parkinglot_.single_lot.topright.y + current_parkinglot_.single_lot.btmright.y) / 2;
bx = (current_parkinglot_.single_lot.topleft.x + current_parkinglot_.single_lot.btmleft.x) / 2;
by = (current_parkinglot_.single_lot.topleft.y + current_parkinglot_.single_lot.btmleft.y) / 2;     % 计算车位中线 

lambda = 0;
r = sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
lambda = 1 / (r - 1); 

current_parkinglot_.single_obj.lot_x = (ax + lambda * bx) / (1 + lambda);
current_parkinglot_.single_obj.lot_y = (ay + lambda * by) / (1 + lambda);           %库位底端

plot(ax, ay, 'rs','linewidth', 2); hold on;
plot(bx, by, 'rs','linewidth', 2); hold on;
line([ax, bx],[ay, by]);  %绘制车位中线
plot(current_parkinglot_.single_obj.lot_x, current_parkinglot_.single_obj.lot_y, 'ks','linewidth', 1); hold on;   %绘制泊入车位底端

lot_center.x = (current_parkinglot_.single_lot.topleft.x + current_parkinglot_.single_lot.topright.x + current_parkinglot_.single_lot.btmleft.x + current_parkinglot_.single_lot.btmright.x) / 4;
lot_center.y = (current_parkinglot_.single_lot.topleft.y + current_parkinglot_.single_lot.topright.y + current_parkinglot_.single_lot.btmleft.y + current_parkinglot_.single_lot.btmright.y) / 4;

plot(lot_center.x, lot_center.y, 'k*','linewidth', 1); hold on;      %绘制库位中心点

lx = lambda * current_parkinglot_.single_lot.topleft.x + (1 - lambda) * current_parkinglot_.single_lot.btmleft.x;
ly = lambda * current_parkinglot_.single_lot.topleft.y + (1 - lambda) * current_parkinglot_.single_lot.btmleft.y;
rx = lambda * current_parkinglot_.single_lot.topright.x + (1 - lambda) * current_parkinglot_.single_lot.btmright.x;
ry = lambda * current_parkinglot_.single_lot.topright.y + (1 - lambda) * current_parkinglot_.single_lot.btmright.y;

plot(lx, ly, 'k*','linewidth', 1); hold on;
plot(rx, ry, 'k*','linewidth', 1); hold on;    %绘制库位靠近车辆一端，用于判断是否走人字型

dis_x = (-ly * (rx - lx)) / (ry - ly) + lx;
disp(dis_x);
if (dis_x > 0)
    herringbone_mode_ = true;
    disp("enable herringbone_mode_");
else
    herringbone_mode_ = false;
    disp("disable herringbone_mode_");
end

plot(current_parkinglot_.single_lot.topleft.x, current_parkinglot_.single_lot.topleft.y, 'ro'); hold on;
plot(current_parkinglot_.single_lot.topright.x, current_parkinglot_.single_lot.topright.y, 'ro'); hold on;
plot(current_parkinglot_.single_lot.btmleft.x, current_parkinglot_.single_lot.btmleft.y, 'ro'); hold on;
plot(current_parkinglot_.single_lot.btmright.x, current_parkinglot_.single_lot.btmright.y, 'ro'); hold on;

plot(0,0, 'bo','linewidth', 3);

dis_x_offset = 0;
% 与入库点的夹角
delta_top_left_y = current_parkinglot_.single_lot.topleft.y - current_parkinglot_.single_lot.btmleft.y;
delta_btm_left_x = current_parkinglot_.single_lot.topleft.x - current_parkinglot_.single_lot.btmleft.x;
disp(delta_top_left_y);
disp(delta_btm_left_x);
line([current_parkinglot_.single_lot.btmleft.x, current_parkinglot_.single_lot.topleft.x],[current_parkinglot_.single_lot.btmleft.y, current_parkinglot_.single_lot.topleft.y]);  %绘制车位中线
current_parkinglot_.single_obj.lot_theta = atan2(delta_top_left_y, delta_btm_left_x);   %弧度
disp(current_parkinglot_.single_obj.lot_theta);
line([0,delta_btm_left_x],[0,delta_top_left_y]);

radius2_ = 5;

if herringbone_mode_
    
    k = 1;
    for i = 0.0: 0.02 : dis_x
        tmp_point.X(k) = i;
        tmp_point.Y(k) = 0;
        k = k + 1;
        disp(k);
    end
    k = 1;
    plot(tmp_point.X, tmp_point.Y, "b--", "LineWidth",3);
    diff = (current_parkinglot_.single_lot.topleft.x + current_parkinglot_.single_lot.btmleft.x) - (current_parkinglot_.single_lot.topright.x + current_parkinglot_.single_lot.btmright.x);
    disp(diff);
    if (abs((current_parkinglot_.single_lot.topleft.x + current_parkinglot_.single_lot.btmleft.x) - (current_parkinglot_.single_lot.topright.x + current_parkinglot_.single_lot.btmright.x)) > 0)
        k_af4_1 = (((current_parkinglot_.single_lot.topleft.y + current_parkinglot_.single_lot.btmleft.y) / 2) - (current_parkinglot_.single_lot.topright.y + current_parkinglot_.single_lot.btmright.y) / 2);
        k_af4_2 = (((current_parkinglot_.single_lot.topleft.x + current_parkinglot_.single_lot.btmleft.x) / 2) - (current_parkinglot_.single_lot.topright.x + current_parkinglot_.single_lot.btmright.x) / 2);
    
        k_af4 = k_af4_1 / k_af4_2;
    
        disp(" k_af4 : ");
        disp(k_af4);
    else
        k_af4 = 65535;
        disp(k_af4);
    end
    
    k_af4 = -1 * k_af4;
    delta_dot_1 = current_parkinglot_.single_obj.lot_y - k_af4 * current_parkinglot_.single_obj.lot_x + radius2_ * sqrt(k_af4 * k_af4 + 1) + radius2_;
    delta_dot_ = power((2 * k_af4 * delta_dot_1), 2) - 4 * (1 + k_af4 * k_af4) * (power(delta_dot_1,2) - 4 * power(radius2_,2));
    disp("delta_dot_");
    disp(delta_dot_);

    if delta_dot_ >= 0
        disp(k_af4);
        x_o3 = (-2 * k_af4 * (current_parkinglot_.single_obj.lot_y - k_af4 * current_parkinglot_.single_obj.lot_x + radius2_ * sqrt(k_af4 * k_af4 + 1) + radius2_) - sqrt(delta_dot_)) / 2 / (1 + k_af4 * k_af4);
        y_o3 = k_af4 * x_o3 + (current_parkinglot_.single_obj.lot_y - k_af4 * current_parkinglot_.single_obj.lot_x) + radius2_ * sqrt(1 + k_af4 * k_af4);
    %     if (current_parkinglot_.single_obj.lot_type == LEFT_VERTICAL)
    %         x_o3 = (-2 * k_af4 * (current_parkinglot_.single_obj.lot_y - k_af4 * current_parkinglot_.single_obj.lot_x + radius2_ * sqrt(k_af4 * k_af4 + 1) + radius2_) - sqrt(delta_dot_)) / 2 / (1 + k_af4 * k_af4);
    %         y_o3 = k_af4 * x_o3 + (current_parkinglot_.single_obj.lot_y - k_af4 * current_parkinglot_.single_obj.lot_x) + radius2_ * sqrt(1 + k_af4 * k_af4);
    %     end
        disp("x_o3");
        disp(x_o3);
        disp("y_o3");
        disp(y_o3);
        
        x_f2 = x_o3 / 2;
    
        y_f2 = (-radius2_ + y_o3) / 2;
    
        alpha_2 = asin(x_f2 / radius2_);
    
        x_o2 = 0;
        y_o2 = radius2_;
    
        x_o2f1 = 0;
        y_o2f1 = -y_o2;
        x_o2f2 = x_f2 - x_o2;
        y_o2f2 = y_f2 - y_o2;
    
        alpha_3 = alpha_2;
    
        x_o2f3 = (sin(alpha_2 - alpha_3) / sin(alpha_2)) * x_o2f1 + (sin(alpha_3) / sin(alpha_2)) * x_o2f2;
        y_o2f3 = (sin(alpha_2 - alpha_3) / sin(alpha_2)) * y_o2f1 + (sin(alpha_3) / sin(alpha_2)) * y_o2f2;

        disp("x_o2f3");
        disp(x_o2f3);
        disp("y_o2f3");
        disp(y_o2f3);
        
        k = 1;
        for i = 0: 0.01: alpha_3
            x_o2f = (sin(alpha_3 - i) / sin(alpha_3)) * x_o2f1 + (sin(i) / sin(alpha_3)) * x_o2f3;
            y_o2f = (sin(alpha_3 - i) / sin(alpha_3)) * y_o2f1 + (sin(i) / sin(alpha_3)) * y_o2f3;
            output_point.X(k) = x_o2 + x_o2f + dis_x_offset;
            output_point.Y(k) = y_o2 + y_o2f;
            k = k + 1;
        end
        k = 1;
        
        plot(output_point.X, output_point.Y, "r--", "LineWidth",3);
    end
end



