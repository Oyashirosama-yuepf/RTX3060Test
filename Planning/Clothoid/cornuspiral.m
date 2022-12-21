function cornuspiral(b)     %�˳�����������[-b,b]�ϵĿ�Ŧ���ߣ���Ҫ���ú���romberg������comp_simpson1,comp_simpson2)
tic
if nargin<1
    b=5;
end
if b>10
    fprintf('b>10ʱ��������ܻ����нϳ�ʱ�䣡��\n');
end
a=1;

s=a:0.1:b;                %���ڿ�Ŧ�����ǶԳƵģ���ˣ�����ֻ�軭������[0,b]�ϵ�ͼ�񼴿�
[m,n]=size(s);
x=zeros(1,n);                %��ʼ������x(s),y(s)
y=zeros(1,n);

% f=@(x)cos(x.^2/2);           %���������ֵı�������
% g=@(x)sin(x.^2/2);

% for k=1:n
%     x(k)=romberg(f,0,s(k),1e-3);       %���������񷽷�������������ֵĽ���ֵ�������ȡ1e-3
%     y(k)=romberg(g,0,s(k),1e-3);
%     
% %     x(k)=romberg1(0,s(k),1e-3);
% %     y(k)=romberg2(0,s(k),1e-3);
% 
% end
% subplot(1,2,1);
% plot(x,y,'g');                      %������Ŧ��������[0,b]�ϵ�ͼ��
% hold on
% plot(-x,-y,'g');                    %���öԳ��ԣ�����[-b,0]�ϵ�ͼ��
% hold on
% text(-1,1,'green--ep=1e-3');
% title('cornuspiral');
% 
%  for k=1:n
%     x(k)=romberg(f,0,s(k),1e-7);       %���������񷽷�������������ֵĽ���ֵ�������ȡ1e-7
%     y(k)=romberg(g,0,s(k),1e-7);
%     
% %     x(k)=romberg1(0,s(k),1e-7);
% %     y(k)=romberg2(0,s(k),1e-7);
%     
%  end
%  subplot(1,2,2);
%  plot(x,y,'r');                      %������Ŧ��������[0,b]�ϵ�ͼ��
%  hold on
%  plot(-x,-y,'r');                    %���öԳ��ԣ�����[-b,0]�ϵ�ͼ��
%  hold on
%  text(-1,0.8,'red--ep=1e-7');
%  title('cornuspiral');
 
 for k=1:n   
    x(k)=comp_simpson1(s(1),s(k),20*b);     %���ø���simpson�����ʽ������������ֵĽ���ֵ��ȡ20*b+1���ȷֽڵ�
    y(k)=comp_simpson2(s(1),s(k),20*b);
 end
% subplot(1,2,1);
plot(x,y,'k', 'linewidth',3);                      %������Ŧ��������[0,b]�ϵ�ͼ��
hold on
% plot(-x,-y,'y');                    %���öԳ��ԣ�����[-b,0]�ϵ�ͼ��
% hold on

%  for k=1:n 
%     x(k)=comp_simpson1(0,s(k),40*b);         %���ø���simpson�����ʽ������������ֵĽ���ֵ��ȡ40*b+1���ȷֽڵ�
%     y(k)=comp_simpson2(0,s(k),40*b);
%  end
%  subplot(1,2,2);
%  plot(x,y,'b');                      %������Ŧ��������[0,b]�ϵ�ͼ��
%  hold on
%  plot(-x,-y,'b');                    %���öԳ��ԣ�����[-b,0]�ϵ�ͼ��
%  hold on

 toc
end