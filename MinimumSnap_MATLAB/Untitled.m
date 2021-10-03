%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 绘制三个速度变方向的例子 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
clear all;
clc;
%第一个例子 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figurepos(2, 3, 1, '三个例子');

%设置点，时间以及每段轨迹的时间占比
point_x = [0, 5, 1, 3];
point_y = [0, 1, 2, 3];
proportion = [1/3, 1/3, 1/3];
T = 3;
%设置速度
vel_x = [0, -3, -3, 0];
vel_y = [0, 1, 1, 1];

%共三段轨迹，每段轨迹都是五次多项式，每段轨迹的时间为T/3
[para_x_1] = mini_snap_plan(point_x, T, vel_x, proportion);
[para_y_1] = mini_snap_plan(point_y, T, vel_y, proportion);

subplot(1,3,1);
%画点和速度标识
plot_point(point_x, point_y);
plot_vel_arrow(point_x, point_y, vel_x, vel_y);
axis([-1 6 -1 5]);
hold on;

%轨迹可视化
plot_traj(para_x_1, para_y_1, T, proportion);


%第二个例子 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1);

%设置速度
vel_x = [0, 0, 0, 0];
vel_y = [0, 1, 1, 1];

%共三段轨迹，每段轨迹都是五次多项式，每段轨迹的时间为T/3
[para_x_2] = mini_snap_plan(point_x, T, vel_x, proportion);
[para_y_2] = mini_snap_plan(point_y, T, vel_y, proportion);

subplot(1,3,2);
%画点和速度标识
plot_point(point_x, point_y);
plot_vel_arrow(point_x, point_y, vel_x, vel_y);
axis([-1 6 -1 5]);
hold on;

%轨迹可视化
plot_traj(para_x_2, para_y_2, T, proportion);


%第三个例子 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1);

%设置速度
vel_x = [0, 3, 3, 0];
vel_y = [0, 1, 1, 1];

%共三段轨迹，每段轨迹都是五次多项式，每段轨迹的时间为T/3
[para_x_3] = mini_snap_plan(point_x, T, vel_x, proportion);
[para_y_3] = mini_snap_plan(point_y, T, vel_y, proportion);

subplot(1,3,3);
%画点和速度标识
plot_point(point_x, point_y);
plot_vel_arrow(point_x, point_y, vel_x, vel_y);
axis([-1 6 -1 5]);
hold on;

%轨迹可视化
plot_traj(para_x_3, para_y_3, T, proportion);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 绘制第一个例子的pos, vel以及acc %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figurepos(2, 3, 2, '第一个例子的pos, vel以及acc');

plot_pos_vel_acc(para_x_1, para_y_1, T);
