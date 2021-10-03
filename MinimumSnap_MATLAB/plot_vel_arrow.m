function [] = plot_vel_arrow(point_x_input, point_y_input, vel_x_input, vel_y_input)

arrow_num = length(point_x_input(:));

for i =1:1:arrow_num
    switch i
        case 1
            quiver(point_x_input(i), point_y_input(i), vel_x_input(i)/sqrt(vel_x_input(i)^2 + vel_y_input(i)^2), vel_y_input(i)/sqrt(vel_x_input(i)^2 + vel_y_input(i)^2), 'LineWidth', 2, 'maxheadsize', 1, 'Color', 'r');
            hold on;
        case 2
            quiver(point_x_input(i), point_y_input(i), vel_x_input(i)/sqrt(vel_x_input(i)^2 + vel_y_input(i)^2), vel_y_input(i)/sqrt(vel_x_input(i)^2 + vel_y_input(i)^2), 'LineWidth', 2, 'maxheadsize', 1, 'Color', 'm');
            hold on;
        case 3
            quiver(point_x_input(i), point_y_input(i), vel_x_input(i)/sqrt(vel_x_input(i)^2 + vel_y_input(i)^2), vel_y_input(i)/sqrt(vel_x_input(i)^2 + vel_y_input(i)^2), 'LineWidth', 2, 'maxheadsize', 1, 'Color', 'c');
            hold on;
        case 4
            quiver(point_x_input(i), point_y_input(i), vel_x_input(i)/sqrt(vel_x_input(i)^2 + vel_y_input(i)^2), vel_y_input(i)/sqrt(vel_x_input(i)^2 + vel_y_input(i)^2), 'LineWidth', 2, 'maxheadsize', 1, 'Color', 'b');
            hold on;
    end
end

end