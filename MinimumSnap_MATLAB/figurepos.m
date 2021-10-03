function figurepos(RowNum, ColNum, FigNum, FigName)

% FIGUREPOS(FigName, RowNum, ColNum, FigNum) divide the whole screen into 

%RowNum*ColNum, put figure named FigName at position FigNum

% --FigName: figure name

% --RowNum: number of rows

% --ColNum: number of columns

% --FigNum: figure position

Fighandle = figure('NumberTitle', 'off', 'Name', FigName);

a = ceil(FigNum/ColNum);

b = rem(FigNum, ColNum);

if a==0

    a = 1;

end

if b==0

    b = ColNum;

end

axes('Position', [0.01 0.01 0.98 1]);%child figure position:[left, bottom, width, height]

set(Fighandle,'Unit','normalized','Position', [0.01+(b-1)/ColNum,0.06+(0.95-0.01*RowNum)*(RowNum-a)/RowNum,(1-0.01*(ColNum+1))/ColNum, (0.95-0.01*RowNum)/RowNum*0.8]);