close all;
clear;
clc;

dir=getenv('HOLO_LOG_ROOT_LOCALIZATION_VISION');
cd(dir)

%% read bagname from user
bag_name = input('Please input bag name: ', 's');

%% import tracking result from .csv files
tracks_info = importdata('evaluated_result.csv');
time_cost = importdata('time_cost.csv');
valid_candidate = tracks_info(tracks_info(:,3) > 1, :);
total_tracks_number = length(tracks_info);
valid_candidate_number = length(valid_candidate);

%% plot tracker time cost per frame
time_cost_name = strcat(bag_name, 'TimeCostPerFrame');
figure('Name', time_cost_name);
plot(time_cost(:, 1), '-+');
xlabel('frame id');
ylabel('tracking time (ms)');
title('tracking time cost per frame');
grid on;
set(gcf,'Position',get(0,'ScreenSize'));
saveas(gca, fullfile('.', time_cost_name), 'png');

%% plot track length for all tracks
track_length_name = strcat(bag_name, 'TrackLength_AllTracks');
figure('Name', track_length_name);
subplot(2, 2, 1);
histogram(tracks_info(:,3), 'BinWidth', 1);
xlabel('track length');
ylabel('track number');
title('track length histogram(BinWidth: 1)');
grid on;

subplot(2, 2, 2);
boxplot(tracks_info(:,3));
hold on;
plot(mean(tracks_info(:, 3)), 'd');
ylabel('track length');
title('track length box plot');
grid on;

subplot(2, 2, 3);
plot(tracks_info(:,1), tracks_info(:,3), 'o');
xlabel('track id');
ylabel('track length');
title('track length w.r.t track id');
grid on;

set(gcf,'Position',get(0,'ScreenSize'));
saveas(gca, fullfile('.', track_length_name), 'png');

%% plot track length for valid candidate tracks
track_length_name = strcat(bag_name, 'TrackLength_CandidateTracks');
figure('Name', track_length_name);
subplot(2, 2, 1);
histogram(valid_candidate(:,3), 'BinWidth', 1);
xlabel('track length');
ylabel('track number');
title('track length histogram(BinWidth: 1)');
grid on;

subplot(2, 2, 2);
boxplot(valid_candidate(:,3));
hold on;
plot(mean(valid_candidate(:, 3)), 'd');
ylabel('track length');
title('track length box plot');
grid on;

subplot(2, 2, 3);
plot(valid_candidate(:,1), valid_candidate(:,3), 'o');
xlabel('track id');
ylabel('track length');
title('track length w.r.t track id');
grid on;

set(gcf,'Position',get(0,'ScreenSize'));
saveas(gca, fullfile('.', track_length_name), 'png');

%% plot reproject error
proj_err_name = strcat(bag_name, 'ReprojectError');
figure('Name', proj_err_name);
subplot(2, 2, 1);
histogram(valid_candidate(:,2), 'BinWidth', 3);
xlabel('reproject error in pixel');
ylabel('track number');
title('reproject error histogram(BinWidth: 3.0 pixel)');
grid on;

subplot(2, 2, 2);
boxplot(valid_candidate(:,2));
hold on;
plot(mean(valid_candidate(:, 2)), 'd');
ylabel('reproject error in pixel');
title('reproject error box plot');
grid on;

subplot(2, 2, 3);
plot(valid_candidate(:,1), valid_candidate(:,2), 'o');
xlabel('track id');
ylabel('reproject error(pixel)');
title('reproject error w.r.t track id');
grid on;

set(gcf,'Position',get(0,'ScreenSize'));
saveas(gca, fullfile('.', proj_err_name), 'png');

%% plot result table
error_th = 5;
format long g;
format short g;
data = [length(time_cost(:,1)), ...
        total_tracks_number, ...
        100.0 * valid_candidate_number / total_tracks_number, ...
        mean(valid_candidate(:, 3)), ...
        mean(valid_candidate(:, 2)), ...
        100.0 * length(valid_candidate(valid_candidate(:,2) < error_th, :)) / valid_candidate_number, ...
        mean(time_cost(:, 1));
        
        NaN, ...
        NaN, ...
        NaN, ...
        std(valid_candidate(:, 3)), ...
        std(valid_candidate(:, 2)), ...
        NaN, ...
        std(time_cost(:, 1));
        
        NaN, ...
        NaN, ...
        NaN, ...
        rms(valid_candidate(:, 3)), ...
        rms(valid_candidate(:, 2)), ...
        NaN, ...
        rms(time_cost(:, 1));
        
        NaN, ...
        NaN, ...
        NaN, ...
        min(valid_candidate(:, 3)), ...
        min(valid_candidate(:, 2)), ...
        NaN, ...
        min(time_cost(:, 1));
        
        NaN, ...
        NaN, ...
        NaN, ...
        max(valid_candidate(:, 3)), ...
        max(valid_candidate(:, 2)), ...
        NaN, ...
        max(time_cost(:, 1));
        ];

column_name = {'FrameNum', ...
               'TotalTrackNum', ...
               'CandidateRatio(%)', ...
               'TrackLength', ...
               'ProjError', ...
               'Error < 5 (%)', ...
               'TimeCost(ms)'};
row_name = {'mean', 'std', 'rmse', 'min', 'max'};

table_name = strcat(bag_name, 'ResultTable');
f = figure('Name', table_name);
t = uitable('Data', data, 'Columnname', column_name, 'Rowname', row_name);
t.Position(1:2) = [0 0];
t.Position(3:4) = t.Extent(3:4);
f.Position(3:4) = t.Position(3:4);
saveas(gca, fullfile('.', table_name), 'png');

%% save track id which error > 20
focused_track = valid_candidate(((valid_candidate(:,2) > 20)));
fid = fopen('focused_track_id.txt','w');
for i = 1:length(focused_track(:,1))
   fprintf(fid,'%d, ',focused_track(i,1));
end
fclose(fid);
close all;
clear;
clc;
