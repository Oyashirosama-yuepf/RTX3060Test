clc;
clear;


slot.topleft.x = -4.35126;
slot.topleft.y = 3.39865;
slot.topright.x = -4.5815;
slot.topright.y = 8.11547;

slot.btmleft.x = -6.91003;
slot.btmleft.y = 3.27369;
slot.btmright.x = -7.08769;
slot.btmright.y = 7.9929;

plot(slot.topleft.x, slot.topleft.y, "b*-", "LineWidth",3); hold on;
line([slot.topleft.x,slot.topright.x],[slot.topleft.y, slot.topright.y]);
plot(slot.topright.x, slot.topright.y, "b*-", "LineWidth",3); hold on;
line([slot.topright.x,slot.btmright.x],[slot.topright.y, slot.btmright.y]);
plot(slot.btmright.x, slot.btmright.y, "b*-", "LineWidth",3); hold on;
line([slot.btmright.x,slot.btmleft.x],[slot.btmright.y, slot.btmleft.y]);
plot(slot.btmleft.x, slot.btmleft.y, "b*-", "LineWidth",3); hold on;
line([slot.btmleft.x,slot.topleft.x],[slot.btmleft.y, slot.topleft.y]);

lot_theta = atan2(slot.btmleft.y - slot.btmright.y, slot.btmleft.x - slot.btmright.x);

in_centerx = (slot.topleft.x + slot.btmleft.x) / 2;
in_centery = (slot.topleft.y + slot.btmleft.y) / 2;

plot(in_centerx, in_centery, "ko-", "LineWidth",3); hold on;


offset_length = 0.3 * sqrt(in_centerx^2 + in_centery^2);
% px1 = -5.55678;
% py1 = 1.37413;
% plot(px1, py1, "k*-", "LineWidth",3); hold on;
px1 = in_centerx + offset_length * cos(lot_theta);
py1 = in_centery + offset_length * sin(lot_theta);
plot(px1, py1, "k*-", "LineWidth",3); hold on;     % 入库点

lambda = 0;
bx = (slot.topright.x + slot.btmright.x) / 2;
by = (slot.topright.y + slot.btmright.y) / 2;     % 库位底端 
pxf = bx / (1 + lambda);
pyf = by / (1 + lambda);           

plot(pxf, pyf, "b*-", "LineWidth",3); hold on;

p_step = 2.5;
px3 = pxf + p_step * cos(lot_theta);
py3 = pyf + p_step * sin(lot_theta);              %约为库位中心点

plot(px3, py3, "m*-", "LineWidth",3); hold on;

px2 = (px1 + px3) / 2;
py2 = (py1 + py3) / 2;

plot(px2, py2, "r*-", "LineWidth",3); hold on;

LENGTHOFPATH = 150;

for i = 1 : 1 : LENGTHOFPATH
    t(i) = i / (LENGTHOFPATH - 1);
end

for i = 1 : 1 : LENGTHOFPATH
    path.x(i) = 4 * px1 * power(1 - t(i), 3) * t(i) + 6 * px2 * power(1 - t(i), 2) * t(i) * t(i) + 4 * px3 * (1 - t(i)) * t(i) * t(i) * t(i) + pxf * power(t(i), 4);
    path.y(i) = 4 * py1 * power(1 - t(i), 3) * t(i) + 6 * py2 * power(1 - t(i), 2) * t(i) * t(i) + 4 * py3 * (1 - t(i)) * t(i) * t(i) * t(i) + pyf * power(t(i), 4);
end

plot(path.x, path.y, "r--", "LineWidth",2); hold on; grid on;

po_step = 10;
pxo = pxf + po_step * cos(lot_theta);
pyo = pyf + po_step * sin(lot_theta);

tmp_a.x                = pxo;
tmp_a.y                = pyo;
tmp_b.x                = pxf;
tmp_b.y                = pyf;

plot(pxo, pyo, "r*-", "LineWidth",3); hold on;

distance2line = 65535;
for i = 1 : 1 : LENGTHOFPATH / 2
    tmp_o.x             = path.x(i);
    tmp_o.y             = path.y(i);
    tmp_value(i) = DistanceFromPointToLine(tmp_a.x, tmp_b.x, tmp_o.x,  tmp_a.y, tmp_b.y, tmp_o.y);
    if distance2line > tmp_value(i)  
       distance2line = tmp_value(i);
       tmp_index     = i;
    end
end

extend_length = 1;
pxf                     = pxf - extend_length * cos(lot_theta);
pyf                     = pyf - extend_length * sin(lot_theta);
plot(pxf, pyf, "b*-", "LineWidth",3); hold on;

if (distance2line < 0.1 && tmp_index > 0)
    po_step = Distance(path.x(tmp_index), path.y(tmp_index), pxf, pyf);
    for i = tmp_index :1 : LENGTHOFPATH   
        path.x(i) = pxf + (LENGTHOFPATH - i - 1) / (LENGTHOFPATH - tmp_index) * po_step * cos(lot_theta);
        path.y(i) = pyf + (LENGTHOFPATH - i - 1) / (LENGTHOFPATH - tmp_index) * po_step * sin(lot_theta);    
    end
end

plot(path.x, path.y, "r--", "LineWidth",2); hold on; grid on;

p_s.x = slot.btmleft.x;
p_s.y = slot.btmleft.y;
p_e.x = slot.topleft.x;
p_e.y = slot.topleft.y;
p_u.x = 0;
p_u.y = 0;


p_a.x = (p_s.x + p_e.x) / 2;
p_a.y = (p_s.y + p_e.y) / 2;
p_b.x = lot.single_obj.lot_x;
p_b.y = lot.single_obj.lot_y;

dist = Distance(p_a, p_b);
ext_index = (LENGTHOFPATH / (1 + dist));

for i = 1 : 1 : LENGTHOFPATH - ext_index
    path.x(i) = (p_b.x + (LENGTHOFPATH - ext_index - i) / (LENGTHOFPATH - ext_index) * dist * cos(lot_theta));
    path.y(i) = SetY(p_b.y + (LENGTHOFPATH - ext_index - i) /  (LENGTHOFPATH - ext_index) * dist * sin(lot_theta));
end

for i = 1 : 1 : LENGTHOFPATH - ext_index
    path.x(i) = (p_b.x - (i - LENGTHOFPATH + ext_index) / ext_index * cos(lot_theta));
    path.y(i) = (p_b.y - (i - LENGTHOFPATH + ext_index) / ext_index * sin(lot_theta));
end

% x1 = point_a.x;
% x2 = point_b.x;
% x3 = point_origin.x;
% y1 = point_a.y;
% y2 = point_b.y;
% y3 = point_origin.y;

function [distance] = DistanceFromPointToLine(x1, x2, x3 , y1, y2, y3)
    temp_distance = power(y2 - y1, 2) + power(x2 - x1, 2);
    project_x = ((y2 - y1) * (x1 * y2 - x2 * y1) + power(x2 - x1, 2) * x3 + (x2 - x1) * (y2 - y1) * y3) / temp_distance;
    project_y = ((x2 - x1) * (x2 * y1 - x1 * y2) + power(y2 - y1, 2) * y3 + (x2 - x1) * (y2 - y1) * x3) / temp_distance;
    distance = sqrt(power(project_x - x3, 2) + power(project_y - y3, 2));
end

function [distance] = Distance(x1, y1, x2, y2)
    distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
end

%https://blog.csdn.net/LuckilyHaveYou/article/details/105974743 使用内积公式计算夹角 外积公式判断方向
function [value] = CrossProd(x1,y1, x2,y2, x3,y3)
    deltax1 = x2 - x1;
    deltay1 = y2 - y1;

    deltax2 = x3 - x1;
    deltay2 = y3 - y1;

    value = deltax1 * deltay2 - deltax2 * deltay1;
end
