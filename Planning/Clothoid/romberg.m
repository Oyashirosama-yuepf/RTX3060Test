function r=romberg(f,a,b,ep)   %此程序使用龙贝格方法求解函数f在区间[a,b]上积分的近似值，ep为后验误差限，f为函数句柄

if nargin<4
    ep=1e-8;
end

N=20;               %N控制循环次数的上限，防止龙贝格方法的外推次数过多
A=zeros(N);         %A存放龙贝格方法产生的积分近似值

h=b-a;                                      %h为等分后小区间的长度，初始值设为b-a
A(1,1)=h*(f(a)+f(b))/2;                     %A(1,1)存放由梯形公式计算出的积分近似值
for k=2:N                                   %循环外推
    for j=1:k
        if j==1
            h=h/2;
            for i=1:2^(k-2)
            A(k,j)=A(k,j)+f(a+(2*i-1)*h);         %A矩阵的第一列存放由梯形公式的逐次分半算法计算出的积分近似值
            end
            A(k,j)=A(k,j)*h+A(k-1,j)/2;
            p=1;
        else
            p=4*p;
            A(k,j)=(p*A(k,j-1)-A(k-1,j-1))/(p-1);     %外推
        end
    end
    if abs(A(k,k)-A(k-1,k-1))<ep                   %如果后验误差小于给定的误差限，终止循环
        break;
    end
end
r=A(k,k);                                      %循环终止时A(k,k)存放的即是所要求的积分近似值

if k==N                                        %如果外推次数达到上限却仍没有达到给定的精度，则警告
    fprintf('Romberg外推次数已达上限%d！\n',N);
end
% fprintf('由Romberg求积公式，被积函数在区间[%.3f,%.3f]上误差限不超过%e的积分近似值为%.12f\n',a,b,ep,A(k,k));
end