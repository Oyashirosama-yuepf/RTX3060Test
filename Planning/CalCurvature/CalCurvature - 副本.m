%通过待求节点及上下两侧节点求曲率
syms r
filename = 'U1.xlsx';
%d=90.3447;
d=100.769;
r=xlsread(filename);
r([1],:)=[];
X=zeros(size(r,1),3);
Y=zeros(size(r,1),3);
X(:,1)=r(:,2)-d;
X(:,2)=r(:,4);
X(:,3)=r(:,6)+d;
for i=1:3
    Y(:,i)=r(:,6+2*i);
end
a=zeros(size(r,1),1);
b=zeros(size(r,1),1);
c=zeros(size(r,1),1);
R=zeros(size(r,1),2);
R(:,1)=r(:,1);
 for i=1:size(r,1)
  a(i)=((X(i,1)-X(i,2))^2+(Y(i,1)-Y(i,2))^2);
   b(i)=((X(i,1)-X(i,3))^2+(Y(i,1)-Y(i,3))^2);
   c(i)=((X(i,2)-X(i,3))^2+(Y(i,2)-Y(i,3))^2);
 % R(i)=1/(sqrt(((X(i,1)-X(i,2))^2+(Y(i,1)-Y(i,2))^2)*((X(i,1)-X(i,3))^2+(Y(i,1)-Y(i,3))^2)*((X(i,2)-X(i,3))^2+(Y(i,2)-Y(i,3))^2))/sqrt(4*((X(i,1)-X(i,3))^2+(Y(i,1)-Y(i,3))^2)*((X(i,2)-X(i,3))^2+(Y(i,2)-Y(i,3))^2)-(((X(i,1)-X(i,3))^2+(Y(i,1)-Y(i,3))^2)+((X(i,2)-X(i,3))^2+(Y(i,2)-Y(i,3))^2)-((X(i,1)-X(i,2))^2+(Y(i,1)-Y(i,2))^2))^2));
R(i,2)=1/(sqrt(a(i)*b(i)*c(i))/sqrt(4*b(i)*c(i)-(b(i)+c(i)-a(i))^2));
 end
 %写入原文件
 A={' ','曲率'};
sheet = 1;
xlRange = 'N1';
xlswrite(filename,A,sheet,xlRange);
xlRange = 'N2';
xlswrite(filename,R,sheet,xlRange);


