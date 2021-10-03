%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ���������ٶȱ䷽������� %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
clear all;
clc;
%��һ������ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figurepos(2, 3, 1, '��������');

%���õ㣬ʱ���Լ�ÿ�ι켣��ʱ��ռ��
point_x = [0, 5, 1, 3];
point_y = [0, 1, 2, 3];
proportion = [1/3, 1/3, 1/3];
T = 3;
%�����ٶ�
vel_x = [0, -3, -3, 0];
vel_y = [0, 1, 1, 1];

%�����ι켣��ÿ�ι켣������ζ���ʽ��ÿ�ι켣��ʱ��ΪT/3
[para_x_1] = mini_snap_plan(point_x, T, vel_x, proportion);
[para_y_1] = mini_snap_plan(point_y, T, vel_y, proportion);

subplot(1,3,1);
%������ٶȱ�ʶ
plot_point(point_x, point_y);
plot_vel_arrow(point_x, point_y, vel_x, vel_y);
axis([-1 6 -1 5]);
hold on;

%�켣���ӻ�
plot_traj(para_x_1, para_y_1, T, proportion);


%�ڶ������� %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1);

%�����ٶ�
vel_x = [0, 0, 0, 0];
vel_y = [0, 1, 1, 1];

%�����ι켣��ÿ�ι켣������ζ���ʽ��ÿ�ι켣��ʱ��ΪT/3
[para_x_2] = mini_snap_plan(point_x, T, vel_x, proportion);
[para_y_2] = mini_snap_plan(point_y, T, vel_y, proportion);

subplot(1,3,2);
%������ٶȱ�ʶ
plot_point(point_x, point_y);
plot_vel_arrow(point_x, point_y, vel_x, vel_y);
axis([-1 6 -1 5]);
hold on;

%�켣���ӻ�
plot_traj(para_x_2, para_y_2, T, proportion);


%���������� %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1);

%�����ٶ�
vel_x = [0, 3, 3, 0];
vel_y = [0, 1, 1, 1];

%�����ι켣��ÿ�ι켣������ζ���ʽ��ÿ�ι켣��ʱ��ΪT/3
[para_x_3] = mini_snap_plan(point_x, T, vel_x, proportion);
[para_y_3] = mini_snap_plan(point_y, T, vel_y, proportion);

subplot(1,3,3);
%������ٶȱ�ʶ
plot_point(point_x, point_y);
plot_vel_arrow(point_x, point_y, vel_x, vel_y);
axis([-1 6 -1 5]);
hold on;

%�켣���ӻ�
plot_traj(para_x_3, para_y_3, T, proportion);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ���Ƶ�һ�����ӵ�pos, vel�Լ�acc %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figurepos(2, 3, 2, '��һ�����ӵ�pos, vel�Լ�acc');

plot_pos_vel_acc(para_x_1, para_y_1, T);
