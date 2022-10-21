clc;
clear;

current_parkinglot_.single_lot.topleft.x = 4;
current_parkinglot_.single_lot.topleft.y = 2;
current_parkinglot_.single_lot.topright.x = 4;
current_parkinglot_.single_lot.topright.y = 8;
current_parkinglot_.single_lot.btmleft.x = 2;
current_parkinglot_.single_lot.btmleft.y = 2;
current_parkinglot_.single_lot.btmright.x = 2;
current_parkinglot_.single_lot.btmright.y = 8;

plot(current_parkinglot_.single_lot.topleft.x, current_parkinglot_.single_lot.topleft.y, 'ro', 'linewidth',3); hold on;
plot(current_parkinglot_.single_lot.topright.x, current_parkinglot_.single_lot.topright.y, 'ro', 'linewidth',3); hold on;
plot(current_parkinglot_.single_lot.btmleft.x, current_parkinglot_.single_lot.btmleft.y, 'ro', 'linewidth',3); hold on;
plot(current_parkinglot_.single_lot.btmright.x, current_parkinglot_.single_lot.btmright.y, 'ro', 'linewidth',3); hold on;

line([current_parkinglot_.single_lot.topleft.x,current_parkinglot_.single_lot.topright.x],[current_parkinglot_.single_lot.topleft.y, current_parkinglot_.single_lot.topright.y]);
line([current_parkinglot_.single_lot.topright.x,current_parkinglot_.single_lot.btmright.x],[current_parkinglot_.single_lot.topright.y, current_parkinglot_.single_lot.btmright.y]);
line([current_parkinglot_.single_lot.btmright.x,current_parkinglot_.single_lot.btmleft.x],[current_parkinglot_.single_lot.btmright.y, current_parkinglot_.single_lot.btmleft.y]);
line([current_parkinglot_.single_lot.topleft.x,current_parkinglot_.single_lot.btmleft.x],[current_parkinglot_.single_lot.topleft.y, current_parkinglot_.single_lot.btmleft.y]);

lot_center.x = (current_parkinglot_.single_lot.topleft.x + current_parkinglot_.single_lot.topright.x + current_parkinglot_.single_lot.btmleft.x + current_parkinglot_.single_lot.btmright.x) / 4;
lot_center.y = (current_parkinglot_.single_lot.topleft.y + current_parkinglot_.single_lot.topright.y + current_parkinglot_.single_lot.btmleft.y + current_parkinglot_.single_lot.btmright.y) / 4;

plot(lot_center.x, lot_center.y, 'ks', 'linewidth',3); hold on;

length = current_parkinglot_.single_lot.topright.y - current_parkinglot_.single_lot.topleft.y;
width = current_parkinglot_.single_lot.topleft.x - current_parkinglot_.single_lot.btmleft.x;

diagnol_line = sqrt(length^2 + width^2);
rectangle_center_angle_base = atan2(width,length);

k = 0;

for rotate_angle = 0:-5:-30

k = k + 1;

transformMatrix = [cosd(rotate_angle), sind(rotate_angle);
                   -sind(rotate_angle), cosd(rotate_angle)];

square(k).y1 = (cos(rectangle_center_angle_base) * diagnol_line * (1/2) + lot_center.y);
square(k).x1 = (sin(rectangle_center_angle_base) * diagnol_line * (1/2) + lot_center.x);

square(k).y2 = (-cos(rectangle_center_angle_base) * diagnol_line * (1/2) + lot_center.y);
square(k).x2 = (sin(rectangle_center_angle_base) * diagnol_line * (1/2) + lot_center.x);

square(k).y3 = (cos(rectangle_center_angle_base) * diagnol_line * (1/2) + lot_center.y);
square(k).x3 = (-sin(rectangle_center_angle_base) * diagnol_line * (1/2) + lot_center.x);

square(k).y4 = (-cos(rectangle_center_angle_base) * diagnol_line * (1/2) + lot_center.y);
square(k).x4 = (-sin(rectangle_center_angle_base) * diagnol_line * (1/2) + lot_center.x);

[square(k).xy1t] = transformMatrix * [square(k).x1; square(k).y1];
[square(k).xy2t] = transformMatrix * [square(k).x2; square(k).y2];
[square(k).xy3t] = transformMatrix * [square(k).x3; square(k).y3];
[square(k).xy4t] = transformMatrix * [square(k).x4; square(k).y4];

% plot(square.x1, square.y1, 'b*', 'linewidth',3); hold on;
% plot(square.x2, square.y2, 'b*', 'linewidth',3); hold on;
% plot(square.x3, square.y3, 'b*', 'linewidth',3); hold on;
% plot(square.x4, square.y4, 'b*', 'linewidth',3); hold on;

plot(square(k).xy1t(1), square(k).xy1t(2), 'b*', 'linewidth',3); hold on;
plot(square(k).xy2t(1), square(k).xy2t(2), 'b*', 'linewidth',3); hold on;
plot(square(k).xy3t(1), square(k).xy3t(2), 'b*', 'linewidth',3); hold on;
plot(square(k).xy4t(1), square(k).xy4t(2), 'b*', 'linewidth',3); hold on;

line([square(k).xy4t(1),square(k).xy3t(1)],[square(k).xy4t(2), square(k).xy3t(2)]);
line([square(k).xy3t(1),square(k).xy1t(1)],[square(k).xy3t(2), square(k).xy1t(2)]);
line([square(k).xy1t(1),square(k).xy2t(1)],[square(k).xy1t(2), square(k).xy2t(2)]);
line([square(k).xy2t(1),square(k).xy4t(1)],[square(k).xy2t(2), square(k).xy4t(2)]);

end
