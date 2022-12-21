x = linspace(0,20,10000);

a1 = animatedline('Color',[0 .7 .7]);
a2 = animatedline('Color',[0 .5 .5]);
for k = 1:length(x)
    % first line
    xk = x(k);%更新x坐标
    ysin = sin(xk);
    addpoints(a1,xk,ysin);%点的添加

    % second line
    ycos = cos(xk);
    addpoints(a2,xk,ycos);

    % update screen
    drawnow limitrate %命令
    pause(0.01);
end