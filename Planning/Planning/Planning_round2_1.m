
delta_parking_y = current_parkinglot_.single_lot.btmleft.y - current_parkinglot_.single_lot.btmright.y;
delta_parking_x = current_parkinglot_.single_lot.btmleft.x - current_parkinglot_.single_lot.btmright.x;
lot_theta2_for_judging = atan2(delta_parking_y, delta_parking_x);

% k_af4_1 = (((current_parkinglot_.single_lot.topleft.y + current_parkinglot_.single_lot.btmleft.y) / 2) - (current_parkinglot_.single_lot.topright.y + current_parkinglot_.single_lot.btmright.y) / 2);
% k_af4_2 = (((current_parkinglot_.single_lot.topleft.x + current_parkinglot_.single_lot.btmleft.x) / 2) - (current_parkinglot_.single_lot.topright.x + current_parkinglot_.single_lot.btmright.x) / 2);

k_af4_3 = (current_parkinglot_.single_obj.lot_y - (current_parkinglot_.single_lot.topright.y + current_parkinglot_.single_lot.btmright.y) / 2);
k_af4_4 = (current_parkinglot_.single_obj.lot_x - (current_parkinglot_.single_lot.topright.x + current_parkinglot_.single_lot.btmright.x) / 2);

plot(current_parkinglot_.single_obj.lot_x, current_parkinglot_.single_obj.lot_y, 'y*','linewidth', 3); hold on;
plot((current_parkinglot_.single_lot.topright.x + current_parkinglot_.single_lot.btmright.x) / 2, (current_parkinglot_.single_lot.topright.y + current_parkinglot_.single_lot.btmright.y) / 2, 'y*','linewidth', 3); hold on;    %绘制库位靠近车辆一端，用于判断是否走人字型

k_af4 = k_af4_3 / k_af4_4;
        
alpha_3  = asin(1 / sqrt(1 / k_af4 / k_af4 + 1));
radius_3 = abs(current_parkinglot_.single_obj.lot_y - k_af4 * current_parkinglot_.single_obj.lot_x) / sqrt(k_af4 * k_af4 + 1) / (1 - cos(alpha_3));
x_tangent_point = -radius_3 * sin(alpha_3);
