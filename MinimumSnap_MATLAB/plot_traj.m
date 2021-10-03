function [] = plot_traj(para_x_input, para_y_input, T, proportion_input)

%本次规划共有多少段
seg_time = length(proportion_input);

%在每个给定点处的时间
t(1) = proportion_input(1) * T; 
if seg_time > 1
    for i = 2:1:seg_time
        t(i) = t(i-1) + proportion_input(i) * T
    end
end

%绘制每段轨迹
for i = 1:1:seg_time
    if i ==1
        dt = 0:T/300:t(1);
    else
        dt = t(i - 1):T/300:t(i);
    end
    
    x = para_x_input((i - 1) * 6 + 1).*(dt.^5) + ...
        para_x_input((i - 1) * 6 + 2).*(dt.^4) + ...
        para_x_input((i - 1) * 6 + 3).*(dt.^3) + ...
        para_x_input((i - 1) * 6 + 4).*(dt.^2) + ...
        para_x_input((i - 1) * 6 + 5).*(dt.^1) + ...
        para_x_input((i - 1) * 6 + 6)*(dt.^0); 
    y = para_y_input((i - 1) * 6 + 1).*(dt.^5) + ...
        para_y_input((i - 1) * 6 + 2).*(dt.^4) + ...
        para_y_input((i - 1) * 6 + 3).*(dt.^3) + ...
        para_y_input((i - 1) * 6 + 4).*(dt.^2) + ...
        para_y_input((i - 1) * 6 + 5).*(dt.^1) + ...
        para_y_input((i - 1) * 6 + 6)*(dt.^0);
    
    plot(x,y,'LineWidth',2,'Color','k');
    hold on;
end











% %第一段轨迹
% t = 0:T/300:proportion_input(1)*T;
% x = para_x_input(1).*(t.^5) + para_x_input(2).*(t.^4) + para_x_input(3).*(t.^3) + para_x_input(4).*(t.^2) + para_x_input(5).*(t.^1) + para_x_input(6)*(t.^0); 
% y = para_y_input(1).*(t.^5) + para_y_input(2).*(t.^4) + para_y_input(3).*(t.^3) + para_y_input(4).*(t.^2) + para_y_input(5).*(t.^1) + para_y_input(6)*(t.^0);  
% plot(x,y,'LineWidth',2,'Color','k');
% hold on;
% 
% %第二段轨迹
% t = proportion_input(1)*T:T/300:(proportion_input(1)+proportion_input(2))*T;
% x = para_x_input(7).*(t.^5) + para_x_input(8).*(t.^4) + para_x_input(9).*(t.^3) + para_x_input(10).*(t.^2) + para_x_input(11).*(t.^1) + para_x_input(12)*(t.^0); 
% y = para_y_input(7).*(t.^5) + para_y_input(8).*(t.^4) + para_y_input(9).*(t.^3) + para_y_input(10).*(t.^2) + para_y_input(11).*(t.^1) + para_y_input(12)*(t.^0);  
% plot(x,y,'LineWidth',2,'Color','k');
% hold on;
% 
% %第三段轨迹
% t = (proportion_input(1)+proportion_input(2))*T:T/300:T;
% x = para_x_input(13).*(t.^5) + para_x_input(14).*(t.^4) + para_x_input(15).*(t.^3) + para_x_input(16).*(t.^2) + para_x_input(17).*(t.^1) + para_x_input(18)*(t.^0); 
% y = para_y_input(13).*(t.^5) + para_y_input(14).*(t.^4) + para_y_input(15).*(t.^3) + para_y_input(16).*(t.^2) + para_y_input(17).*(t.^1) + para_y_input(18)*(t.^0);  
% plot(x,y,'LineWidth',2,'Color','k');
% hold on;

end