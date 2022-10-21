clear;
clc;
origindatatest1 = readcell("log_200108_180356.csv");
origindatatest2 = readcell("log_200108_181125.csv");
origindatatest3 = readcell("log_200108_183247.csv");
origindata = importdata("log_200108_183247.txt");
data = origindata.data;

time = data(:,1) - 64.7026;

err_dist0 = data(:,30);
err_psi0 = data(:,31);

err_dist = data(:,32);
err_psi = data(:,33);

control_angle = data(:,41);

speed = data(:,10);

figure(1);
plot(time, err_dist, "r-", "LineWidth",3);
hold on; grid on;
plot(time, err_psi, "b-", "LineWidth",3);
hold on; grid on;
plot(time, speed, "k-", "LineWidth",3);
hold on; grid on;
plot(time, control_angle / 1000, "m-", "LineWidth",3);
hold on; grid on;
%axis([0 26 -1 1]);

figure(2);
plot(time(1:200), err_dist0(1:200), "r-", "LineWidth",3);
hold on; grid on;
plot(time, err_psi0, "b-", "LineWidth",3);
hold on; grid on;
plot(time, speed, "k-", "LineWidth",3);
hold on; grid on;
plot(time, control_angle / 1000, "m-", "LineWidth",3);
hold on; grid on;
% axis([0 26 -1 1]);