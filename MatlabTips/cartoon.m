%取0~pi之间的正弦曲线做燕子的翅膀
%0~pi/2之间的曲线当做右翅膀
%pi/2~pi之间的曲线当做左翅膀
clear all
clc
x1 = [ 0:0.01:1/2 ] * pi;%右侧翅膀横坐标
y1 = sin( x1 );          %右侧翅膀纵坐标
x2 = [ 1/2:0.001:1 ] * pi;%左侧翅膀横坐标
y2 = sin( x2 );           %左侧翅膀纵坐标
p1 = plot( (x1+pi)/2, (y1+3)/2, 'k' );%右翅膀在右侧，所以需要“+pi”
hold on
p2 = plot( x2/2, (y2+3)/2, 'k' );
axis( [ -8, 10, 0, 10 ] ) %规划处矩形区域
 
p3 = plot( (x1+pi)/2+2, (y1+3)/3 + 3, 'k' );
p4 = plot( x2/2+2, (y2+3)/3 + 3 , 'k' );
 
p5 = plot( (x1+pi)/3-2, (y1+3)/3 + 1, 'k' );
p6 = plot( x2/3-2, (y2+3)/3 + 1, 'k' );
 
%给矩形区域添加背景色
axis( [ -8, 10, 0, 10 ] )
%set( gcf, 'doublebuffer', 'on');
set( gca, 'color', [ 1, 1, 0.9 ] );%gca表示当前图形区域
 
%绘制红太阳
t = (0:0.1:2) * pi;
x = 0.5 * cos(t) + 8;
y = 0.5 * sin(t) + 9;
fill( x, y, 'r' ) 
axis equal
axis( [ -8, 10, 0, 10 ] )
%绘制两座高山
xh = [ -8 : 0.2 : 8 ];
yh1 = 2 * exp( -(xh + 5).^2 / 2 );
fill( xh, yh1, 'b' )
hold on
yh2 = 1.5 * exp( -xh.^2 / 4 );
area( xh, yh2, 'FaceColor', [ 0.1, 0.1, 0.9 ] );
 
%运动路线
path_x = [-2 : 0.01 : 2] *pi;%横坐标
path_y1 = sin( path_x );        %第一只小燕子的飞行路线
path_y2 = cos( path_x );        %第二只小燕子的飞行路线
path_y3 = cos( fliplr(path_x) );%第三只小燕子的飞行路线
set( gcf, 'doublebuffer', 'on');
hight = 2;%设定小燕子的初始高度
period = 5; %运动周期
k = 0;
len = length( path_x );
while k < period
    for i = 1 : len
        set( p1, 'Xdata', path_x(i) +(x1+pi)/2, 'Ydata', path_y1(i)+2  + (y1+3)/2 + hight );
        set( p2, 'Xdata', path_x(i) + x2/2, 'Ydata', path_y1(i) + 2 + (y2+3)/2 + hight );
        set( p3, 'Xdata', path_x(i)-2 + (x1+pi)/2, 'Ydata', path_y2(i)+2  + (y1+3)/3 + hight );
        set( p4, 'Xdata', path_x(i)-2 + x2/2, 'Ydata', path_y2(i) + 2 + (y2+3)/3 + hight );
        set( p5, 'Xdata', path_x(len-i+1) + (x1+pi)/3, 'Ydata', path_y3(i) + 2  + (y1+3)/3 + hight );
        set( p6, 'Xdata', path_x(len-i+1) + x2/3, 'Ydata', path_y3(i) + 2 + (y2+3)/3 + hight );
        pause(0.02);
    end
    path_x = fliplr( path_x );%逆向返回飞行
    k = k + 1;
end

