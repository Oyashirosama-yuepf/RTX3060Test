clc
clear all
Kp = 1.0 ; 
dt = 0.1  ;% [s]
L = 2.9 ;% [m] wheel base of vehicle
Q = eye(4);
R = eye(1);
max_steer =60 * pi/180; % in rad
target_speed = 15.0 / 3.6;

cx = 0:0.1:200; % sampling interception from 0 to 100, with step 0.1
for i = 1:500   % here we create a original reference line, which the vehicle should always follow when there is no obstacles;
    cy(i) = -sin(cx(i)/20)*cx(i)/2;
end
for i = 501: length(cx)
    cy(i) = -sin(cx(i)/20)*cx(i)/2; %cy(500);
end

p = [cx', cy'];
 for i = 1:length(cx)-1
 pd(i) = (p(i+1,2)-p(i,2))/(p(i+1,1)-p(i,1));
 end
 pd(end+1) = pd(end);
  %计算一阶导数
 for i =2: length(cx)-1
     pdd(i) = (p(i+1,2)-2*p(i,2) + p(i-1,2))/(0.5*(-p(i-1,1)+p(i+1,1)))^2;
 end
      pdd(1) = pdd(2);
     pdd(length(cx)) = pdd(length(cx)-1);
     
  for i  = 1:length(cx)
     k(i) = (pdd(i))/(1+pd(i)^2)^(1.5);
  end
  
  cx= cx'
  cy =cy'
  cyaw = atan(pd');
 
  ck = k'
%   plot(1:1001, cyaw)
%   plot(1:1001, ck)
%   plot(1:1001, pd)
pe = 0; pth_e = 0;
i = 1;
target_v = 50/3.6;
T = 80;
lastIndex = length(cx);
x = 0; y = -1; yaw = 0; v = 0;
time = 0;
ind =0;
figure

while ind < length(cx)
   
    [delta,ind,e,th_e] =  lqr_steering_control(x,y,v,yaw,cx,cy,cyaw,ck, pe, pth_e,L,Q,R,dt);
    pe =e;
    pth_e = th_e;
    if abs(e)> 4
        fprintf('mayday mayday!\n')
        break;
    end
    delta
    a = PIDcontrol(target_v, v, Kp);
     [x,y,yaw,v] = update(x,y,yaw,v, a, delta, dt,L, max_steer);
     posx(i) = x;
     posy(i)  =y;
     i = i+1;
     plot(cx,cy,'r-')
     hold on
     plot(posx(i-1),posy(i-1),'bo')
      drawnow
     
      hold on
end

% function"Update" updates vehicle states
function [x, y, yaw, v] = update(x, y, yaw, v, a, delta,dt,L,max_steer)
 delta = max(min(max_steer, delta), -max_steer);
    x = x + v * cos(yaw) * dt;
    y = y + v * sin(yaw) * dt;
    yaw = yaw + v / L * tan(delta) * dt;
   v = v + a * dt;
end

function [a] = PIDcontrol(target_v, current_v, Kp)
a = Kp * (target_v - current_v);
end

function [angle] = pipi(angle) % the unit of angle is in rad;

if (angle > pi)
    angle =  angle - 2*pi;
elseif (angle < -pi)
    angle = angle + 2*pi;
else
    angle = angle;
end
end

function [Xn] = solve_DARE(A,B,Q,R)
X = Q;
maxiter = 150;
epsilon = 0.01;
for i = 1:maxiter
    Xn = A' * X * A - A' * X * B * ((R + B' * X * B) \ B') * X * A +Q;
    if abs(Xn - X) <= epsilon
        X = Xn;
        break;
    end
    X = Xn;
end
end

function [K] = dlqr (A,B,Q,R)
X = solve_DARE(A,B,Q,R);
K = (B' * X * B + R) \ (B' * X * A);
end

function [delta,ind,e,th_e] =  lqr_steering_control(x,y,v,yaw,cx,cy,cyaw,ck, pe, pth_e,L,Q,R,dt)
[ind, e] = calc_target_index(x,y,cx,cy,cyaw);
k =ck(ind);
th_e = pipi(yaw -cyaw(ind));
A = zeros(4,4);

A(1,1) = 1; A(1,2) = dt; A(2,3) = v; A(3,3) = 1; A(3,4) = dt;
B= zeros(4,1);
B(4,1) = v/L;
K = dlqr(A,B,Q,R);
x = zeros(4,1);
x(1,1)=e; x(2,1)= (e-pe)/dt; x(3,1) = th_e; x(4,1) = (th_e - pth_e)/dt;
ff = atan(L * (k));
fb = pipi(-K * x);
delta =   1*ff + 1*fb;
ff
fb
end

function [ind, error] = calc_target_index(x,y, cx,cy,cyaw)
N =  length(cx);
Distance = zeros(N,1);
for i = 1:N
Distance(i) =  sqrt((cx(i)-x)^2 + (cy(i)-y)^2);
end
[value, location]= min(Distance);
ind = location

dx1 = cx(ind)- x;
dy1 = cy(ind) -y;
angle = pipi(cyaw(ind)-atan(dy1/dx1));
heading = cyaw(ind)*180/pi
    if y<cy(ind) 
        error = -value;
    else
        error = value;
    end

end

% if cx(ind)> x
%     error = -value;
% else
% error = value;
% end



