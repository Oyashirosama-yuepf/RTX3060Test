clear;
clc;

%% 调用 clothoid函数，并将终点位置的曲率半径设置为 0.1:0.2:3

sk_min = 1*sqrt(10^2 + 5^2);   % 理论最短距离 走直线
plot(3,2,'ks'); %%回旋曲线的最后一个点
line([0,9.7],[0,4.8]);

for sk = 1 * sk_min : 0.1 : 1.2 * sk_min
    for Rmin = 1 : 0.1 : 10
        [x_end, y_end, beta_end] = clothoid(Rmin,sk);
        if ((abs(x_end - 3) <= 0.3) && (abs(y_end - 2) <= 0.3)) % && (abs(beta_end - 40) <= 40))
            disp("planning success");
            break;
        end
    end
end

disp("planning stop");

%%%% 计算回旋曲线，并绘图
function [x_end, y_end, beta_end] = clothoid(Rmin,sk)

sk_i_s = 0.01;   % 步长标准 
N = fix(sk / sk_i_s); %% 
x = zeros(1,N);
y = zeros(1,N);

dx = 0;
dy = 0;
for sk_i = sk / N : sk / N : sk   %离散化处理
    beta0 = 0;
    Rmin = Rmin;% + 1 * rand() - 1 * rand();
    c = 1 / Rmin / sk; %% 曲率变化率 a = dk/dl = 1/A^2, LR = A^2 = 1/a, 初始曲率-末尾曲率 / 总长度
    beta = sk_i^2 / (2 * Rmin * sk) + beta0;
    dx_pre = dx;
    dy_pre = dy;
    dx = dx + sk/N * cos(beta);
    disp(dx);
    dy = dy + sk/N * sin(beta);
    disp(dy);
    AangleTan = (dy - dy_pre) / (dx - dx_pre);
    x(int32(sk_i / sk * N)) = dx;
    y(int32(sk_i / sk * N)) = dy;    
   arraybeta(int32(sk_i / sk * N)) = abs(atan(AangleTan) / pi * 180);
end
x_end = dx;
y_end = dy;
beta_end = 0;%abs(atan(AangleTan) / pi * 180);

figure(1);
hold on;
plot(x,y);
hold on;
plot(x(end),y(end),'*'); %%回旋曲线的最后一个点
axis equal;

% r = Rmin;%半径
% a = 0;%圆心横坐标
% b = Rmin;%圆心纵坐标
% theta = -pi/2:pi/20:0; %角度[0,2*pi] 
% x = a+r*cos(theta);
% y = b+r*sin(theta);
% plot(x,y,'r--')
% axis equal


end

%% 阶乘函数
function y = fctorial(x)    %阶数不可以过高，否则对于计算机会无法计算

n = 1;
for i = 1 : x
    n = n * i;
end

y = n ;
end

