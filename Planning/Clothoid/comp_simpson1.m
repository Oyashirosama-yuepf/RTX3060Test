function s=comp_simpson1(a,b,n)    %此程序使用n+1个等分节点的复化simpson公式计算函数f在区间[a,b]上积分的近似值，需要调用函数f1

m=floor(n/2);   %若n为偶数，则n=2*m.若n为奇数，则n=2*m+1.
h=(b-a)/n;      %将区间[a,b]等分成n份，每个小区间的长度

x=linspace(a,b,n+1);    %求出各个节点和节点上的函数值，分别保存在向量x，fx中
fx=f1(x);

s=0;
for k=1:m-1             %利用复化simpson公式求解函数f在区间[a,x(2*m+1)]上积分的近似值
    s=s+2*fx(2*k+1);
end
for k=1:m
    s=s+4*fx(2*k);
end
s=h/3*(fx(1)+fx(2*m+1)+s);
if m~=n/2                %如果n为偶数，则s即为所求的积分近似值，否则，需要加上最后一个小区间[x(2*m+1),x(2*m+2)]上积分的近似值，此值利用梯形公式求出
    s=s+(fx(2*m+1)+fx(2*m+2))*h/2;
end

% fprintf('根据复化simpson公式，利用[%.3f,%.3f]上%d个等分节点计算出的被积函数在区间[%.3f,%.3f]上的定积分近似值为：\n%.12f\n',a,b,n+1,a,b,s);
% end