function [] = plot_point(point_x_input, point_y_input)

point_num = length(point_x_input(:));

for i =1:1:point_num
    switch i
        case 1
            plot(point_x_input(i),point_y_input(i),'r.','MarkerSize',40);
            hold on;
        case 2
            plot(point_x_input(2),point_y_input(2),'m.','MarkerSize',40);
            hold on;
        case 3
            plot(point_x_input(3),point_y_input(3),'c.','MarkerSize',40);
            hold on;
        case 4
            plot(point_x_input(4),point_y_input(4),'b.','MarkerSize',40);
            hold on;
    end
end

axis equal;
grid on;
hold on;

end