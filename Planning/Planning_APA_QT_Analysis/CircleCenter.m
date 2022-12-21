clear;
clc;

Line = struct("x", 8, "y", 3, "angle", 0);
CircleLeft = struct("x", -0.5, "y", 3, "radius", 4.6614);
CircleRight = struct("x", 1, "y", 1, "radius", 4.7079);

[CircleRight.x CircleRight.y] = Tangent_CCL(Line, CircleLeft, CircleRight);

% 1.1  rectangle(‘Position’,[x,y,w,h])，其中以x，y为起始坐标开始，画出长为w,宽为h的矩形。
% 1.2  rectangle(…,‘Curvature’,[a,b])指定矩阵边的曲率，可以使它从矩形到椭圆不同变化，水平曲率x为矩形宽度的分数，是沿着矩形的顶部和底部的边进行弯曲。
% a和b取值范围是从0（无曲率）到1（最大曲率）。在画圆时就可以将这里的曲率，也就是a和b设都为1，矩形就变成了圆。
% 注意：rectangle绘制一个矩形，其默认位置是[0,0,1,1] ，默认曲率是 [0,0]（也就是说，没有曲率）。
% 原文链接：https://blog.csdn.net/qq_40505953/article/details/104778359
% 例子：
% r = 5;%半径
% a = 0;%横坐标
% b = 2;%纵坐标
% para = [a-r, b-r, 2*r, 2*r];
% rectangle('Position', para, 'Curvature', [1 1]);
plot(Line.x, Line.y, 'ro', 'lineWidth', 3);
line([Line.x, 0], [Line.y,Line.y], 'lineWidth', 2);

paraLeft = [CircleLeft.x - CircleLeft.radius, CircleLeft.y-CircleLeft.radius, 2*CircleLeft.radius, 2*CircleLeft.radius];
rectangle('Position', paraLeft, 'Curvature', [1 1]);

paraRight = [CircleRight.x - CircleRight.radius, CircleRight.y-CircleRight.radius, 2*CircleRight.radius, 2*CircleRight.radius];
rectangle('Position', paraRight, 'Curvature', [1 1]);

crline.x = CircleRight.x;
crline.y = CircleRight.y;
crline.angle = Line.angle - pi / 4;
CircleRight_move.x = CircleRight.x + 0.1;
CircleRight_move.y = LinearAlgebra(crline, CircleRight.x);
CircleRight_move.radius = 4.7079;

paraRight_move = [CircleRight_move.x - CircleRight_move.radius, CircleRight_move.y-CircleRight_move.radius, 2*CircleRight_move.radius, 2*CircleRight_move.radius];
rectangle('Position', paraRight_move, 'Curvature', [1 1]);

function [x,y] = Tangent_CCL(l,cl,cr)

	sec_v = 1/cos(l.angle);
	tan_v = tan(l.angle);

	Value_temp = l.y - cl.y - tan_v*l.x - sec_v*cr.radius;

	a = 1 + tan_v * tan_v;
	b = 2*(tan_v * Value_temp - cl.x);
	c = power(Value_temp,2) - power(cl.radius + cr.radius ,2);

    x = (QuadraticEquation(a,b,c));

    y = LinearAlgebra(l,cr.x) - sec_v*cr.radius;
end

function [x] = QuadraticEquation(a,b,c)
	x = 0.5 * (-b + sqrt(b*b - 4*a*c)) / a;
end

function [y] = LinearAlgebra(l,x)
	y = tan(l.angle)*(x - l.x) + l.y;
end

