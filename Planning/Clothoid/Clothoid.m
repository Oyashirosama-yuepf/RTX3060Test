clear;
clc;

%% 调用 clothoid函数，并将终点位置的曲率半径设置为 0.1:0.2:3
sk = 1; %% 曲线长
clothoid(0.1,sk)

%%%% 计算回旋曲线，并绘图
function [] = clothoid(Rmin,sk)

N = 100; %% 
c = 1 / Rmin / sk; %% 曲率变化率 a = dk/dl = 1/A^2, LR = A^2 = 1/a, 初始曲率-末尾曲率 / 总长度
x = zeros(1,N);
y = zeros(1,N);

dx = 0;
dy = 0;
for sk_i = sk / N : sk / N : sk   %离散化处理
    result_x = 0; %% 初始化x坐标点的值
    result_y = 0; %% 初始化y坐标点的值
    
    %方案1 按照原始定义计算
    beta = sk_i^2 / (2 * Rmin * sk);
    dx = dx + sk/N * cos(beta);
    dy = dy + sk/N * sin(beta);
    x(int32(sk_i / sk * N)) = dx;
    y(int32(sk_i / sk * N)) = dy;
    
    %方案2 按照幂级数展开累加方式计算
    for i = 0 : 100 %% 计算x   考虑计算机的计算能力和准确性，100比较合适
        result_x = result_x + ((-1) ^ i) * (c ^ (2 * i)) * (sk_i ^ (4 * i + 1)) / ((2 ^ (2 * i)) * (4 * i + 1) * fctorial(2 * i));
    end    
  
    for i = 0 : 100 %% 计算y
        result_y = result_y + ((-1) ^ i) * (c ^ (2 * i + 1)) * (sk_i ^ (4 * i + 3)) / ((2 ^ (2 * i + 1)) * (4 * i + 3) * fctorial(2 * i + 1));
        disp(result_y);
    end
    x2(int32(sk_i / sk * N)) = result_x;
    y2(int32(sk_i / sk * N)) = result_y;
    %方案3 按照级数展开累加式取前几项的方式计算，结果不准确，具体需要保留多少项不清楚，测试发现最小曲率半径（终点处）越小，越不准确
%     result_x = sk_i - sk_i^5 / (40 * (1/c/sk_i)^2 * sk^2) + sk_i^9 / (3456 * (1/c/sk_i)^4 * sk^4);  
%     result_y = sk_i^3 / (6*(1/c/sk_i)*sk) - sk_i^7 / (336 * (1/c/sk_i)^3 * sk^3); 
%     x(int32(sk_i / sk * N)) = result_x;
%     y(int32(sk_i / sk * N)) = result_y;
    
end

hold on;
plot(x,y);
hold on;
plot(x2,y2);
plot(x(end),y(end),'*'); %%回旋曲线的最后一个点
axis equal;
end

%% 阶乘函数
function y = fctorial(x)    %阶数不可以过高，否则对于计算机会无法计算

n = 1;
for i = 1 : x
    n = n * i;
end

y = n ;
end
