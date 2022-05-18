function  lujingyouhua_1(L,N,M,a,b,p,Q, q1)
% L 地形图为01矩阵，如果为0表示机器人能通过，如果为1表示障碍物，机器人不能通过
% N 迭代的次数
% M 蚁群中蚂蚁的个数
% a 表示信息启发式因子，反映了蚁群在运动过程中所残留的信息量的相对重要程度
% b 表示期望启发式因子，反映了期望值的相对重要程度
% p 表示信息素挥发系数
% Q 常量，表示蚂蚁循环一周或一个过程在经过的路径上所释放的信息素总量
%q1是（0,1）间的一个算法参量，在状态转移时作为一个判断基准 
M1=size(L,1); 
Set=1;	 % Set 为地图中路径起始点位置
En=M1*M1;        % En为地图中终止点位置    
H= route_distance (L); %通过调用子函数route_distance.m，产生地图中方格的邻接矩阵H用此矩
%阵存储蚂蚁可以先后通过的两个方格的位置及距离，这两个方格都是无障碍方格并且处于相
%邻或对角位置。H矩阵是蚂蚁机器人移动的根据。
K=size(H,1);	%K表示问题的规模，也表示L地图上的方格总数
t1=ones(K,K); % t1 初始信息素矩阵，
t1=9.*t1;  %将每条路径上的信息素数设为常数9；
d_t1=zeros(K,K);% d_t1 信息素增量矩阵
aa=1;	%aa方格的边长
Enx=M1-0.5;	 %Enx 终止点的横坐标
Eny=0.5;	%终止点纵坐标
y1=zeros(K);	%启发式信息矩阵，表示蚂蚁在方格间转移的期望程度
%%下面构造启发式信息矩阵,每个节点的启发式信息素数量取为至目标点（在此为终止点）的
%直线距离的倒数
for i=1:K
ix=aa*(mod(i,M1)-0.5); 
 if ix==-0.5  %当i等于M1的整数倍时，ix=-0.5，即每一行的最后一个方格
 ix=M1-0.5; 
 end 
iy=aa*(M1+0.5-ceil(i/M1));  
   if i~=En 
   y1(i)=1/((ix-Enx)^2+(iy-Eny)^2)^0.5; 	%构造启发式信息矩阵
   else 
   y1(i)=100; 
   end 
end 
Rs=cell(N,M);		%用细胞结构存储每一代的每一只蚂蚁的爬行路线
Pr=zeros(N,M);	%用矩阵存储每一代的每一只蚂蚁的爬行路线长度
kn=inf; k2=0; n2=0;	%初始化过程参数

%N轮蚂蚁觅食开始，每轮派出的蚂蚁数为M
for k=1:N 
for m=1:M 
%% 第一步：初始化参数
S1=Set;	%当前节点初始化为起始点
rt_1=Set;		%rt_1存储当前蚂蚁的爬行路线
rd=0;	%rd 爬行路线长度
tabuk=ones(K);	%初始化禁忌表
tabuk(Set)=0;	%排除起始点
H1=H;	%邻接矩阵初始化
%% 第二步：搜寻蚂蚁下一步可以前往的方格
H2=H1(S1,:); % H2为H1矩阵的第一行，表示L矩阵第S1个元素（按行排列）与其他元素的
%连通关系 
H3=find(H2); %返回H2中不为零元素的序号，按顺序排列
for j=1:length(H3) 
  if tabuk(H3(j))==0 
  H2(H3(j))=0; 
end 
end 
L1=find(H2); 
Len_L1=length(L1);%可选节点的个数
while S1~=En&&Len_L1>=1 	% 觅食停止条件：蚂蚁到终点或者陷入死胡同
%% 第三步：确定蚂蚁下一步将要转移的位置
q=rand;
if q<=q1
t12=zeros(1,K);
for i=1:Len_L1
t12(i)= (t1(S1,L1(i))^a)*((y1(L1(i)))^b);
end
m_t12=max(t12);
select=find(t12>=m_t12);
to_visit=L1(select(1));
else
P1=zeros(Len_L1);  %初始化状态转移概率矩阵
for i=1:Len_L1 
  P1(i)=(t1(S1,L1(i))^a)*((y1(L1(i)))^b); 
end 
sump1=sum(P1); 
P1=P1/sump1;%计算状态转移概率
%%利用轮盘赌方式选择蚂蚁下一步要去的位置
P2(1)=P1(1); 
for i=2:Len_L1
  P2(i)=P2(i-1)+P1(i); 
end 
Select1=find(P2>=rand); 
to_visit=L1 (Select1(1)); 
end
%% 第四步：更新状态并做有关记录
rt_1=[rt_1,to_visit];%路径增加
rd=rd+H1(S1,to_visit);%路径长度增加
S1=to_visit;%蚂蚁移到下一个节点位置
for k12=1:K 
  if tabuk(k12)==0 
   H1(S1,k12)=0; 
   H1(k12,S1)=0; 
  end 
end 
tabuk(S1)=0;%已访问过的节点从禁忌表中删除
H2=H1(S1,:); 
H3=find(H2); 
for j=1:length(H3) 
 if tabuk(H3(j))==0 
  H2(j)=0; 
 end 
end 
L1=find(H2); 
Len_L1=length(L1);%可选节点的个数
end 
%% 第五步：记录蚂蚁的爬行路线并且记录搜索到本轮最短路径的蚂蚁及路径长度
Rs{k,m}=rt_1;	%存储第k轮第m个蚂蚁的路线 
if rt_1(end)==En 
   Pr(k,m)=rd; 
   if rd<kn 
   k2=k;
n2=m;
kn=rd; 
   end 
   else 
      Pr(k,m)=0; 
   end 
end 
%% 第六步：执行全局更新

d_t1=zeros(K,K);
for m=1:M 
 if Pr(k,m)  
   Rt=Rs{k,m}; 
   TS=length(Rt)-1;	 
   PL_d=Pr(k,m); 
   for s=1:TS 
   x=Rt(s); 
   y=Rt(s+1); 
   d_t1(x,y)=d_t1(x,y)+Q/PL_d; 
   d_t1(y,x)=d_t1(y,x)+Q/PL_d; 
   end 
 end 
end 
t1=(1-p).*t1+d_t1;%信息素挥发一部分，新增加一部分
end 
%%绘图
%绘制机器人寻优路径收敛曲线
minrt=zeros(N);
rt11=zeros(1,M); 
for i=1:N
rt11=Pr(i,:); 
Nzero=find(rt11); 
 rt12=rt11(Nzero); 
 minrt(i)=min(rt12); 
end 
figure(1) 
plot(minrt); 
hold on 
grid on 
title('机器人寻优路径收敛曲线'); 
xlabel('迭代的次数'); 
ylabel('蚂蚁搜寻路径长度'); 
%绘蚂蚁爬行图
figure(2) 
axis([0,M1,0,M1]) 
for i=1:M1
for j=1:M1 
if L(i,j)==1 
x1=j-1;y1=M1-i;   x2=j;y2=M1-i; 
x3=j;y3=M1-i+1;   x4=j-1;y4=M1-i+1; 
fill([x1,x2,x3,x4],[y1,y2,y3,y4],[0.2,0.2,0.2]); 
hold on 
else 
x1=j-1;y1=M1-i;  x2=j;y2=M1-i; 
x3=j;y3=M1-i+1;  x4=j-1;y4=M1-i+1; 
fill([x1,x2,x3,x4],[y1,y2,y3,y4],[1,1,1]); 
hold on 
end 
end 
end 
hold on 
Rt=Rs{k2,n2};
LEN_Rt=length(Rt); 
Rx=Rt; 
Ry=Rt; 
for ik=1:LEN_Rt 
Rx(ik)=aa*(mod(Rt(ik),M1)-0.5); 
if Rx(ik)==-0.5 
Rx(ik)=M1-0.5; 
end 
Ry(ik)=aa*(M1+0.5-ceil(Rt(ik)/M1)); 
end 
plot(Rx,Ry) 
end
%% route_distance.m子函数
%下面的子函数产生表示蚂蚁可先后通过的两方格及其距离的矩阵H，在H矩阵中元素行下标
%代表任意先后两节点第一个节点在L中位置，列下标代表第二个节点在L中的位置，若这两
%个节点为蚂蚁可先后通过则元素值为这两个无障碍节点之间的距离，否则元素值0。
%，蚂蚁可先后通过的两方格为L地形图中两个无障碍方格并且这两个方格处于相邻或对
%角位置。通过对矩阵L两次嵌套的搜索遍历，寻找两个相邻或者对角的无障碍方格的所有可
%能并计算蚂蚁通过它们的距离，在这里若两无障碍方格相邻，则距离设为1，相应的若两无障
%碍方格对角，则距离为2^0.5≈1.4142。
function H=route_distance(L) 
h=size(L,1); 	
H=zeros(h*h,h*h); 
%用i表示H矩阵的行下标，j表示H矩阵的列下标，这是第一个嵌套循环的外部循环 
%用m表示L矩阵的行下标，n表示L矩阵的列下标，这是嵌套循环的内循环
for i=1:h	 
for j=1:h
if L(i,j)==0 
for m=1:h 
for n=1:h 
if L(m,n)==0 
im=abs(i-m);jn=abs(j-n); 	%分别计算在L矩阵搜寻到的两个零元素即L地图中的两个无
%障碍方格在L地图中x方向距离和y方向距离
if im+jn==1||(im==1&&jn==1) 
H((i-1)*h+j,(m-1)*h+n)=(im^2+jn^2)^0.5; 
%用矩阵H中部分元素存储两相邻或对角的无障碍方格在L地图中位置和路径距
%离，其他元素值为0
end 
end 
end 
end 
end 
end 
end 
end
