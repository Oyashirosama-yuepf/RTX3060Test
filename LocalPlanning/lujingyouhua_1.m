function  lujingyouhua_1(L,N,M,a,b,p,Q, q1)
% L ����ͼΪ01�������Ϊ0��ʾ��������ͨ�������Ϊ1��ʾ�ϰ�������˲���ͨ��
% N �����Ĵ���
% M ��Ⱥ�����ϵĸ���
% a ��ʾ��Ϣ����ʽ���ӣ���ӳ����Ⱥ���˶�����������������Ϣ���������Ҫ�̶�
% b ��ʾ��������ʽ���ӣ���ӳ������ֵ�������Ҫ�̶�
% p ��ʾ��Ϣ�ػӷ�ϵ��
% Q ��������ʾ����ѭ��һ�ܻ�һ�������ھ�����·�������ͷŵ���Ϣ������
%q1�ǣ�0,1�����һ���㷨��������״̬ת��ʱ��Ϊһ���жϻ�׼ 
M1=size(L,1); 
Set=1;	 % Set Ϊ��ͼ��·����ʼ��λ��
En=M1*M1;        % EnΪ��ͼ����ֹ��λ��    
H= route_distance (L); %ͨ�������Ӻ���route_distance.m��������ͼ�з�����ڽӾ���H�ô˾�
%��洢���Ͽ����Ⱥ�ͨ�������������λ�ü����룬���������������ϰ������Ҵ�����
%�ڻ�Խ�λ�á�H���������ϻ������ƶ��ĸ��ݡ�
K=size(H,1);	%K��ʾ����Ĺ�ģ��Ҳ��ʾL��ͼ�ϵķ�������
t1=ones(K,K); % t1 ��ʼ��Ϣ�ؾ���
t1=9.*t1;  %��ÿ��·���ϵ���Ϣ������Ϊ����9��
d_t1=zeros(K,K);% d_t1 ��Ϣ����������
aa=1;	%aa����ı߳�
Enx=M1-0.5;	 %Enx ��ֹ��ĺ�����
Eny=0.5;	%��ֹ��������
y1=zeros(K);	%����ʽ��Ϣ���󣬱�ʾ�����ڷ����ת�Ƶ������̶�
%%���湹������ʽ��Ϣ����,ÿ���ڵ������ʽ��Ϣ������ȡΪ��Ŀ��㣨�ڴ�Ϊ��ֹ�㣩��
%ֱ�߾���ĵ���
for i=1:K
ix=aa*(mod(i,M1)-0.5); 
 if ix==-0.5  %��i����M1��������ʱ��ix=-0.5����ÿһ�е����һ������
 ix=M1-0.5; 
 end 
iy=aa*(M1+0.5-ceil(i/M1));  
   if i~=En 
   y1(i)=1/((ix-Enx)^2+(iy-Eny)^2)^0.5; 	%��������ʽ��Ϣ����
   else 
   y1(i)=100; 
   end 
end 
Rs=cell(N,M);		%��ϸ���ṹ�洢ÿһ����ÿһֻ���ϵ�����·��
Pr=zeros(N,M);	%�þ���洢ÿһ����ÿһֻ���ϵ�����·�߳���
kn=inf; k2=0; n2=0;	%��ʼ�����̲���

%N��������ʳ��ʼ��ÿ���ɳ���������ΪM
for k=1:N 
for m=1:M 
%% ��һ������ʼ������
S1=Set;	%��ǰ�ڵ��ʼ��Ϊ��ʼ��
rt_1=Set;		%rt_1�洢��ǰ���ϵ�����·��
rd=0;	%rd ����·�߳���
tabuk=ones(K);	%��ʼ�����ɱ�
tabuk(Set)=0;	%�ų���ʼ��
H1=H;	%�ڽӾ����ʼ��
%% �ڶ�������Ѱ������һ������ǰ���ķ���
H2=H1(S1,:); % H2ΪH1����ĵ�һ�У���ʾL�����S1��Ԫ�أ��������У�������Ԫ�ص�
%��ͨ��ϵ 
H3=find(H2); %����H2�в�Ϊ��Ԫ�ص���ţ���˳������
for j=1:length(H3) 
  if tabuk(H3(j))==0 
  H2(H3(j))=0; 
end 
end 
L1=find(H2); 
Len_L1=length(L1);%��ѡ�ڵ�ĸ���
while S1~=En&&Len_L1>=1 	% ��ʳֹͣ���������ϵ��յ������������ͬ
%% ��������ȷ��������һ����Ҫת�Ƶ�λ��
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
P1=zeros(Len_L1);  %��ʼ��״̬ת�Ƹ��ʾ���
for i=1:Len_L1 
  P1(i)=(t1(S1,L1(i))^a)*((y1(L1(i)))^b); 
end 
sump1=sum(P1); 
P1=P1/sump1;%����״̬ת�Ƹ���
%%�������̶ķ�ʽѡ��������һ��Ҫȥ��λ��
P2(1)=P1(1); 
for i=2:Len_L1
  P2(i)=P2(i-1)+P1(i); 
end 
Select1=find(P2>=rand); 
to_visit=L1 (Select1(1)); 
end
%% ���Ĳ�������״̬�����йؼ�¼
rt_1=[rt_1,to_visit];%·������
rd=rd+H1(S1,to_visit);%·����������
S1=to_visit;%�����Ƶ���һ���ڵ�λ��
for k12=1:K 
  if tabuk(k12)==0 
   H1(S1,k12)=0; 
   H1(k12,S1)=0; 
  end 
end 
tabuk(S1)=0;%�ѷ��ʹ��Ľڵ�ӽ��ɱ���ɾ��
H2=H1(S1,:); 
H3=find(H2); 
for j=1:length(H3) 
 if tabuk(H3(j))==0 
  H2(j)=0; 
 end 
end 
L1=find(H2); 
Len_L1=length(L1);%��ѡ�ڵ�ĸ���
end 
%% ���岽����¼���ϵ�����·�߲��Ҽ�¼�������������·�������ϼ�·������
Rs{k,m}=rt_1;	%�洢��k�ֵ�m�����ϵ�·�� 
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
%% ��������ִ��ȫ�ָ���

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
t1=(1-p).*t1+d_t1;%��Ϣ�ػӷ�һ���֣�������һ����
end 
%%��ͼ
%���ƻ�����Ѱ��·����������
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
title('������Ѱ��·����������'); 
xlabel('�����Ĵ���'); 
ylabel('������Ѱ·������'); 
%����������ͼ
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
%% route_distance.m�Ӻ���
%������Ӻ���������ʾ���Ͽ��Ⱥ�ͨ���������������ľ���H����H������Ԫ�����±�
%���������Ⱥ����ڵ��һ���ڵ���L��λ�ã����±�����ڶ����ڵ���L�е�λ�ã�������
%���ڵ�Ϊ���Ͽ��Ⱥ�ͨ����Ԫ��ֵΪ���������ϰ��ڵ�֮��ľ��룬����Ԫ��ֵ0��
%�����Ͽ��Ⱥ�ͨ����������ΪL����ͼ���������ϰ����������������������ڻ��
%��λ�á�ͨ���Ծ���L����Ƕ�׵�����������Ѱ���������ڻ��߶Խǵ����ϰ���������п�
%�ܲ���������ͨ�����ǵľ��룬�������������ϰ��������ڣ��������Ϊ1����Ӧ����������
%������Խǣ������Ϊ2^0.5��1.4142��
function H=route_distance(L) 
h=size(L,1); 	
H=zeros(h*h,h*h); 
%��i��ʾH��������±꣬j��ʾH��������±꣬���ǵ�һ��Ƕ��ѭ�����ⲿѭ�� 
%��m��ʾL��������±꣬n��ʾL��������±꣬����Ƕ��ѭ������ѭ��
for i=1:h	 
for j=1:h
if L(i,j)==0 
for m=1:h 
for n=1:h 
if L(m,n)==0 
im=abs(i-m);jn=abs(j-n); 	%�ֱ������L������Ѱ����������Ԫ�ؼ�L��ͼ�е�������
%�ϰ�������L��ͼ��x��������y�������
if im+jn==1||(im==1&&jn==1) 
H((i-1)*h+j,(m-1)*h+n)=(im^2+jn^2)^0.5; 
%�þ���H�в���Ԫ�ش洢�����ڻ�Խǵ����ϰ�������L��ͼ��λ�ú�·����
%�룬����Ԫ��ֵΪ0
end 
end 
end 
end 
end 
end 
end 
end