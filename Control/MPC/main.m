clc
clear
close all


dt = 0.1; % 采样时间

Ac = [1 1;0 1];
Bc = [0;1];
Cc = [1 0];
Dc = [0];
%% 离散方程
[Ap,Bp,Cp,Dp]=c2dm(Ac,Bc,Cc,Dc,dt);

Np=20;
Nc=4;

[Phi,F,Phi_Phi,Phi_F,Phi_R,A_e, B_e,C_e] = mpcgain(Ap,Bp,Cp,Nc,Np);
[n,n_in]=size(B_e);
xm=[0;0];
Xf=zeros(n,1);
N_sim=100;
r=ones(N_sim,1);
u=0; % u(k-1) =0
y=0;
R_bar = 0.1*eye(Nc,Nc);
H = 2*(Phi_Phi + R_bar);
R_ref = ones(Np,1);
A_cons = 0; b = 0;

for kk=1:N_sim
%     DeltaU=inv(Phi_Phi+R_bar)*(Phi_R*r(kk)-Phi_F*Xf);
    f = -2*Phi'*(R_ref-F*Xf);
    DeltaU=QPhild(H,f,A_cons,b);


    deltau=DeltaU(1,1);


    u=u+deltau;
    u1(kk)=u;
    y1(kk)=y;
 
    xm_old=xm;
    xm=Ap*xm+Bp*u;
    y=Cp*xm;
    Xf=[xm-xm_old;y];
end
% 将系统输出、控制量曲线显示出来：
k=0:(N_sim-1);
figure
subplot(211)
plot(k,y1)
xlabel('Sampling Instant')
legend('Output')
subplot(212)
plot(k,u1)
xlabel('Sampling Instant')
legend('Control')
