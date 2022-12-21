function cornuspiral(b)     %此程序用来绘制[-b,b]上的考纽螺线，需要调用函数romberg（或函数comp_simpson1,comp_simpson2)
tic
if nargin<1
    b=5;
end
if b>10
    fprintf('b>10时，程序可能会运行较长时间！！\n');
end
a=1;

s=a:0.1:b;                %由于考纽螺线是对称的，因此，我们只需画出区间[0,b]上的图像即可
[m,n]=size(s);
x=zeros(1,n);                %初始化向量x(s),y(s)
y=zeros(1,n);

% f=@(x)cos(x.^2/2);           %菲涅尔积分的被积函数
% g=@(x)sin(x.^2/2);

% for k=1:n
%     x(k)=romberg(f,0,s(k),1e-3);       %利用龙贝格方法计算菲涅尔积分的近似值，误差限取1e-3
%     y(k)=romberg(g,0,s(k),1e-3);
%     
% %     x(k)=romberg1(0,s(k),1e-3);
% %     y(k)=romberg2(0,s(k),1e-3);
% 
% end
% subplot(1,2,1);
% plot(x,y,'g');                      %画出考纽螺线区间[0,b]上的图像
% hold on
% plot(-x,-y,'g');                    %利用对称性，画出[-b,0]上的图像
% hold on
% text(-1,1,'green--ep=1e-3');
% title('cornuspiral');
% 
%  for k=1:n
%     x(k)=romberg(f,0,s(k),1e-7);       %利用龙贝格方法计算菲涅尔积分的近似值，误差限取1e-7
%     y(k)=romberg(g,0,s(k),1e-7);
%     
% %     x(k)=romberg1(0,s(k),1e-7);
% %     y(k)=romberg2(0,s(k),1e-7);
%     
%  end
%  subplot(1,2,2);
%  plot(x,y,'r');                      %画出考纽螺线区间[0,b]上的图像
%  hold on
%  plot(-x,-y,'r');                    %利用对称性，画出[-b,0]上的图像
%  hold on
%  text(-1,0.8,'red--ep=1e-7');
%  title('cornuspiral');
 
 for k=1:n   
    x(k)=comp_simpson1(s(1),s(k),20*b);     %利用复化simpson求积公式计算菲涅尔积分的近似值，取20*b+1个等分节点
    y(k)=comp_simpson2(s(1),s(k),20*b);
 end
% subplot(1,2,1);
plot(x,y,'k', 'linewidth',3);                      %画出考纽螺线区间[0,b]上的图像
hold on
% plot(-x,-y,'y');                    %利用对称性，画出[-b,0]上的图像
% hold on

%  for k=1:n 
%     x(k)=comp_simpson1(0,s(k),40*b);         %利用复化simpson求积公式计算菲涅尔积分的近似值，取40*b+1个等分节点
%     y(k)=comp_simpson2(0,s(k),40*b);
%  end
%  subplot(1,2,2);
%  plot(x,y,'b');                      %画出考纽螺线区间[0,b]上的图像
%  hold on
%  plot(-x,-y,'b');                    %利用对称性，画出[-b,0]上的图像
%  hold on

 toc
end