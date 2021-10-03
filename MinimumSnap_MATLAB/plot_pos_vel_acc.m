function [] = plot_pos_vel_acc(para_x_1, para_y_1, T)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% x和y的第一段 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
t = 0:T/300:T/3;
pos_x_exampleI_1 = para_x_1(1).*(t.^5) + para_x_1(2).*(t.^4) + para_x_1(3).*(t.^3) + para_x_1(4).*(t.^2) + para_x_1(5).*(t.^1) + para_x_1(6)*(t.^0);
vel_x_exampleI_1 = 5*para_x_1(1).*(t.^4) + 4*para_x_1(2).*(t.^3) + 3*para_x_1(3).*(t.^2) + 2*para_x_1(4).*(t.^1) + para_x_1(5);
acc_x_exampleI_1 = 20*para_x_1(1).*(t.^3) + 12*para_x_1(2).*(t.^2) + 6*para_x_1(3).*(t.^1) + 2*para_x_1(4);

subplot(3, 2, 1);
plot(t, pos_x_exampleI_1, 'LineWidth', 2, 'Color', 'r');
hold on;

subplot(3, 2, 3);
plot(t, vel_x_exampleI_1, 'LineWidth', 2, 'Color', 'r');
hold on;

subplot(3, 2, 5);
plot(t, acc_x_exampleI_1, 'LineWidth', 2, 'Color', 'r');
hold on;


pos_y_exampleI_1 = para_y_1(1).*(t.^5) + para_y_1(2).*(t.^4) + para_y_1(3).*(t.^3) + para_y_1(4).*(t.^2) + para_y_1(5).*(t.^1) + para_y_1(6)*(t.^0);
vel_y_exampleI_1 = 5*para_y_1(1).*(t.^4) + 4*para_y_1(2).*(t.^3) + 3*para_y_1(3).*(t.^2) + 2*para_y_1(4).*(t.^1) + para_y_1(5);
acc_y_exampleI_1 = 20*para_y_1(1).*(t.^3) + 12*para_y_1(2).*(t.^2) + 6*para_y_1(3).*(t.^1) + 2*para_y_1(4);

subplot(3, 2, 2);
plot(t, pos_y_exampleI_1, 'LineWidth', 2, 'Color', 'r');
hold on;

subplot(3, 2, 4);
plot(t, vel_y_exampleI_1, 'LineWidth', 2, 'Color', 'r');
hold on;

subplot(3, 2, 6);
plot(t, acc_y_exampleI_1, 'LineWidth', 2, 'Color', 'r');
hold on;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% x和y的第二段 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
t = T/3:T/300:2*T/3;
pos_x_exampleI_2 = para_x_1(7).*(t.^5) + para_x_1(8).*(t.^4) + para_x_1(9).*(t.^3) + para_x_1(10).*(t.^2) + para_x_1(11).*(t.^1) + para_x_1(12)*(t.^0);
vel_x_exampleI_2 = 5*para_x_1(7).*(t.^4) + 4*para_x_1(8).*(t.^3) + 3*para_x_1(9).*(t.^2) + 2*para_x_1(10).*(t.^1) + para_x_1(11);
acc_x_exampleI_2 = 20*para_x_1(7).*(t.^3) + 12*para_x_1(8).*(t.^2) + 6*para_x_1(9).*(t.^1) + 2*para_x_1(10);

subplot(3, 2, 1);
plot(t, pos_x_exampleI_2, 'LineWidth', 2, 'Color', 'm');
hold on;

subplot(3, 2, 3);
plot(t, vel_x_exampleI_2, 'LineWidth', 2, 'Color', 'm');
hold on;

subplot(3, 2, 5);
plot(t, acc_x_exampleI_2, 'LineWidth', 2, 'Color', 'm');
hold on;


pos_y_exampleI_2 = para_y_1(7).*(t.^5) + para_y_1(8).*(t.^4) + para_y_1(9).*(t.^3) + para_y_1(10).*(t.^2) + para_y_1(11).*(t.^1) + para_y_1(12)*(t.^0);
vel_y_exampleI_2 = 5*para_y_1(7).*(t.^4) + 4*para_y_1(8).*(t.^3) + 3*para_y_1(9).*(t.^2) + 2*para_y_1(10).*(t.^1) + para_y_1(11);
acc_y_exampleI_2 = 20*para_y_1(7).*(t.^3) + 12*para_y_1(8).*(t.^2) + 6*para_y_1(9).*(t.^1) + 2*para_y_1(10);

subplot(3, 2, 2);
plot(t, pos_y_exampleI_2, 'LineWidth', 2, 'Color', 'm');
hold on;

subplot(3, 2, 4);
plot(t, vel_y_exampleI_2, 'LineWidth', 2, 'Color', 'm');
hold on;

subplot(3, 2, 6);
plot(t, acc_y_exampleI_2, 'LineWidth', 2, 'Color', 'm');
hold on;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% x和y的第三段 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
t = 2*T/3:T/300:T;
pos_x_exampleI_3 = para_x_1(13).*(t.^5) + para_x_1(14).*(t.^4) + para_x_1(15).*(t.^3) + para_x_1(16).*(t.^2) + para_x_1(17).*(t.^1) + para_x_1(18)*(t.^0);
vel_x_exampleI_3 = 5*para_x_1(13).*(t.^4) + 4*para_x_1(14).*(t.^3) + 3*para_x_1(15).*(t.^2) + 2*para_x_1(16).*(t.^1) + para_x_1(17);
acc_x_exampleI_3 = 20*para_x_1(13).*(t.^3) + 12*para_x_1(14).*(t.^2) + 6*para_x_1(15).*(t.^1) + 2*para_x_1(16);

subplot(3, 2, 1);
plot(t, pos_x_exampleI_3, 'LineWidth', 2, 'Color', 'c');
hold on;

subplot(3, 2, 3);
plot(t, vel_x_exampleI_3, 'LineWidth', 2, 'Color', 'c');
hold on;

subplot(3, 2, 5);
plot(t, acc_x_exampleI_3, 'LineWidth', 2, 'Color', 'c');
hold on;


pos_y_exampleI_3 = para_y_1(13).*(t.^5) + para_y_1(14).*(t.^4) + para_y_1(15).*(t.^3) + para_y_1(16).*(t.^2) + para_y_1(17).*(t.^1) + para_y_1(18)*(t.^0);
vel_y_exampleI_3 = 5*para_y_1(13).*(t.^4) + 4*para_y_1(14).*(t.^3) + 3*para_y_1(15).*(t.^2) + 2*para_y_1(16).*(t.^1) + para_y_1(17);
acc_y_exampleI_3 = 20*para_y_1(13).*(t.^3) + 12*para_y_1(14).*(t.^2) + 6*para_y_1(15).*(t.^1) + 2*para_y_1(16);

subplot(3, 2, 2);
plot(t, pos_y_exampleI_3, 'LineWidth', 2, 'Color', 'c');
hold on;

subplot(3, 2, 4);
plot(t, vel_y_exampleI_3, 'LineWidth', 2, 'Color', 'c');
hold on;

subplot(3, 2, 6);
plot(t, acc_y_exampleI_3, 'LineWidth', 2, 'Color', 'c');
hold on;

end

